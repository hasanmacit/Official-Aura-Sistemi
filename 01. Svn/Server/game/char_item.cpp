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
							// 무시무시하지만 이전에 하던 걸 고치기는 무섭고...
							// 그래서 그냥 하드 코딩. 선물 상자용 자동물약 아이템들.
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
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<아우라> 당신의 영혼에 묶여 있기 때문에 당신의 아우라 의상에서 부스트를 지울 수 없습니다."));
										return false;
									}
#endif

									if (item2->GetSocket(ITEM_SOCKET_AURA_BOOST) == 0)
									{
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<아우라> 오라 의상에는 부스트가 없습니다."));
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
							// [NOTE] 코스튬 아이템에는 아이템 최초 생성시 랜덤 속성을 부여하되, 재경재가 등등은 막아달라는 요청이 있었음.
							// 원래 ANTI_CHANGE_ATTRIBUTE 같은 아이템 Flag를 추가하여 기획 레벨에서 유연하게 컨트롤 할 수 있도록 할 예정이었으나
							// 그딴거 필요없으니 닥치고 빨리 해달래서 그냥 여기서 막음... -_-
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
								ChatPacket(CHAT_TYPE_INFO, LC_TEXT("속성을 변경할 수 없는 아이템입니다."));
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

										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<아우라> 오라 부스터가 성공적으로 연결되었습니다."));

										LogManager::instance().ItemLog(this, item, "PUT_AURA_SOCKET", buf);

										if (IS_SET(item->GetFlag(), ITEM_FLAG_STACKABLE) && !IS_SET(item->GetAntiFlag(), ITEM_ANTIFLAG_STACK) && item->GetCount() > 1)
											item->SetCount(item->GetCount() - 1);
										else
											ITEM_MANAGER::instance().RemoveItem(item, "PUT_AURA_SOCKET_REMOVE");
									}
									else
										ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<아우라> 이 아이템에 오라 부스트를 추가 할 수 없습니다."));
								}
								break;
#endif

// In the CHARACTER::UseItem function extend the prevent trade checks like this way:
		//거래관련 창 체크
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
		)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("거래창,창고 등을 연 상태에서는 귀환부,귀환기억부 를 사용할수 없습니다."));
			return false;
		}

// Same function, a bit below:
	//보따리 비단 사용시 거래창 제한 체크 
	if (item->GetVnum() == 50200 | item->GetVnum() == 71049)
	{
		if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen()
#ifdef __AURA_SYSTEM__
			|| IsAuraRefineWindowOpen()
#endif
			)
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("거래창,창고 등을 연 상태에서는 보따리,비단보따리를 사용할수 없습니다."));
			return false;
		}

	}

// In the CHARACTER::MoveItem function make this check like this way:
	if (!CanHandleItem())
	{
		if (NULL != DragonSoul_RefineWindow_GetOpener())
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("강화창을 연 상태에서는 아이템을 옮길 수 없습니다."));
#ifdef __AURA_SYSTEM__
		if (IsAuraRefineWindowOpen())
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<아우라> 오라 창이 열려있을 때까지 항목을 이동할 수 없습니다."));
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
