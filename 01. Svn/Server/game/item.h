// Add the followings to the bottom of the CItem class:
#ifdef __AURA_SYSTEM__
	private:
		LPEVENT m_pkAuraBoostSocketExpireEvent;

	public:
		bool	IsAuraBoosterForSocket();

		void	StartAuraBoosterSocketExpireEvent();
		void	StopAuraBoosterSocketExpireEvent();
		void	SetAuraBoosterSocketExpireEvent(LPEVENT pkEvent);
#endif
