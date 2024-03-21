// Extend the CHARACTER_POINT_INSTANT with the following:
#ifdef __AURA_SYSTEM__
	LPENTITY		m_pAuraRefineWindowOpener;
#endif

// Add the followings to the bottom of the CHARACTER class:
#ifdef __AURA_SYSTEM__
	private:
		BYTE		m_bAuraRefineWindowType;
		bool		m_bAuraRefineWindowOpen;
		TItemPos	m_pAuraRefineWindowItemSlot[AURA_SLOT_MAX];
		TAuraRefineInfo m_bAuraRefineInfo[AURA_REFINE_INFO_SLOT_MAX];

	protected:
		BYTE		__GetAuraAbsorptionRate(BYTE bLevel, BYTE bBoostIndex) const;
		TAuraRefineInfo __GetAuraRefineInfo(TItemPos Cell);
		TAuraRefineInfo __CalcAuraRefineInfo(TItemPos Cell, TItemPos MaterialCell);
		TAuraRefineInfo __GetAuraEvolvedRefineInfo(TItemPos Cell);

	public:
		void		OpenAuraRefineWindow(LPENTITY pOpener, EAuraWindowType type);
		bool		IsAuraRefineWindowOpen() const { return  m_bAuraRefineWindowOpen; }
		BYTE		GetAuraRefineWindowType() const { return  m_bAuraRefineWindowType; }
		LPENTITY	GetAuraRefineWindowOpener() { return  m_pointsInstant.m_pAuraRefineWindowOpener; }

		bool		IsAuraRefineWindowCanRefine();

		void		AuraRefineWindowCheckIn(BYTE bAuraRefineWindowType, TItemPos AuraCell, TItemPos ItemCell);
		void		AuraRefineWindowCheckOut(BYTE bAuraRefineWindowType, TItemPos AuraCell);
		void		AuraRefineWindowAccept(BYTE bAuraRefineWindowType);
		void		AuraRefineWindowClose();
#endif
