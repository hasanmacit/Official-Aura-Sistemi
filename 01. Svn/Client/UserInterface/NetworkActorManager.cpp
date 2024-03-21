// Extend the SNetworkActorData::__copy__ function with:
#ifdef ENABLE_AURA_SYSTEM
	m_dwAura = src.m_dwAura;
#endif

// Extend the SNetworkActorData::SNetworkActorData constructor function with:
#ifdef ENABLE_AURA_SYSTEM
	m_dwAura=0;
#endif

// Extend the CNetworkActorManager::__AppendCharacterManagerActor with:
	kCreateData.m_dwHair=rkNetActorData.m_dwHair;
	kCreateData.m_isMain=__IsMainActorVID(dwVID);
#ifdef ENABLE_AURA_SYSTEM
	kCreateData.m_dwAura=rkNetActorData.m_dwAura;
#endif

// Extend the CNetworkActorManager::UpdateActor with:
		pkInstFind->ChangeWeapon(c_rkNetUpdateActorData.m_dwWeapon);
		pkInstFind->ChangeHair(c_rkNetUpdateActorData.m_dwHair);		
#ifdef ENABLE_AURA_SYSTEM
		pkInstFind->ChangeAura(c_rkNetUpdateActorData.m_dwAura);
#endif
	//[...]
	rkNetActorData.m_sAlignment=c_rkNetUpdateActorData.m_sAlignment;
	rkNetActorData.m_byPKMode=c_rkNetUpdateActorData.m_byPKMode;
#ifdef ENABLE_AURA_SYSTEM
	rkNetActorData.m_dwAura=c_rkNetUpdateActorData.m_dwAura;
#endif
