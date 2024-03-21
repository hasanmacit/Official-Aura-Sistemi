// Add these functions anywhere you want:
void CEffectElementBaseInstance::SetParticleScale(float fParticleScale)
{
	m_fParticleScale = fParticleScale;
}

void CEffectElementBaseInstance::SetMeshScale(D3DXVECTOR3 rv3MeshScale)
{
	m_v3MeshScale = rv3MeshScale;
}

// In the CEffectElementBaseInstance::Initialize function add before the OnInitialize():
	m_fParticleScale = 1.0f;
	m_v3MeshScale.x = m_v3MeshScale.y = m_v3MeshScale.z = 1.0f;

