// In the CInputDB::SafeboxLoad function extend the trade prevent checks like this way:
	if (ch->GetShopOwner() || ch->GetExchange() || ch->GetMyShop() || ch->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| ch->IsAuraRefineWindowOpen()
#endif
		)
	{
		d->GetCharacter()->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ��ŷ�â�� �������¿����� â�� ������ �����ϴ�." ) );
		d->GetCharacter()->CancelSafeboxLoad();
		return;
	}
