// Extend the SNetworkActorData struct with:
#ifdef ENABLE_AURA_SYSTEM
	DWORD	m_dwAura;
#endif

// Extend the SNetworkUpdateActorData struct and its constructor with:
#ifdef ENABLE_AURA_SYSTEM
	DWORD m_dwAura;
#endif

	SNetworkUpdateActorData()
	{
#ifdef ENABLE_AURA_SYSTEM
		m_dwAura=0;
#endif
};
