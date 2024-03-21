// Add the followings to the bottom of the CPythonPlayer class:
#ifdef ENABLE_AURA_SYSTEM
	public:
		enum EItemAuraSockets
		{
			ITEM_SOCKET_AURA_DRAIN_ITEM_VNUM,
			ITEM_SOCKET_AURA_CURRENT_LEVEL,
			ITEM_SOCKET_AURA_BOOST,
		};

		enum EItemAuraMaterialValues
		{
			ITEM_VALUE_AURA_MATERIAL_EXP,
		};

		enum EItemAuraBoostValues
		{
			ITEM_VALUE_AURA_BOOST_PERCENT,
			ITEM_VALUE_AURA_BOOST_TIME,
			ITEM_VALUE_AURA_BOOST_UNLIMITED,
		};

	private:
		typedef struct SAuraRefineInfo
		{
			BYTE bAuraRefineInfoLevel;
			BYTE bAuraRefineInfoExpPercent;
		} TAuraRefineInfo;

		std::vector<TItemData> m_AuraItemInstanceVector;

	protected:
		bool				m_bAuraWindowOpen;
		BYTE				m_bOpenedAuraWindowType;
		TItemPos			m_AuraRefineActivatedCell[AURA_SLOT_MAX];
		TAuraRefineInfo		m_bAuraRefineInfo[AURA_REFINE_INFO_SLOT_MAX];

		void				__ClearAuraRefineWindow();

	public:
		void				SetAuraRefineWindowOpen(BYTE wndType);
		BYTE				GetAuraRefineWindowType() const { return m_bOpenedAuraWindowType; };

		bool				IsAuraRefineWindowOpen() const { return m_bAuraWindowOpen; }
		bool				IsAuraRefineWindowEmpty();

		void				SetAuraRefineInfo(BYTE bAuraRefineInfoSlot, BYTE bAuraRefineInfoLevel, BYTE bAuraRefineInfoExpPercent);
		BYTE				GetAuraRefineInfoLevel(BYTE bAuraRefineInfoSlot);
		BYTE				GetAuraRefineInfoExpPct(BYTE bAuraRefineInfoSlot);

		void				SetAuraItemData(BYTE bSlotIndex, const TItemData& rItemInstance);
		void				DelAuraItemData(BYTE bSlotIndex);

		BYTE				FineMoveAuraItemSlot();
		BYTE				GetAuraCurrentItemSlotCount();

		BOOL				GetAuraItemDataPtr(BYTE bSlotIndex, TItemData** ppInstance);

		void				SetActivatedAuraSlot(BYTE bSlotIndex, TItemPos ItemCell);
		BYTE				FindActivatedAuraSlot(TItemPos ItemCell);
		TItemPos			FindUsingAuraSlot(BYTE bSlotIndex);
#endif
