// Optional, not used: Extend the ACOUNT_CHARACTER enum with this:
#ifdef ENABLE_AURA_SYSTEM
			ACCOUNT_CHARACTER_SLOT_AURA,
#endif

// Add the followings to the bottom of the CPythonNetworkStream class:
#ifdef ENABLE_AURA_SYSTEM
	protected:
		bool RecvAuraPacket();

	public:
		bool SendAuraRefineCheckIn(TItemPos InventoryCell, TItemPos AuraCell, BYTE byAuraRefineWindowType);
		bool SendAuraRefineCheckOut(TItemPos AuraCell, BYTE byAuraRefineWindowType);
		bool SendAuraRefineAccept(BYTE byAuraRefineWindowType);
		bool SendAuraRefineCancel();
#endif
