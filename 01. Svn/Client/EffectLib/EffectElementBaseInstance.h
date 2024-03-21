// Add the following to the bottom of the CEffectElementBaseInstance class
	public:
		void SetParticleScale(float fParticleScale);
		void SetMeshScale(D3DXVECTOR3 rv3MeshScale);

	protected:
		float m_fParticleScale;
		D3DXVECTOR3 m_v3MeshScale;
