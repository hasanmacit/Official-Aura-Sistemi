// In the Cube_open extend the trade prvent checks like this way:
	if (ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen()
#ifdef __AURA_SYSTEM__
		|| ch->IsAuraRefineWindowOpen()
#endif
		)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ٸ� �ŷ���(â��,��ȯ,����)���� ����� �� �����ϴ�."));
		return;
	}
