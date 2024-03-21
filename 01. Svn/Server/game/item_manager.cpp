// In the ITEM_MANAGER::CreateItem function before returning the item add the following:
#ifdef __AURA_SYSTEM__
	if (item->GetType() == ITEM_COSTUME && item->GetSubType() == COSTUME_AURA)
	{
		const BYTE c_bGrade = item->GetOriginalVnum() % 10;
		const BYTE c_bBaseLevel = GetAuraRefineInfo(c_bGrade, AURA_REFINE_INFO_LEVEL_MIN);
		const WORD c_wBaseExp = 0;
		item->SetSocket(ITEM_SOCKET_AURA_CURRENT_LEVEL, (1000 + c_bBaseLevel) * 100000 + c_wBaseExp);
	}
#endif
