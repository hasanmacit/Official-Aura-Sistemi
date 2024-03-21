// Add the following to the constructor of the CItem like this way:
CItem::CItem(DWORD dwVnum)
	: m_dwVnum(dwVnum), m_bWindow(0), m_dwID(0), m_bEquipped(false), m_dwVID(0), m_wCell(0), m_dwCount(0), m_lFlag(0), m_dwLastOwnerPID(0),
	m_bExchanging(false), m_pkDestroyEvent(NULL), m_pkUniqueExpireEvent(NULL), m_pkTimerBasedOnWearExpireEvent(NULL), m_pkRealTimeExpireEvent(NULL),
	m_pkExpireEvent(NULL),
   	m_pkAccessorySocketExpireEvent(NULL), m_pkOwnershipEvent(NULL), m_dwOwnershipPID(0), m_bSkipSave(false), m_isLocked(false),
	m_dwMaskVnum(0), m_dwSIGVnum (0)
#ifdef __AURA_SYSTEM__
	, m_pkAuraBoostSocketExpireEvent(NULL)
#endif
{
	memset( &m_alSockets, 0, sizeof(m_alSockets) );
	memset( &m_aAttr, 0, sizeof(m_aAttr) );
}

// Add the bottom of the CItem::Initialize function this:
#ifdef __AURA_SYSTEM__
	m_pkAuraBoostSocketExpireEvent = NULL;
#endif

// Extend the CItem::Destroy function where the rest events are being cancelled:
#ifdef __AURA_SYSTEM__
	event_cancel(&m_pkAuraBoostSocketExpireEvent);
#endif

// Extend the CItem::FindEquipCell for auras like this way:
	else if (GetType() == ITEM_COSTUME)
	{
		if (GetSubType() == COSTUME_BODY)
			return WEAR_COSTUME_BODY;
		else if (GetSubType() == COSTUME_HAIR)
			return WEAR_COSTUME_HAIR;
#ifdef __AURA_SYSTEM__
		else if (GetSubType() == COSTUME_AURA)
			return WEAR_COSTUME_AURA;
#endif
	}

// In the CItem::ModifyPoints function find this code part:
	for (int i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
	{
		if (m_pProto->aApplies[i].bType == APPLY_NONE)
			continue;

		long value = m_pProto->aApplies[i].lValue;

		if (m_pProto->aApplies[i].bType == APPLY_SKILL)
		{
			m_pOwner->ApplyPoint(m_pProto->aApplies[i].bType, bAdd ? value : value ^ 0x00800000);
		}
		else
		{
			if (0 != accessoryGrade)
				value += MAX(accessoryGrade, value * aiAccessorySocketEffectivePct[accessoryGrade] / 100);

			m_pOwner->ApplyPoint(m_pProto->aApplies[i].bType, bAdd ? value : -value);
		}
	}

// And add below of it the following:
#ifdef __AURA_SYSTEM__
	float fAuraDrainPer = 0.0f;
	if (m_pProto->bType == ITEM_COSTUME && m_pProto->bSubType == COSTUME_AURA)
	{
		const long c_lLevelSocket = GetSocket(ITEM_SOCKET_AURA_CURRENT_LEVEL);
		const long c_lDrainSocket = GetSocket(ITEM_SOCKET_AURA_DRAIN_ITEM_VNUM);
		const long c_lBoostSocket = GetSocket(ITEM_SOCKET_AURA_BOOST);

		BYTE bCurLevel = (c_lLevelSocket / 100000) - 1000;
		BYTE bBoostIndex = c_lBoostSocket / 100000000;

		TItemTable* pBoosterProto = ITEM_MANAGER::instance().GetTable(ITEM_AURA_BOOST_ITEM_VNUM_BASE + bBoostIndex);
		fAuraDrainPer = (1.0f * bCurLevel / 10.0f) / 100.0f;
		if (pBoosterProto)
			fAuraDrainPer += 1.0f * pBoosterProto->alValues[ITEM_AURA_BOOST_PERCENT_VALUE] / 100.0f;

		TItemTable* p = NULL;
		if (c_lDrainSocket != 0)
			p = ITEM_MANAGER::instance().GetTable(c_lDrainSocket);

		if (p != NULL && (ITEM_ARMOR == p->bType && (ARMOR_SHIELD == p->bSubType || ARMOR_WRIST == p->bSubType || ARMOR_NECK == p->bSubType || ARMOR_EAR == p->bSubType)))
		{
			for (int i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
			{
				if (p->aApplies[i].bType == APPLY_NONE || /*p->aApplies[i].bType == APPLY_MOUNT || */p->aApplies[i].bType == APPLY_MOV_SPEED || p->aApplies[i].lValue <= 0)
					continue;

				float fValue = p->aApplies[i].lValue * fAuraDrainPer;
				int iValue = static_cast<int>((fValue < 1.0f) ? ceilf(fValue) : truncf(fValue));
				if (p->aApplies[i].bType == APPLY_SKILL)
					m_pOwner->ApplyPoint(p->aApplies[i].bType, bAdd ? iValue : iValue ^ 0x00800000);
				else
					m_pOwner->ApplyPoint(p->aApplies[i].bType, bAdd ? iValue : -iValue);
			}
		}
	}
#endif

// Next is a bit complicated. Find the following part and compare it to yours make if fit together with the sash
		for (int i = 0; i < ITEM_ATTRIBUTE_MAX_NUM; ++i)
		{
			if (GetAttributeType(i))
			{
				const TPlayerItemAttribute& ia = GetAttribute(i);
#ifdef __AURA_SYSTEM__
				if (ia.bType == APPLY_SKILL)
				{
					if (m_pProto->bType == ITEM_COSTUME && m_pProto->bSubType == COSTUME_AURA)
					{
						if (ia.sValue <= 0)
							continue;

						float fValue = ia.sValue * fAuraDrainPer;
						int iValue = static_cast<int>((fValue < 1.0f) ? ceilf(fValue) : truncf(fValue));
						m_pOwner->ApplyPoint(ia.bType, bAdd ? iValue : iValue ^ 0x00800000);
					}
					else
						m_pOwner->ApplyPoint(ia.bType, bAdd ? ia.sValue : ia.sValue ^ 0x00800000);
				}
				else
				{
					if (m_pProto->bType == ITEM_COSTUME && m_pProto->bSubType == COSTUME_AURA)
					{
						if (ia.sValue <= 0)
							continue;

						float fValue = ia.sValue * fAuraDrainPer;
						int iValue = static_cast<int>((fValue < 1.0f) ? ceilf(fValue) : truncf(fValue));
						m_pOwner->ApplyPoint(ia.bType, bAdd ? iValue : -iValue);
					}
					else
						m_pOwner->ApplyPoint(ia.bType, bAdd ? ia.sValue : -ia.sValue);
				}
#else
				if (ia.bType == APPLY_SKILL)
					m_pOwner->ApplyPoint(ia.bType, bAdd ? ia.sValue : ia.sValue ^ 0x00800000);
				else
					m_pOwner->ApplyPoint(ia.bType, bAdd ? ia.sValue : -ia.sValue);
#endif
			}
		}
	}

// Below a bit add the aura subtype
		case ITEM_COSTUME:
			{
				DWORD toSetValue = this->GetVnum();
				EParts toSetPart = PART_MAX_NUM;

				// 갑옷 코스츔
				if (GetSubType() == COSTUME_BODY)
				{
					toSetPart = PART_MAIN;

					if (false == bAdd)
					{
						// 코스츔 갑옷을 벗었을 때 원래 갑옷을 입고 있었다면 그 갑옷으로 look 세팅, 입지 않았다면 default look
						const CItem* pArmor = m_pOwner->GetWear(WEAR_BODY);
						toSetValue = (NULL != pArmor) ? pArmor->GetVnum() : m_pOwner->GetOriginalPart(PART_MAIN);						
					}
					
				}

				// 헤어 코스츔
				else if (GetSubType() == COSTUME_HAIR)
				{
					toSetPart = PART_HAIR;

					// 코스츔 헤어는 shape값을 item proto의 value3에 세팅하도록 함. 특별한 이유는 없고 기존 갑옷(ARMOR_BODY)의 shape값이 프로토의 value3에 있어서 헤어도 같이 value3으로 함.
					// [NOTE] 갑옷은 아이템 vnum을 보내고 헤어는 shape(value3)값을 보내는 이유는.. 기존 시스템이 그렇게 되어있음...
					toSetValue = (true == bAdd) ? this->GetValue(3) : 0;
				}
#ifdef __AURA_SYSTEM__
				else if (GetSubType() == COSTUME_AURA)
				{
					if (m_wCell == INVENTORY_MAX_NUM + WEAR_COSTUME_AURA)
						m_pOwner->SetPart(PART_AURA, bAdd ? GetVnum() : m_pOwner->GetOriginalPart(PART_AURA));
				}
#endif

// In the CItem::EquipTo function find the following:
		// ACCESSORY_REFINE
		StartAccessorySocketExpireEvent();
		// END_OF_ACCESSORY_REFINE

// And add below:
#ifdef __AURA_SYSTEM__
		StartAuraBoosterSocketExpireEvent();
#endif

// In the CItem::Unequip function find the following:
	// ACCESSORY_REFINE
	StopAccessorySocketExpireEvent();
	// END_OF_ACCESSORY_REFINE

// And add below:
#ifdef __AURA_SYSTEM__
	StopAuraBoosterSocketExpireEvent();
#endif

// In the  CItem::AlterToMagicItem function extend the ITEM_COSTUME case with:
#ifdef __AURA_SYSTEM__
				else if (GetType() == ITEM_COSTUME && GetSubType() == COSTUME_AURA)
				{
					iSecondPct = 0;
					iThirdPct = 0;
				}
#endif

// Extend the CItem::CanPutInto function like this way:
{
	if (item->GetType() == ITEM_BELT)
		return this->GetSubType() == USE_PUT_INTO_BELT_SOCKET;

	else if(item->GetType() == ITEM_RING)
		return CanPutIntoRing(item, this);

#ifdef __AURA_SYSTEM__
	else if (item->GetType() == ITEM_COSTUME && item->GetSubType() == COSTUME_AURA)
		return this->GetSubType() == USE_PUT_INTO_AURA_SOCKET;
#endif

	else if (item->GetType() != ITEM_ARMOR)
		return false;

// Add the followings anywhere you want to:
#ifdef __AURA_SYSTEM__
bool CItem::IsAuraBoosterForSocket()
{
	if (m_pProto->bType == ITEM_COSTUME && m_pProto->bSubType == COSTUME_AURA)
		return this->GetSocket(ITEM_SOCKET_AURA_BOOST) == 0;

	return false;
}

EVENTFUNC(aura_boost_socket_expire_event)
{
	item_event_info* info = dynamic_cast<item_event_info*>(event->info);
	if (info == NULL)
	{
		sys_err("aura_boost_socket_expire_event> <Factor> Null pointer");
		return 0;
	}

	LPITEM pkAura = info->item;
	const long c_lBoosterSocket = pkAura->GetSocket(ITEM_SOCKET_AURA_BOOST);
	const long c_lBoosterIndex = c_lBoosterSocket / 100000000;
	if (c_lBoosterIndex <= ITEM_AURA_BOOST_ERASER || c_lBoosterIndex >= ITEM_AURA_BOOST_MAX)
		return 0;

	DWORD dwBoosterItemVnum = ITEM_AURA_BOOST_ITEM_VNUM_BASE + c_lBoosterIndex;
	TItemTable* pBoosterProto = ITEM_MANAGER::instance().GetTable(dwBoosterItemVnum);
	if (!pBoosterProto)
		return 0;

	if (pBoosterProto->alValues[ITEM_AURA_BOOST_UNLIMITED_VALUE] == 1)
		return 0;

	long lBoostTimeSec = (c_lBoosterSocket % 100000000) - processing_time / passes_per_sec;
	if (lBoostTimeSec <= 0)
	{
		sys_log(0, "AURA BOOST EXPIRED : expired %s %lu", pkAura->GetName(), pkAura->GetID());
		pkAura->SetAuraBoosterSocketExpireEvent(NULL);
		pkAura->ModifyPoints(false);
		pkAura->SetSocket(ITEM_SOCKET_AURA_BOOST, 0);
		pkAura->ModifyPoints(true);
		if (pkAura->GetOwner())
		{
			pkAura->GetOwner()->ComputeBattlePoints();
			pkAura->GetOwner()->UpdatePacket();
		}

		LogManager::instance().ItemLog(pkAura->GetOwner(), pkAura, "AURA_BOOST_EXPIRED", pkAura->GetName());

		return 0;
	}

	pkAura->SetSocket(ITEM_SOCKET_AURA_BOOST, c_lBoosterIndex * 100000000 + lBoostTimeSec);
	return PASSES_PER_SEC(MIN(60, lBoostTimeSec));
}

void CItem::StartAuraBoosterSocketExpireEvent()
{
	if (!(m_pProto->bType == ITEM_COSTUME && m_pProto->bSubType == COSTUME_AURA))
		return;

	if (GetSocket(ITEM_SOCKET_AURA_BOOST) == 0)
		return;

	if (m_pkAuraBoostSocketExpireEvent)
		return;

	const long c_lBoosterSocket = GetSocket(ITEM_SOCKET_AURA_BOOST);
	const long c_lBoosterIndex = c_lBoosterSocket / 100000000;
	if (c_lBoosterIndex <= ITEM_AURA_BOOST_ERASER || c_lBoosterIndex >= ITEM_AURA_BOOST_MAX)
		return;

	DWORD dwBoosterItemVnum = ITEM_AURA_BOOST_ITEM_VNUM_BASE + c_lBoosterIndex;
	TItemTable* pBoosterProto = ITEM_MANAGER::instance().GetTable(dwBoosterItemVnum);
	if (!pBoosterProto)
		return;

	if (pBoosterProto->alValues[ITEM_AURA_BOOST_UNLIMITED_VALUE] == 1)
		return;

	long lBoostTimeSec = c_lBoosterSocket % 100000000;
	if (0 != lBoostTimeSec)
	{
		lBoostTimeSec %= 60;
		if (0 == lBoostTimeSec)
			lBoostTimeSec = 60;
	}

	item_event_info* info = AllocEventInfo<item_event_info>();
	info->item = this;

	SetAuraBoosterSocketExpireEvent(event_create(aura_boost_socket_expire_event, info, PASSES_PER_SEC(lBoostTimeSec)));
}

void CItem::StopAuraBoosterSocketExpireEvent()
{
	if (!m_pkAuraBoostSocketExpireEvent)
		return;

	const long c_lBoosterSocket = GetSocket(ITEM_SOCKET_AURA_BOOST);
	const long c_lBoosterIndex = c_lBoosterSocket / 100000000;
	if (c_lBoosterIndex <= ITEM_AURA_BOOST_ERASER || c_lBoosterIndex >= ITEM_AURA_BOOST_MAX)
		return;

	DWORD dwBoosterItemVnum = ITEM_AURA_BOOST_ITEM_VNUM_BASE + c_lBoosterIndex;
	TItemTable* pBoosterProto = ITEM_MANAGER::instance().GetTable(dwBoosterItemVnum);
	if (!pBoosterProto)
		return;

	long lBoostTimeSec = (c_lBoosterSocket % 100000000) - event_processing_time(m_pkAuraBoostSocketExpireEvent) / passes_per_sec;
	SetSocket(ITEM_SOCKET_AURA_BOOST, c_lBoosterIndex * 100000000 + lBoostTimeSec);
	event_cancel(&m_pkAuraBoostSocketExpireEvent);

	ITEM_MANAGER::instance().SaveSingleItem(this);
}

void CItem::SetAuraBoosterSocketExpireEvent(LPEVENT pkEvent)
{
	m_pkAuraBoostSocketExpireEvent = pkEvent;
}
#endif
