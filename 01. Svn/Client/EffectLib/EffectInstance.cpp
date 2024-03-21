// In the CEffectInstance::__SetParticleData function add the following before the line with push_back:
	pInstance->SetParticleScale(GetParticleScale());

// In the CEffectInstance::__SetMeshData function add the following before the line with push_back:
	pMeshInstance->SetMeshScale(GetMeshScale());

// Add the followings in the CEffectInstance::__Initialize function:
	m_fParticleScale = 1.0f;
	m_v3MeshScale.x = m_v3MeshScale.y = m_v3MeshScale.z = 1.0f;
