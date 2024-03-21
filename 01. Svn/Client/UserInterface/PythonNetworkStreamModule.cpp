// Add the new functions anywhere you want to:
#ifdef ENABLE_AURA_SYSTEM
PyObject* netSendAuraRefineCheckIn(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos InventoryPos;
	TItemPos AuraPos;
	BYTE bAuraRefineWindowType;
	switch (PyTuple_Size(poArgs))
	{
	case 3:
		if (!PyTuple_GetInteger(poArgs, 0, &InventoryPos.cell))
			return Py_BuildException();
		AuraPos.window_type = AURA_REFINE;
		if (!PyTuple_GetInteger(poArgs, 1, &AuraPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 2, &bAuraRefineWindowType))
			return Py_BuildException();
		break;
	case 5:
		if (!PyTuple_GetByte(poArgs, 0, &InventoryPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &InventoryPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 2, &AuraPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 3, &AuraPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 4, &bAuraRefineWindowType))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendAuraRefineCheckIn(InventoryPos, AuraPos, bAuraRefineWindowType);
	return Py_BuildNone();
}

PyObject* netSendAuraRefineCheckOut(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos AuraPos;
	BYTE byAuraRefineWindowType;
	switch (PyTuple_Size(poArgs))
	{
	case 2:
		AuraPos.window_type = AURA_REFINE;
		if (!PyTuple_GetInteger(poArgs, 0, &AuraPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 1, &byAuraRefineWindowType))
			return Py_BuildException();
		break;
	case 3:
		if (!PyTuple_GetByte(poArgs, 0, &AuraPos.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &AuraPos.cell))
			return Py_BuildException();
		if (!PyTuple_GetByte(poArgs, 2, &byAuraRefineWindowType))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendAuraRefineCheckOut(AuraPos, byAuraRefineWindowType);
	return Py_BuildNone();
}

PyObject* netSendAuraRefineAccept(PyObject* poSelf, PyObject* poArgs)
{
	BYTE byAuraRefineWindowType;
	if (!PyTuple_GetByte(poArgs, 0, &byAuraRefineWindowType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendAuraRefineAccept(byAuraRefineWindowType);
	return Py_BuildNone();
}

PyObject* netSendAuraRefineCancel(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendAuraRefineCancel();
	return Py_BuildNone();
}
#endif

// Then enable them in the method-list:
#ifdef ENABLE_AURA_SYSTEM
		{ "SendAuraRefineCheckIn",					netSendAuraRefineCheckIn,					METH_VARARGS },
		{ "SendAuraRefineCheckOut",					netSendAuraRefineCheckOut,					METH_VARARGS },
		{ "SendAuraRefineAccept",					netSendAuraRefineAccept,					METH_VARARGS },
		{ "SendAuraRefineCancel",					netSendAuraRefineCancel,					METH_VARARGS },
#endif

// Optional, not used:
#ifdef ENABLE_AURA_SYSTEM
	PyModule_AddIntConstant(poModule, "ACCOUNT_CHARACTER_SLOT_AURA", CPythonNetworkStream::ACCOUNT_CHARACTER_SLOT_AURA);
#endif
