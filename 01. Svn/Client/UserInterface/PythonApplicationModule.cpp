// Add the macro to the constants:
#ifdef ENABLE_AURA_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_AURA_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_AURA_SYSTEM", 0);
#endif
