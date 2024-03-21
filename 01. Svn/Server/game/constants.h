// Add these anywhere you want:
#ifdef __AURA_SYSTEM__
static int s_aiAuraRefineTable[AURA_GRADE_MAX_NUM][AURA_REFINE_INFO_MAX];
int* GetAuraRefineInfo(BYTE bLevel);
int GetAuraRefineInfo(BYTE bGrade, BYTE bInfo);
#endif
