// In the CShopManager::StartShopping extend the trade prevent checks like this way:
	if (pkChr->IsOpenSafebox() || pkChr->GetExchange() || pkChr->GetMyShop() || pkChr->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| pkChr->IsAuraRefineWindowOpen()
#endif
	)
	{
		pkChr->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ�â�� �������¿����� �����ŷ��� �Ҽ� �� �����ϴ�."));
		return false;
	}
