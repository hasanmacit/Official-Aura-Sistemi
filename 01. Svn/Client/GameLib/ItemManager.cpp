// In the CItemManager::LoadItemList function replace the following code:
		else
		{
			if (4 == TokenVector.size())
			{
				const std::string& c_rstrModelFileName = TokenVector[3];
				pItemData->SetDefaultItemData(c_rstrIcon.c_str(), c_rstrModelFileName.c_str());
			}
			else
			{
				pItemData->SetDefaultItemData(c_rstrIcon.c_str());
			}
		}

// With this:
		else
		{
			if (4 == TokenVector.size())
			{
#ifdef ENABLE_AURA_SYSTEM
				if (!strcmp(c_rstrType.c_str(), "AURA"))
				{
					const std::string& c_rstrAuraEffectFileName = TokenVector[3];
					pItemData->SetAuraEffectID(c_rstrAuraEffectFileName.c_str());
					pItemData->SetDefaultItemData(c_rstrIcon.c_str());
				}
				else
				{
					const std::string& c_rstrModelFileName = TokenVector[3];
					pItemData->SetDefaultItemData(c_rstrIcon.c_str(), c_rstrModelFileName.c_str());
				}
#else
				const std::string& c_rstrModelFileName = TokenVector[3];
				pItemData->SetDefaultItemData(c_rstrIcon.c_str(), c_rstrModelFileName.c_str());
#endif
			}
			else
			{
				pItemData->SetDefaultItemData(c_rstrIcon.c_str());
			}
		}

// Add the following function anywhere you want:
#ifdef ENABLE_AURA_SYSTEM
bool CItemManager::LoadAuraScale(const char* c_szFileName)
{
	CMappedFile File;
	LPCVOID pData;
	if (!CEterPackManager::Instance().Get(File, c_szFileName, &pData))
		return false;

	CMemoryTextFileLoader textFileLoader;
	textFileLoader.Bind(File.Size(), pData);

	CTokenVector TokenVector;
	for (DWORD i = 0; i < textFileLoader.GetLineCount(); ++i)
	{
		if (!textFileLoader.SplitLine(i, &TokenVector, "\t"))
			continue;

		if (TokenVector.size() != AURA_SCALE_COL_NUM)
		{
			TraceError(" CItemManager::LoadAuraScale(%s) - Error on line %d\n", c_szFileName, i);
			continue;
		}

		const std::string& c_rstrID = TokenVector[AURA_SCALE_COL_VNUM];
		const std::string& c_rstrJob = TokenVector[AURA_SCALE_COL_JOB];
		const std::string& c_rstrSex = TokenVector[AURA_SCALE_COL_SEX];
		const std::string& c_rstrMeshScaleX = TokenVector[AURA_SCALE_COL_MESH_SCALE_X];
		const std::string& c_rstrMeshScaleY = TokenVector[AURA_SCALE_COL_MESH_SCALE_Y];
		const std::string& c_rstrMeshScaleZ = TokenVector[AURA_SCALE_COL_MESH_SCALE_Z];
		const std::string& c_rstrParticleScale = TokenVector[AURA_SCALE_COL_PARTICLE_SCALE];

		DWORD dwItemVnum = atoi(c_rstrID.c_str());
		BYTE byJob = 0;
		if (!strcmp(c_rstrJob.c_str(), "JOB_WARRIOR"))
			byJob = NRaceData::JOB_WARRIOR;
		if (!strcmp(c_rstrJob.c_str(), "JOB_ASSASSIN"))
			byJob = NRaceData::JOB_ASSASSIN;
		if (!strcmp(c_rstrJob.c_str(), "JOB_SURA"))
			byJob = NRaceData::JOB_SURA;
		if (!strcmp(c_rstrJob.c_str(), "JOB_SHAMAN"))
			byJob = NRaceData::JOB_SHAMAN;
#ifdef ENABLE_WOLFMAN_CHARACTER
		if (!strcmp(c_rstrJob.c_str(), "JOB_WOLFMAN"))
			byJob = NRaceData::JOB_WOLFMAN;
#endif
		BYTE bySex = c_rstrSex[0] == 'M';

		float fMeshScaleX = atof(c_rstrMeshScaleX.c_str()) * 0.01f;
		float fMeshScaleY = atof(c_rstrMeshScaleY.c_str()) * 0.01f;
		float fMeshScaleZ = atof(c_rstrMeshScaleZ.c_str()) * 0.01f;
		float fParticleScale = atof(c_rstrParticleScale.c_str());

		for (BYTE i = 0; i < CItemData::AURA_GRADE_MAX_NUM; ++i)
		{
			CItemData* pItemData = MakeItemData(dwItemVnum + i);
			if (pItemData)
				pItemData->SetAuraScaleTableData(byJob, bySex, fMeshScaleX, fMeshScaleY, fMeshScaleZ, fParticleScale);
		}
	}
	return true;
}
#endif
