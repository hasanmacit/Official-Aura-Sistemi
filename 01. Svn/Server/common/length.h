// Extend the EWearPositions enum with the new aura, but make sure the value of it will match to the clientside in GameType.h!
#ifdef __AURA_SYSTEM__
	WEAR_COSTUME_AURA,
#endif

// Extend the EParts enum with the new aura part, but make sure the value of it will be the same as it is on clientside!
#ifdef __AURA_SYSTEM__
	PART_AURA,
#endif

// Extend the EWindows enum with the new aura window, but make sure the value of it will be the same as it is on clientside!
#ifdef __AURA_SYSTEM__
	AURA_REFINE,
#endif

// Add the != operator function into the TItemPos struct:
	bool operator!=(const struct SItemPos& rhs) const
	{
		return (window_type != rhs.window_type) || (cell != rhs.cell);
	}

// Add anywhere you want but before the #pragma pack(pop)
#ifdef __AURA_SYSTEM__
typedef struct SAuraRefineInfo
{
	BYTE bAuraRefineInfoLevel;
	BYTE bAuraRefineInfoExpPercent;
} TAuraRefineInfo;

enum EAuraMisc
{
	AURA_MAX_LEVEL = 250,
	AURA_REFINE_MAX_DISTANCE = 1000,
};

enum EAuraWindowType
{
	AURA_WINDOW_TYPE_ABSORB,
	AURA_WINDOW_TYPE_GROWTH,
	AURA_WINDOW_TYPE_EVOLVE,
	AURA_WINDOW_TYPE_MAX,
};

enum EAuraSlotType
{
	AURA_SLOT_MAIN,
	AURA_SLOT_SUB,
	AURA_SLOT_RESULT,
	AURA_SLOT_MAX
};

enum EAuraGradeType
{
	AURA_GRADE_NONE,
	AURA_GRADE_ORDINARY,
	AURA_GRADE_SIMPLE,
	AURA_GRADE_NOBLE,
	AURA_GRADE_SPARKLING,
	AURA_GRADE_MAGNIFICENT,
	AURA_GRADE_RADIANT,
	AURA_GRADE_MAX_NUM,
};
enum EAuraRefineInfoType
{
	AURA_REFINE_INFO_STEP,
	AURA_REFINE_INFO_LEVEL_MIN,
	AURA_REFINE_INFO_LEVEL_MAX,
	AURA_REFINE_INFO_NEED_EXP,
	AURA_REFINE_INFO_MATERIAL_VNUM,
	AURA_REFINE_INFO_MATERIAL_COUNT,
	AURA_REFINE_INFO_NEED_GOLD,
	AURA_REFINE_INFO_EVOLVE_PCT,
	AURA_REFINE_INFO_MAX
};

enum ERefineInfoType
{
	AURA_REFINE_INFO_SLOT_CURRENT,
	AURA_REFINE_INFO_SLOT_NEXT,
	AURA_REFINE_INFO_SLOT_EVOLVED,
	AURA_REFINE_INFO_SLOT_MAX
};
#endif
