// In the CHARACTER::ExchangeStart function extend the trade prevent checks like this way:
	if (IsOpenSafebox() || GetShopOwner() || GetMyShop() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| IsAuraRefineWindowOpen()
#endif
	)
	{
		ChatPacket( CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ�â�� ����������� �ŷ��� �Ҽ� �����ϴ�." ) );
		return false;
	}

	if (victim->IsOpenSafebox() || victim->GetShopOwner() || victim->GetMyShop() || victim->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| victim->IsAuraRefineWindowOpen()
#endif
	)
	{
		ChatPacket( CHAT_TYPE_INFO, LC_TEXT("������ �ٸ� �ŷ����̶� �ŷ��� �Ҽ� �����ϴ�." ) );
		return false;
	}
