// Add the new functions anywhere you want to:
PyObject* itemIsWeddingItem(PyObject* poSelf, PyObject* poArgs)
{
	DWORD dwItemIndex;
	switch (PyTuple_Size(poArgs))
	{
	case 0:
	{
		CItemData* pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
		if (!pItemData)
			return Py_BuildException("No item selected!");
		dwItemIndex = pItemData->GetIndex();
		break;
	}
	case 1:
	{
		if (!PyTuple_GetUnsignedLong(poArgs, 0, &dwItemIndex))
			return Py_BuildException();
		break;
	}
	default:
		return Py_BuildException();
	}
	//if ((dwItemIndex == 50201 || dwItemIndex == 50202) || (dwItemIndex >= 11901 && dwItemIndex <= 11914))
	//	return Py_BuildValue("i", TRUE);

	switch (dwItemIndex)
	{
		case CItemData::WEDDING_TUXEDO1:
		case CItemData::WEDDING_TUXEDO2:
		case CItemData::WEDDING_TUXEDO3:
		case CItemData::WEDDING_TUXEDO4:
		case CItemData::WEDDING_BRIDE_DRESS1:
		case CItemData::WEDDING_BRIDE_DRESS2:
		case CItemData::WEDDING_BRIDE_DRESS3:
		case CItemData::WEDDING_BRIDE_DRESS4:
		case CItemData::WEDDING_BOUQUET1:
		case CItemData::WEDDING_BOUQUET2:
			return Py_BuildValue("i", TRUE);
			break;
	}

	return Py_BuildValue("i", FALSE);
}

PyObject* itemGetItemNameByVnum(PyObject* poSelf, PyObject* poArgs)
{
	DWORD dwItemIndex;
	if (!PyTuple_GetUnsignedLong(poArgs, 0, &dwItemIndex))
		return Py_BadArgument();

	if (!CItemManager::Instance().SelectItemData(dwItemIndex))
	{
		TraceError("Cannot find item by vnum %lu", dwItemIndex);
		return Py_BuildValue("s", "");
	}

	return Py_BuildValue("s", CItemManager::Instance().GetSelectedItemDataPointer()->GetName());
}

// Enable them in the method-list:
		{ "IsWeddingItem",					itemIsWeddingItem,						METH_VARARGS },
		{ "GetItemNameByVnum",				itemGetItemNameByVnum,					METH_VARARGS },

// Add the new constants:
#ifdef ENABLE_AURA_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_AURA",			CItemData::COSTUME_AURA);
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_AURA",			c_Costume_Slot_Aura);
	PyModule_AddIntConstant(poModule, "USE_PUT_INTO_AURA_SOCKET",	CItemData::USE_PUT_INTO_AURA_SOCKET);
	PyModule_AddIntConstant(poModule, "RESOURCE_AURA",				CItemData::RESOURCE_AURA);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_NONE",			CItemData::AURA_GRADE_NONE);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_ORDINARY",		CItemData::AURA_GRADE_ORDINARY);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_SIMPLE",			CItemData::AURA_GRADE_SIMPLE);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_NOBLE",			CItemData::AURA_GRADE_NOBLE);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_SPARKLING",		CItemData::AURA_GRADE_SPARKLING);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_MAGNIFICENT",		CItemData::AURA_GRADE_MAGNIFICENT);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_RADIANT",			CItemData::AURA_GRADE_RADIANT);
	PyModule_AddIntConstant(poModule, "AURA_GRADE_MAX_NUM",			CItemData::AURA_GRADE_MAX_NUM);
	PyModule_AddIntConstant(poModule, "AURA_BOOST_ITEM_VNUM_BASE",	CItemData::AURA_BOOST_ITEM_VNUM_BASE);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_ERASER",		CItemData::ITEM_AURA_BOOST_ERASER);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_WEAK",		CItemData::ITEM_AURA_BOOST_WEAK);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_NORMAL",		CItemData::ITEM_AURA_BOOST_NORMAL);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_STRONG",		CItemData::ITEM_AURA_BOOST_STRONG);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_ULTIMATE",	CItemData::ITEM_AURA_BOOST_ULTIMATE);
	PyModule_AddIntConstant(poModule, "ITEM_AURA_BOOST_MAX",		CItemData::ITEM_AURA_BOOST_MAX);
#endif
