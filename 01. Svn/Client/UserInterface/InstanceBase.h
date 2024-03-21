// Extend the CInstanceBase::SCreateData struct with:
#ifdef ENABLE_AURA_SYSTEM
			DWORD	m_dwAura;
#endif

// Add the followings to the bottom of the CInstanceBase class:
#ifdef ENABLE_AURA_SYSTEM
	public:
		bool	SetAura(DWORD eAura);
		void	ChangeAura(DWORD eAura);
	protected:
		DWORD	m_auraRefineEffect;
#endif

// In the CInstanceBase class modify this function:
		DWORD	__AttachEffect(UINT eEftType);
// To:
		DWORD	__AttachEffect(UINT eEftType, float fScale = 1.0f);

// In the CInstanceBase class modify these functions:
		void CreateSpecialEffect(DWORD iEffectIndex);
		void AttachSpecialEffect(DWORD effect);
// To:
		void CreateSpecialEffect(DWORD iEffectIndex, float fScale = 1.0f);
		void AttachSpecialEffect(DWORD effect, float fScale = 1.0f);
