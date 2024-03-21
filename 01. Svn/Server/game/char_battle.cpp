// In the function CHARACTER::Dead after these:
	CloseMyShop();
	CloseSafebox();

// Add this one:
#ifdef __AURA_SYSTEM__
	if (IsAuraRefineWindowOpen())
		AuraRefineWindowClose();
#endif
