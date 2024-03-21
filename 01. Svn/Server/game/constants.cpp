// Add these anywhere you want:
#ifdef __AURA_SYSTEM__
int s_aiAuraRefineInfo[AURA_GRADE_MAX_NUM][AURA_REFINE_INFO_MAX] = {
//  [ Grade | LevelMin | LevelMax | NeedEXP | EvolMaterial | EvolMaterialCount | EvolCost | EvolPCT ]
	{1,   1,  49,  1000, 30617, 10,  5000000, 100},
	{2,  50,  99,  2000, 31136, 10,  5000000, 100},
	{3, 100, 149,  4000, 31137, 10,  5000000, 100},
	{4, 150, 199,  8000, 31138, 10,  8000000, 100},
	{5, 200, 249, 16000, 31138, 20, 10000000, 100},
	{6, 250, 250,     0,     0,  0,        0,   0},
	{0,   0,   0,     0,     0,  0,        0,   0}
};

int* GetAuraRefineInfo(BYTE bLevel)
{
	if (bLevel > 250)
		return NULL;

	for (int i = 0; i < AURA_GRADE_MAX_NUM; ++i)
	{
		if (bLevel >= s_aiAuraRefineInfo[i][AURA_REFINE_INFO_LEVEL_MIN] && bLevel <= s_aiAuraRefineInfo[i][AURA_REFINE_INFO_LEVEL_MAX])
			return s_aiAuraRefineInfo[i];
	}

	return NULL;
}

int GetAuraRefineInfo(BYTE bGrade, BYTE bInfo)
{
	if (bGrade >= AURA_GRADE_MAX_NUM || bInfo >= AURA_REFINE_INFO_MAX)
		return 0;

	return s_aiAuraRefineInfo[bGrade - 1][bInfo];
}
#endif
