// Add the following to the bottom of the CPythonPlayer::Clear function:
#ifdef ENABLE_AURA_SYSTEM
	m_AuraItemInstanceVector.clear();
	m_AuraItemInstanceVector.resize(AURA_SLOT_MAX);
	for (size_t i = 0; i < m_AuraItemInstanceVector.size(); ++i)
	{
		TItemData& rkAuraItemInstance = m_AuraItemInstanceVector[i];
		ZeroMemory(&rkAuraItemInstance, sizeof(TItemData));
	}

	m_bAuraWindowOpen = false;
	m_bOpenedAuraWindowType = AURA_WINDOW_TYPE_MAX;

	for (BYTE j = 0; j < AURA_SLOT_MAX; ++j)
		m_AuraRefineActivatedCell[j] = NPOS;

	ZeroMemory(&m_bAuraRefineInfo, sizeof(TAuraRefineInfo));
#endif

// Add the following functions anywhere you want to:
#ifdef ENABLE_AURA_SYSTEM
void CPythonPlayer::__ClearAuraRefineWindow()
{
	for (BYTE i = 0; i < AURA_SLOT_MAX; ++i)
	{
		if (!m_AuraRefineActivatedCell[i].IsNPOS())
		{
			//PyCallClassMemberFunc(m_ppyGameWindow, "DeactivateSlot", Py_BuildValue("(iii)", m_AuraRefineActivatedCell[i].window_type, m_AuraRefineActivatedCell[i].cell, SLOT_HIGHLIGHT_AURA));
			m_AuraRefineActivatedCell[i] = NPOS;
		}
	}
}

void CPythonPlayer::SetAuraRefineWindowOpen(BYTE wndType)
{
	m_bOpenedAuraWindowType = wndType;
	m_bAuraWindowOpen = AURA_WINDOW_TYPE_MAX != wndType;
	if (!m_bAuraWindowOpen)
		__ClearAuraRefineWindow();
}

bool CPythonPlayer::IsAuraRefineWindowEmpty()
{
	for (size_t i = 0; i < m_AuraItemInstanceVector.size(); ++i)
	{
		if (m_AuraItemInstanceVector[i].vnum)
			return false;
	}

	return true;
}

void CPythonPlayer::SetAuraRefineInfo(BYTE bAuraRefineInfoSlot, BYTE bAuraRefineInfoLevel, BYTE bAuraRefineInfoExpPercent)
{
	if (bAuraRefineInfoSlot >= AURA_REFINE_INFO_SLOT_MAX)
		return;

	m_bAuraRefineInfo[bAuraRefineInfoSlot].bAuraRefineInfoLevel = bAuraRefineInfoLevel;
	m_bAuraRefineInfo[bAuraRefineInfoSlot].bAuraRefineInfoExpPercent = bAuraRefineInfoExpPercent;
}

BYTE CPythonPlayer::GetAuraRefineInfoLevel(BYTE bAuraRefineInfoSlot)
{
	if (bAuraRefineInfoSlot >= AURA_REFINE_INFO_SLOT_MAX)
		return 0;

	return m_bAuraRefineInfo[bAuraRefineInfoSlot].bAuraRefineInfoLevel;
}

BYTE CPythonPlayer::GetAuraRefineInfoExpPct(BYTE bAuraRefineInfoSlot)
{
	if (bAuraRefineInfoSlot >= AURA_REFINE_INFO_SLOT_MAX)
		return 0;

	return m_bAuraRefineInfo[bAuraRefineInfoSlot].bAuraRefineInfoExpPercent;
}

void CPythonPlayer::SetAuraItemData(BYTE bySlotIndex, const TItemData& rItemInstance)
{
	if (bySlotIndex >= m_AuraItemInstanceVector.size())
	{
		TraceError("CPythonPlayer::SetAuraItemData(bySlotIndex=%u) - Strange slot index", bySlotIndex);
		return;
	}

	m_AuraItemInstanceVector[bySlotIndex] = rItemInstance;

	//if (bySlotIndex != AURA_SLOT_RESULT)
	//	PyCallClassMemberFunc(m_ppyGameWindow, "ActivateSlot", Py_BuildValue("(iii)", m_AuraRefineActivatedCell[bySlotIndex].window_type, m_AuraRefineActivatedCell[bySlotIndex].cell, SLOT_HIGHLIGHT_AURA));
}

void CPythonPlayer::DelAuraItemData(BYTE bySlotIndex)
{
	if (bySlotIndex >= AURA_SLOT_MAX || bySlotIndex >= (BYTE)m_AuraItemInstanceVector.size())
	{
		TraceError("CPythonPlayer::DelAuraItemData(bySlotIndex=%u) - Strange slot index", bySlotIndex);
		return;
	}

	TItemData& rInstance = m_AuraItemInstanceVector[bySlotIndex];
	CItemData* pItemData;
	if (CItemManager::instance().GetItemDataPointer(rInstance.vnum, &pItemData))
	{
		if (bySlotIndex == AURA_SLOT_MAIN || bySlotIndex == AURA_SLOT_SUB)
			DelAuraItemData(AURA_SLOT_RESULT);

		if (bySlotIndex != AURA_SLOT_RESULT)
		{
			//PyCallClassMemberFunc(m_ppyGameWindow, "DeactivateSlot", Py_BuildValue("(iii)", m_AuraRefineActivatedCell[bySlotIndex].window_type, m_AuraRefineActivatedCell[bySlotIndex].cell, SLOT_HIGHLIGHT_AURA));
			m_AuraRefineActivatedCell[bySlotIndex] = NPOS;
		}

		ZeroMemory(&rInstance, sizeof(TItemData));
	}
}

BYTE CPythonPlayer::FineMoveAuraItemSlot()
{
	for (size_t i = 0; i < m_AuraItemInstanceVector.size(); ++i)
	{
		if (!m_AuraItemInstanceVector[i].vnum)
			return (BYTE)i;
	}

	return AURA_SLOT_MAX;
}

BYTE CPythonPlayer::GetAuraCurrentItemSlotCount()
{
	BYTE bCurCount = 0;
	for (BYTE i = 0; i < AURA_SLOT_MAX; ++i)
	{
		if (m_AuraItemInstanceVector[i].vnum)
			++bCurCount;
	}

	return bCurCount;
}

BOOL CPythonPlayer::GetAuraItemDataPtr(BYTE bySlotIndex, TItemData** ppInstance)
{
	if (bySlotIndex >= m_AuraItemInstanceVector.size())
	{
		TraceError("CPythonPlayer::GetAuraItemDataPtr(bySlotIndex=%u) - Strange slot index", bySlotIndex);
		return FALSE;
	}

	*ppInstance = &m_AuraItemInstanceVector[bySlotIndex];

	return TRUE;
}

void CPythonPlayer::SetActivatedAuraSlot(BYTE bySlotIndex, TItemPos ItemCell)
{
	if (bySlotIndex >= AURA_SLOT_MAX)
		return;

	m_AuraRefineActivatedCell[bySlotIndex] = ItemCell;
}

BYTE CPythonPlayer::FindActivatedAuraSlot(TItemPos ItemCell)
{
	for (BYTE i = AURA_SLOT_MAIN; i < AURA_SLOT_MAX; ++i)
	{
		if (m_AuraRefineActivatedCell[i] == ItemCell)
			return BYTE(i);
	}

	return AURA_SLOT_MAX;
}

TItemPos CPythonPlayer::FindUsingAuraSlot(BYTE bySlotIndex)
{
	if (bySlotIndex >= AURA_SLOT_MAX)
		return NPOS;

	return m_AuraRefineActivatedCell[bySlotIndex];
}
#endif
