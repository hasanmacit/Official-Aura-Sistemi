// Extend the types of the costumes in the ECostumeSubTypes enum, make sure everywhere it has the same value, be careful with commas!
#ifdef __AURA_SYSTEM__
	COSTUME_AURA,
#endif

// Extend the types of the resources in the EResourceSubTypes enum, make sure everywhere it has the same value!
#ifdef __AURA_SYSTEM__
	RESOURCE_AURA
#endif

// Extend the types of the use items in the EUseSubTypes enum, make sure everywhere it has the same value!
#ifdef __AURA_SYSTEM__
	USE_PUT_INTO_AURA_SOCKET,			// xx AURA_BOOSTER
#endif

// Add the followings anywhere you want to:
#ifdef __AURA_SYSTEM__
enum EItemAuraSockets
{
	ITEM_SOCKET_AURA_DRAIN_ITEM_VNUM,
	ITEM_SOCKET_AURA_CURRENT_LEVEL,
	ITEM_SOCKET_AURA_BOOST,
};

enum EItemAuraMaterialValues
{
	ITEM_AURA_MATERIAL_EXP_VALUE,
};

enum EItemAuraBoostValues
{
	ITEM_AURA_BOOST_PERCENT_VALUE,
	ITEM_AURA_BOOST_TIME_VALUE,
	ITEM_AURA_BOOST_UNLIMITED_VALUE,
};

enum EItemAuraBoostIndex
{
	ITEM_AURA_BOOST_ERASER,
	ITEM_AURA_BOOST_WEAK,
	ITEM_AURA_BOOST_NORMAL,
	ITEM_AURA_BOOST_STRONG,
	ITEM_AURA_BOOST_ULTIMATE,
	ITEM_AURA_BOOST_MAX,
};
#endif

