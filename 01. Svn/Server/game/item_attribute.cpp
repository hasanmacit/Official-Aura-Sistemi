// Make the function to look like this: (!Can be different!)
int CItem::GetAttributeSetIndex()
{
	if (GetType() == ITEM_WEAPON)
	{
		if (GetSubType() == WEAPON_ARROW)
			return -1;

		return ATTRIBUTE_SET_WEAPON;
	}

#ifdef __AURA_SYSTEM__
	if (GetType() == ITEM_COSTUME && GetSubType() == COSTUME_AURA)
		return -1;
#endif

	if (GetType() == ITEM_ARMOR || GetType() == ITEM_COSTUME)
	{
		switch (GetSubType())
		{
			case ARMOR_BODY:
//			case COSTUME_BODY: // �ڽ��� ������ �Ϲ� ���ʰ� ������ Attribute Set�� �̿��Ͽ� �����Ӽ� ���� (ARMOR_BODY == COSTUME_BODY)
				return ATTRIBUTE_SET_BODY;

			case ARMOR_WRIST:
				return ATTRIBUTE_SET_WRIST;

			case ARMOR_FOOTS:
				return ATTRIBUTE_SET_FOOTS;

			case ARMOR_NECK:
				return ATTRIBUTE_SET_NECK;

			case ARMOR_HEAD:
//			case COSTUME_HAIR: // �ڽ��� ���� �Ϲ� ���� �����۰� ������ Attribute Set�� �̿��Ͽ� �����Ӽ� ���� (ARMOR_HEAD == COSTUME_HAIR)
				return ATTRIBUTE_SET_HEAD;

			case ARMOR_SHIELD:
				return ATTRIBUTE_SET_SHIELD;

			case ARMOR_EAR:
				return ATTRIBUTE_SET_EAR;
		}
	}

	return -1;
}
