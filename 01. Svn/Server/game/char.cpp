// Add the followings to the bottom of the CHARACTER::Initialize function:
#ifdef __AURA_SYSTEM__
	m_bAuraRefineWindowType = AURA_WINDOW_TYPE_MAX;
	m_bAuraRefineWindowOpen = false;
	for (BYTE i = AURA_SLOT_MAIN; i < AURA_SLOT_MAX; i++)
		m_pAuraRefineWindowItemSlot[i] = NPOS;

	memset(&m_bAuraRefineInfo, 0, AURA_REFINE_INFO_SLOT_MAX * sizeof(TAuraRefineInfo));
#endif

// Extend the CHARACTER::EncodeInsertPacket with the following where the rest parts are:
#ifdef __AURA_SYSTEM__
		addPacket.awPart[CHR_EQUIPPART_AURA] = GetPart(PART_AURA);
#endif

// Extend the CHARACTER::UpdatePacket with the following where the rest parts are:
#ifdef __AURA_SYSTEM__
	pack.awPart[CHR_EQUIPPART_AURA] = GetPart(PART_AURA);
#endif

// In the CHARACTER::Disconnect after this:
	CloseMall();

// Paste this:
#ifdef __AURA_SYSTEM__
	if (IsAuraRefineWindowOpen())
		AuraRefineWindowClose();
#endif

// In the CHARACTER::SetPlayerProto after this:
	SetPart(PART_HAIR, t->parts[PART_HAIR]);

// Paste this:
#ifdef __AURA_SYSTEM__
	SetPart(PART_AURA, t->parts[PART_AURA]);
#endif

// In the CHARACTER::ComputeBattlePoints after this:
			if ((pkItem = GetWear(i)) && pkItem->GetType() == ITEM_ARMOR)
			{
				if (pkItem->GetSubType() == ARMOR_BODY || pkItem->GetSubType() == ARMOR_HEAD || pkItem->GetSubType() == ARMOR_FOOTS || pkItem->GetSubType() == ARMOR_SHIELD)
				{
					iArmor += pkItem->GetValue(1);
					iArmor += (2 * pkItem->GetValue(5));
				}
			}

// Paste this:
#ifdef __AURA_SYSTEM__
			else if (pkItem && pkItem->GetType() == ITEM_COSTUME && pkItem->GetSubType() == COSTUME_AURA)
			{
				const long c_lLevelSocket = pkItem->GetSocket(ITEM_SOCKET_AURA_CURRENT_LEVEL);
				const long c_lDrainSocket = pkItem->GetSocket(ITEM_SOCKET_AURA_DRAIN_ITEM_VNUM);
				const long c_lBoostSocket = pkItem->GetSocket(ITEM_SOCKET_AURA_BOOST);

				BYTE bCurLevel = (c_lLevelSocket / 100000) - 1000;
				BYTE bBoostIndex = c_lBoostSocket / 100000000;

				TItemTable* pBoosterProto = ITEM_MANAGER::instance().GetTable(ITEM_AURA_BOOST_ITEM_VNUM_BASE + bBoostIndex);
				float fAuraDrainPer = (1.0f * bCurLevel / 10.0f) / 100.0f;
				if (pBoosterProto)
					fAuraDrainPer += 1.0f * pBoosterProto->alValues[ITEM_AURA_BOOST_PERCENT_VALUE] / 100.0f;

				TItemTable* pDrainedItem = NULL;
				if (c_lDrainSocket != 0)
					pDrainedItem = ITEM_MANAGER::instance().GetTable(c_lDrainSocket);
				if (pDrainedItem != NULL && pDrainedItem->bType == ITEM_ARMOR && pDrainedItem->bSubType == ARMOR_SHIELD)
				{
					float fValue = (pDrainedItem->alValues[1] + (2 * pDrainedItem->alValues[5])) * fAuraDrainPer;
					iArmor += static_cast<int>((fValue < 1.0f) ? ceilf(fValue) : truncf(fValue));;
				}
			}
#endif

// Extend the CHARACTER::ComputePoints with the following where the rest parts are:
#ifdef __AURA_SYSTEM__
	SetPart(PART_AURA, GetOriginalPart(PART_AURA));
#endif

// Extend all the checks in the CHARACTER::OnClick function like this way:
				//PREVENT_TRADE_WINDOW
				if (pkChrCauser == this) // �ڱ�� ����
				{
					if ((GetExchange() || IsOpenSafebox() || GetShopOwner()) || IsCubeOpen()
#ifdef __AURA_SYSTEM__
						|| IsAuraRefineWindowOpen()
#endif

					)
					{
						pkChrCauser->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ���(â��,��ȯ,����)���� ���λ����� ����� �� �����ϴ�."));
						return;
					}
				}
				else // �ٸ� ����� Ŭ��������
				{
					// Ŭ���� ����� ��ȯ/â��/���λ���/�����̿����̶�� �Ұ�
					if (pkChrCauser->GetExchange() || pkChrCauser->IsOpenSafebox() || pkChrCauser->GetMyShop() || pkChrCauser->GetShopOwner() || pkChrCauser->IsCubeOpen()
#ifdef __AURA_SYSTEM__
						|| pkChrCauser->IsAuraRefineWindowOpen()
#endif
						)
					{
						pkChrCauser->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ���(â��,��ȯ,����)���� ���λ����� ����� �� �����ϴ�."));
						return;
					}

					// Ŭ���� ����� ��ȯ/â��/�����̿����̶�� �Ұ�
					//if ((GetExchange() || IsOpenSafebox() || GetShopOwner()))
					if (GetExchange() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
						|| IsAuraRefineWindowOpen()
#endif
					)
					{
						pkChrCauser->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("������ �ٸ� �ŷ��� �ϰ� �ִ� ���Դϴ�."));
						return;
					}
				}
				//END_PREVENT_TRADE_WINDOW

// Do the same in the CHARACTER::IsHack function too:
	if (bCheckShopOwner)
	{
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
		)
		{
			if (bSendMsg)
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ŷ�â,â�� ���� �� ���¿����� �ٸ������� �̵�,���� �Ҽ� �����ϴ�"));

			return true;
		}
	}
	else
	{
		if (GetExchange() || GetMyShop() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
		)
		{
			if (bSendMsg)
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ŷ�â,â�� ���� �� ���¿����� �ٸ������� �̵�,���� �Ҽ� �����ϴ�"));

			return true;
		}
	}

// And in the CHARACTER::CanWarp function too:
	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| IsAuraRefineWindowOpen()
#endif
	)
		return false;
