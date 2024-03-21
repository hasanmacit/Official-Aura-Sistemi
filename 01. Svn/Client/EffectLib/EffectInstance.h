// Add the followings to the bottom of the CEffectInstance class
	protected:
		float m_fParticleScale;
		D3DXVECTOR3 m_v3MeshScale;

	public:
		void SetParticleScale(float fParticleScale) { m_fParticleScale = fParticleScale; }
		float GetParticleScale() { return m_fParticleScale; }
		void SetMeshScale(D3DXVECTOR3 rv3MeshScale) { m_v3MeshScale = rv3MeshScale; }
		D3DXVECTOR3 GetMeshScale() { return m_v3MeshScale; }
