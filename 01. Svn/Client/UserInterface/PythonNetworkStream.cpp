// In the constructor or the CMainPacketHeaderMap class define the new packet:
#ifdef ENABLE_AURA_SYSTEM
			Set(HEADER_GC_AURA, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCAura), DYNAMIC_SIZE_PACKET));
#endif
