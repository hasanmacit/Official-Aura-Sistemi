// Add to the bottom of the CItemManager class the followings:
#ifdef ENABLE_AURA_SYSTEM
	public:
		enum EAuraScaleCol
		{
			AURA_SCALE_COL_VNUM,
			AURA_SCALE_COL_JOB,
			AURA_SCALE_COL_SEX,
			AURA_SCALE_COL_MESH_SCALE_X,
			AURA_SCALE_COL_MESH_SCALE_Y,
			AURA_SCALE_COL_MESH_SCALE_Z,
			AURA_SCALE_COL_PARTICLE_SCALE,
			AURA_SCALE_COL_NUM,
		};

		bool	LoadAuraScale(const char* c_szFileName);
#endif
