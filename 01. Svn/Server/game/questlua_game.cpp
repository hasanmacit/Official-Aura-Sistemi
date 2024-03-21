// Add the new functions anywhere you want to:
#ifdef __AURA_SYSTEM__
	//ALUA(game_open_aura_absorb_window)
	int game_open_aura_absorb_window(lua_State* L)
	{
		const LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (NULL == ch)
		{
			sys_err("NULL POINT ERROR");
			return 0;
		}

		ch->OpenAuraRefineWindow(CQuestManager::instance().GetCurrentNPCCharacterPtr(), AURA_WINDOW_TYPE_ABSORB);
		return 0;
	}

	//ALUA(game_open_aura_growth_window)
	int game_open_aura_growth_window(lua_State* L)
	{
		const LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (NULL == ch)
		{
			sys_err("NULL POINT ERROR");
			return 0;
		}

		ch->OpenAuraRefineWindow(CQuestManager::instance().GetCurrentNPCCharacterPtr(), AURA_WINDOW_TYPE_GROWTH);
		return 0;
	}

	//ALUA(game_open_aura_evolve_window)
	int game_open_aura_evolve_window(lua_State* L)
	{
		const LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (NULL == ch)
		{
			sys_err("NULL POINT ERROR");
			return 0;
		}

		ch->OpenAuraRefineWindow(CQuestManager::instance().GetCurrentNPCCharacterPtr(), AURA_WINDOW_TYPE_EVOLVE);
		return 0;
	}
#endif

// Enable them in the array below:
#ifdef __AURA_SYSTEM__
			{ "open_aura_absorb_window",	game_open_aura_absorb_window	},
			{ "open_aura_growth_window",	game_open_aura_growth_window	},
			{ "open_aura_evolve_window",	game_open_aura_evolve_window	},
#endif
