// In the LoadLocaleData function after this:
	rkNPCMgr.Destroy();
	rkItemMgr.Destroy();	
	rkSkillMgr.Destroy();

// Add these:
#ifdef ENABLE_AURA_SYSTEM
	char szAuraScale[256];
	snprintf(szAuraScale, sizeof(szAuraScale), "%s/aura_scale.txt", localePath);
	if (!rkItemMgr.LoadAuraScale(szAuraScale))
	{
		TraceError("LoadLocaleData - LoadAuraScale(%s) Error", szAuraScale);
	}
#endif
