// Add the following to the bottom of the CPacketInfoCG::CPacketInfoCG function:
#ifdef __AURA_SYSTEM__
	Set(HEADER_CG_AURA, sizeof(TPacketCGAura), "Aura", true);
#endif
