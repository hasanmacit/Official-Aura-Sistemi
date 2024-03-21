// Extend the CHARACTER::CanHandleItem function with the following (before the return true;!):
#ifdef __AURA_SYSTEM__
	if (IsAuraRefineWindowOpen() || NULL != GetAuraRefineWindowOpener())
		return false;
#endif

// After these cases: <!Be careful!>
							case ITEM_AUTO_HP_RECOVERY_S:
							case ITEM_AUTO_HP_RECOVERY_M:
							case ITEM_AUTO_HP_RECOVERY_L:
							case ITEM_AUTO_HP_RECOVERY_X:
							case ITEM_AUTO_SP_RECOVERY_S:
							case ITEM_AUTO_SP_RECOVERY_M:
							case ITEM_AUTO_SP_RECOVERY_L:
							case ITEM_AUTO_SP_RECOVERY_X:
							// ���ù��������� ������ �ϴ� �� ��ġ��� ������...
							// �׷��� �׳� �ϵ� �ڵ�. ���� ���ڿ� �ڵ����� �����۵�.
							case REWARD_BOX_ITEM_AUTO_SP_RECOVERY_XS: 
							case REWARD_BOX_ITEM_AUTO_SP_RECOVERY_S: 
							case REWARD_BOX_ITEM_AUTO_HP_RECOVERY_XS: 
							case REWARD_BOX_ITEM_AUTO_HP_RECOVERY_S:
							case FUCKING_BRAZIL_ITEM_AUTO_SP_RECOVERY_S:
							case FUCKING_BRAZIL_ITEM_AUTO_HP_RECOVERY_S:
								{
								}
								break;

// Add this:
#ifdef __AURA_SYSTEM__
							case ITEM_AURA_BOOST_ITEM_VNUM_BASE + ITEM_AURA_BOOST_ERASER:
								{
									LPITEM item2;
									if (!IsValidItemPosition(DestCell) || !(item2 = GetItem(DestCell)))
										return false;

									if (item2->IsExchanging() || item2->IsEquipped())
										return false;

#ifdef ENABLE_SEALBIND_SYSTEM
									if (item2->IsBound())
									{
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<�ƿ��> ����� ��ȥ�� ���� �ֱ� ������ ����� �ƿ�� �ǻ󿡼� �ν�Ʈ�� ���� �� �����ϴ�."));
										return false;
									}
#endif

									if (item2->GetSocket(ITEM_SOCKET_AURA_BOOST) == 0)
									{
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<�ƿ��> ���� �ǻ󿡴� �ν�Ʈ�� �����ϴ�."));
										return false;
									}

									if (IS_SET(item->GetFlag(), ITEM_FLAG_STACKABLE) && !IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_STACK) && item->GetCount() > 1)
										item->SetCount(item->GetCount() - 1);
									else
										ITEM_MANAGER::instance().RemoveItem(item);

									item2->SetSocket(ITEM_SOCKET_AURA_BOOST, 0);
								}
								break;
#endif

// After these ones:
					case USE_PUT_INTO_BELT_SOCKET:
					case USE_PUT_INTO_RING_SOCKET:
					case USE_PUT_INTO_ACCESSORY_SOCKET:
					case USE_ADD_ACCESSORY_SOCKET:
					case USE_CLEAN_SOCKET:
					case USE_CHANGE_ATTRIBUTE:
					case USE_CHANGE_ATTRIBUTE2 :
					case USE_ADD_ATTRIBUTE:
					case USE_ADD_ATTRIBUTE2:

// Add this:
#ifdef __AURA_SYSTEM__
					case USE_PUT_INTO_AURA_SOCKET:
#endif

// A bit below of that, after this:
							// [NOTE] �ڽ�Ƭ �����ۿ��� ������ ���� ������ ���� �Ӽ��� �ο��ϵ�, ����簡 ����� ���ƴ޶�� ��û�� �־���.
							// ���� ANTI_CHANGE_ATTRIBUTE ���� ������ Flag�� �߰��Ͽ� ��ȹ �������� �����ϰ� ��Ʈ�� �� �� �ֵ��� �� �����̾�����
							// �׵��� �ʿ������ ��ġ�� ���� �ش޷��� �׳� ���⼭ ����... -_-
							if (ITEM_COSTUME == item2->GetType())

// Add this:
#ifdef __AURA_SYSTEM__
							if (item->GetSubType() != USE_PUT_INTO_AURA_SOCKET)
#endif
// So just to be clear:
							if (ITEM_COSTUME == item2->GetType())
#ifdef __AURA_SYSTEM__
							if (item->GetSubType() != USE_PUT_INTO_AURA_SOCKET)
#endif
							{
								ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�Ӽ��� ������ �� ���� �������Դϴ�."));
								return false;
							}

// Then below after these cases: <!Be careful!>
								case USE_PUT_INTO_BELT_SOCKET:
								case USE_PUT_INTO_ACCESSORY_SOCKET:
									if (item2->IsAccessoryForSocket() && item->CanPutInto(item2))
									{
									}
									else
									{
									}
									break;

// Add this:
#ifdef __AURA_SYSTEM__
								case USE_PUT_INTO_AURA_SOCKET:
								{
									if (item2->IsAuraBoosterForSocket() && item->CanPutInto(item2))
									{
										char buf[21];
										snprintf(buf, sizeof(buf), "%lu", item2->GetID());

										const BYTE c_bAuraBoostIndex = item->GetOriginalVnum() - ITEM_AURA_BOOST_ITEM_VNUM_BASE;
										item2->SetSocket(ITEM_SOCKET_AURA_BOOST, c_bAuraBoostIndex * 100000000 + item->GetValue(ITEM_AURA_BOOST_TIME_VALUE));

										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<�ƿ��> ���� �ν��Ͱ� ���������� ����Ǿ����ϴ�."));

										LogManager::instance().ItemLog(this, item, "PUT_AURA_SOCKET", buf);

										if (IS_SET(item->GetFlag(), ITEM_FLAG_STACKABLE) && !IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_STACK) && item->GetCount() > 1)
											item->SetCount(item->GetCount() - 1);
										else
											ITEM_MANAGER::instance().RemoveItem(item, "PUT_AURA_SOCKET_REMOVE");
									}
									else
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<�ƿ��> �� �����ۿ� ���� �ν�Ʈ�� �߰� �� �� �����ϴ�."));
								}
								break;
#endif

// In the CHARACTER::UseItem function extend the prevent trade checks like this way:
		//�ŷ����� â üũ
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
		)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ŷ�â,â�� ���� �� ���¿����� ��ȯ��,��ȯ���� �� ����Ҽ� �����ϴ�."));
			return false;
		}

// Same function, a bit below:
	//������ ��� ���� �ŷ�â ���� üũ 
	if (item->GetVnum() == 50200 | item->GetVnum() == 71049)
	{
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
			)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ŷ�â,â�� ���� �� ���¿����� ������,��ܺ������� ����Ҽ� �����ϴ�."));
			return false;
		}

	}

// In the CHARACTER::MoveItem function make this check like this way:
	if (!CanHandleItem())
	{
		if (NULL != DragonSoul_RefineWindow_GetOpener())
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("��ȭâ�� �� ���¿����� �������� �ű� �� �����ϴ�."));
#ifdef __AURA_SYSTEM__
		if (IsAuraRefineWindowOpen())
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<�ƿ��> ���� â�� �������� ������ �׸��� �̵��� �� �����ϴ�."));
#endif
		return false;
	}

// Extend the function CHARACTER::CanDoCube with:
#ifdef __AURA_SYSTEM__
	if (IsAuraRefineWindowOpen())	return false;
#endif

// Extend the function CHARACTER::CanUnequipNow with:
#ifdef __AURA_SYSTEM__
	if (IsAuraRefineWindowOpen())
		return false;
#endif
