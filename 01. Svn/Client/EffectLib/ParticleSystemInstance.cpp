// In the CParticleSystemInstance::CreateParticles function paste the followings above of the line:
		if (BILLBOARD_TYPE_LIE == m_pParticleProperty->m_byBillboardType && mc_pmatLocal)

// Like this way:
		m_pEmitterProperty->GetParticleSizeX(m_fLocalTime, &v2HalfSize.x);
		m_pEmitterProperty->GetParticleSizeY(m_fLocalTime, &v2HalfSize.y);

		v2HalfSize.x = v2HalfSize.x * m_fParticleScale;
		v2HalfSize.y = v2HalfSize.y * m_fParticleScale;

		if (BILLBOARD_TYPE_LIE == m_pParticleProperty->m_byBillboardType && mc_pmatLocal)
		{
