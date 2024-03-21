// In the CHARACTER::ExchangeStart function extend the trade prevent checks like this way:
	if (IsOpenSafebox() || GetShopOwner() || GetMyShop() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| IsAuraRefineWindowOpen()
#endif
	)
	{
		ChatPacket( CHAT_TYPE_INFO, LC_TEXT("다른 거래창이 열려있을경우 거래를 할수 없습니다." ) );
		return false;
	}

	if (victim->IsOpenSafebox() || victim->GetShopOwner() || victim->GetMyShop() || victim->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| victim->IsAuraRefineWindowOpen()
#endif
	)
	{
		ChatPacket( CHAT_TYPE_INFO, LC_TEXT("상대방이 다른 거래중이라 거래를 할수 없습니다." ) );
		return false;
	}
