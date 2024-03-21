// Extend the switch in the CPythonNetworkStream::GamePhase function with this:
#ifdef ENABLE_AURA_SYSTEM
			case HEADER_GC_AURA:
				ret = RecvAuraPacket();
				break;
#endif

// Add the followings anywhere you want to:
#ifdef ENABLE_AURA_SYSTEM
bool CPythonNetworkStream::RecvAuraPacket()
{
	TPacketGCAura kAuraPacket;
	if (!Recv(sizeof(TPacketGCAura), &kAuraPacket))
	{
		Tracef("Aura Packet Error SubHeader %u\n", kAuraPacket.bSubHeader);
		return false;
	}

	int iPacketSize = int(kAuraPacket.wSize) - sizeof(TPacketGCAura);

	switch (kAuraPacket.bSubHeader)
	{
	case AURA_SUBHEADER_GC_OPEN:
	case AURA_SUBHEADER_GC_CLOSE:
	{
		if (iPacketSize > 0)
		{
			TSubPacketGCAuraOpenClose kSubPacket;
			assert(iPacketSize % sizeof(TSubPacketGCAuraOpenClose) == 0 && "AURA_SUBHEADER_GC_OPENCLOSE");
			if (!Recv(sizeof(TSubPacketGCAuraOpenClose), &kSubPacket))
				return false;

			if (kAuraPacket.bSubHeader == AURA_SUBHEADER_GC_OPEN)
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AuraWindowOpen", Py_BuildValue("(i)", kSubPacket.bAuraWindowType));

			else if (kAuraPacket.bSubHeader == AURA_SUBHEADER_GC_CLOSE)
			{
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AuraWindowClose", Py_BuildValue("()"));
				CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_MAIN);
				CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_SUB);
				CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_RESULT);
			}

			CPythonPlayer::instance().SetAuraRefineWindowOpen(kSubPacket.bAuraWindowType);
		}
		else
			TraceError(" RecvAuraPacket Error 0x04100%u0F", kAuraPacket.bSubHeader);

		break;
	}
	case AURA_SUBHEADER_GC_SET_ITEM:
	{
		if (iPacketSize > 0)
		{
			TSubPacketGCAuraSetItem kSubPacket;
			assert(iPacketSize % sizeof(TSubPacketGCAuraSetItem) == 0 && "AURA_SUBHEADER_GC_SET_ITEM");
			if (!Recv(sizeof(TSubPacketGCAuraSetItem), &kSubPacket))
				return false;

			TItemData kItemData;
			kItemData.vnum = kSubPacket.pItem.vnum;
			kItemData.count = kSubPacket.pItem.count;
			for (int iSocket = 0; iSocket < ITEM_SOCKET_SLOT_MAX_NUM; ++iSocket)
				kItemData.alSockets[iSocket] = kSubPacket.pItem.alSockets[iSocket];
			for (int iAttr = 0; iAttr < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++iAttr)
				kItemData.aAttr[iAttr] = kSubPacket.pItem.aAttr[iAttr];

			if (kSubPacket.Cell.IsValidCell() && !kSubPacket.Cell.IsEquipCell())
				CPythonPlayer::instance().SetActivatedAuraSlot(BYTE(kSubPacket.AuraCell.cell), kSubPacket.Cell);

			CPythonPlayer::instance().SetAuraItemData(BYTE(kSubPacket.AuraCell.cell), kItemData);
		}
		else
			TraceError(" RecvAuraPacket Error 0x040%uBABE", kAuraPacket.bSubHeader);

		break;
	}
	case AURA_SUBHEADER_GC_CLEAR_SLOT:
	{
		if (iPacketSize > 0)
		{
			TSubPacketGCAuraClearSlot kSubPacket;
			assert(iPacketSize % sizeof(TSubPacketGCAuraClearSlot) == 0 && "AURA_SUBHEADER_GC_CLEAR_SLOT");
			if (!Recv(sizeof(TSubPacketGCAuraClearSlot), &kSubPacket))
				return false;

			CPythonPlayer::instance().DelAuraItemData(kSubPacket.bAuraSlotPos);
		}
		else
			TraceError(" RecvAuraPacket Error 0x04FF0%uAA", kAuraPacket.bSubHeader);

		break;
	}
	case AURA_SUBHEADER_GC_CLEAR_ALL:
	{
		CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_MAIN);
		CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_SUB);
		CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_RESULT);
		break;
	}
	case AURA_SUBHEADER_GC_CLEAR_RIGHT:
	{
		if (iPacketSize == 0)
			CPythonPlayer::instance().DelAuraItemData(AURA_SLOT_SUB);
		else
			TraceError("invalid packet size %d", iPacketSize);
		break;
	}
	case AURA_SUBHEADER_GC_REFINE_INFO:
	{
		if (iPacketSize > 0)
		{
			for (size_t i = 0; iPacketSize > 0; ++i)
			{
				assert(iPacketSize % sizeof(TSubPacketGCAuraRefineInfo) == 0 && "AURA_SUBHEADER_GC_REFINE_INFO");
				TSubPacketGCAuraRefineInfo kSubPacket;
				if (!Recv(sizeof(TSubPacketGCAuraRefineInfo), &kSubPacket))
					return false;

				CPythonPlayer::instance().SetAuraRefineInfo(kSubPacket.bAuraRefineInfoType, kSubPacket.bAuraRefineInfoLevel, kSubPacket.bAuraRefineInfoExpPercent);
				iPacketSize -= sizeof(TSubPacketGCAuraRefineInfo);
			}

		}
		else
			TraceError(" RecvAuraPacket Error 0x04000%FF", kAuraPacket.bSubHeader);

		break;
	}
	}

	__RefreshInventoryWindow();

	return true;
}

bool CPythonNetworkStream::SendAuraRefineCheckIn(TItemPos InventoryCell, TItemPos AuraCell, BYTE byAuraRefineWindowType)
{
	__PlayInventoryItemDropSound(InventoryCell);

	TPacketCGAura kAuraPacket;
	kAuraPacket.wSize = sizeof(TPacketCGAura) + sizeof(TSubPacketCGAuraRefineCheckIn);
	kAuraPacket.bSubHeader = AURA_SUBHEADER_CG_REFINE_CHECKIN;

	TSubPacketCGAuraRefineCheckIn kAuraSubPacket;
	kAuraSubPacket.ItemCell = InventoryCell;
	kAuraSubPacket.AuraCell = AuraCell;
	kAuraSubPacket.byAuraRefineWindowType = byAuraRefineWindowType;

	if (!Send(sizeof(TPacketCGAura), &kAuraPacket))
		return false;

	if (!Send(sizeof(TSubPacketCGAuraRefineCheckIn), &kAuraSubPacket))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendAuraRefineCheckOut(TItemPos AuraCell, BYTE byAuraRefineWindowType)
{
	TPacketCGAura kAuraPacket;
	kAuraPacket.wSize = sizeof(TPacketCGAura) + sizeof(TSubPacketCGAuraRefineCheckOut);
	kAuraPacket.bSubHeader = AURA_SUBHEADER_CG_REFINE_CHECKOUT;

	TSubPacketCGAuraRefineCheckOut kAuraSubPacket;
	kAuraSubPacket.AuraCell = AuraCell;
	kAuraSubPacket.byAuraRefineWindowType = byAuraRefineWindowType;

	if (!Send(sizeof(TPacketCGAura), &kAuraPacket))
		return false;

	if (!Send(sizeof(TSubPacketCGAuraRefineCheckOut), &kAuraSubPacket))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendAuraRefineAccept(BYTE byAuraRefineWindowType)
{
	TPacketCGAura kAuraPacket;
	kAuraPacket.wSize = sizeof(TPacketCGAura) + sizeof(TSubPacketCGAuraRefineAccept);
	kAuraPacket.bSubHeader = AURA_SUBHEADER_CG_REFINE_ACCEPT;

	TSubPacketCGAuraRefineAccept kAuraSubPacket;
	kAuraSubPacket.byAuraRefineWindowType = byAuraRefineWindowType;

	if (!Send(sizeof(TPacketCGAura), &kAuraPacket))
		return false;

	if (!Send(sizeof(TSubPacketCGAuraRefineAccept), &kAuraSubPacket))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendAuraRefineCancel()
{
	TPacketCGAura kAuraPacket;
	kAuraPacket.wSize = sizeof(TPacketCGAura);
	kAuraPacket.bSubHeader = AURA_SUBHEADER_CG_REFINE_CANCEL;

	if (!Send(sizeof(TPacketCGAura), &kAuraPacket))
		return false;

	return SendSequence();
}
#endif
