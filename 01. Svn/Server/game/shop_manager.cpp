// In the CShopManager::StartShopping extend the trade prevent checks like this way:
	if (pkChr->IsOpenSafebox() || pkChr->GetExchange() || pkChr->GetMyShop() || pkChr->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| pkChr->IsAuraRefineWindowOpen()
#endif
	)
	{
		pkChr->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("다른 거래창이 열린상태에서는 상점거래를 할수 가 없습니다."));
		return false;
	}
