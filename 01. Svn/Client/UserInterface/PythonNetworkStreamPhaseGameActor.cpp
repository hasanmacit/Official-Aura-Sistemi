// In the CPythonNetworkStream::RecvCharacterAppendPacket function below of this:
	kNetActorData.m_dwHair=0;/*chrAddPacket.awPart[CHR_EQUIPPART_HAIR]*/;	
	kNetActorData.m_dwMountVnum=0;/*chrAddPacket.dwMountVnum*/;	
	kNetActorData.m_dwLevel=0; // 몬스터 레벨 표시 안함

// Add this:
#ifdef ENABLE_AURA_SYSTEM
	kNetActorData.m_dwAura=0;/* chrAddPacket.awPart[CHR_EQUIPPART_AURA]*/
#endif

// In the CPythonNetworkStream::RecvCharacterAdditionalInfo function below of this:
		kNetActorData.m_dwHair=chrInfoPacket.awPart[CHR_EQUIPPART_HAIR];	
		kNetActorData.m_dwMountVnum=chrInfoPacket.dwMountVnum;

// Add this:
#ifdef ENABLE_AURA_SYSTEM
		kNetActorData.m_dwAura=chrInfoPacket.awPart[CHR_EQUIPPART_AURA];
#endif

// In the CPythonNetworkStream::RecvCharacterUpdatePacket function below of this:
	kNetUpdateActorData.m_dwStateFlags=chrUpdatePacket.bStateFlag;
	kNetUpdateActorData.m_dwMountVnum=chrUpdatePacket.dwMountVnum;

// Add this:
#ifdef ENABLE_AURA_SYSTEM
	kNetUpdateActorData.m_dwAura=chrUpdatePacket.awPart[CHR_EQUIPPART_AURA];
#endif
