// In the function chrCreateInstance extend the variables with:
#ifdef ENABLE_AURA_SYSTEM
		kCreateData.m_dwAura=0;
#endif

// Add the function anywhere you want to:
#ifdef ENABLE_AURA_SYSTEM
PyObject* chrSetAura(PyObject* poSelf, PyObject* poArgs)
{
	int iAura;
	if (!PyTuple_GetInteger(poArgs, 0, &iAura))
		return Py_BuildException();

	CInstanceBase* pCharacterInstance = CPythonCharacterManager::Instance().GetSelectedInstancePtr();
	if (pCharacterInstance)
		pCharacterInstance->SetAura(iAura);

	return Py_BuildNone();
}
#endif

// Enable it in the method-list:
#ifdef ENABLE_AURA_SYSTEM
		{ "SetAura",					chrSetAura,							METH_VARARGS },
#endif

// Add the new constant value:
#ifdef ENABLE_AURA_SYSTEM
	PyModule_AddIntConstant(poModule, "PART_AURA",							CRaceData::PART_AURA);
#endif
