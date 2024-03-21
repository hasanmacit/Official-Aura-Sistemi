// Add the following new functions anywhere you want:
int CEffectManager::CreateEffectWithScale(DWORD dwID, const D3DXVECTOR3& c_rv3Position, const D3DXVECTOR3& c_rv3Rotation, float fParticleScale)
{
	int iInstanceIndex = GetEmptyIndex();

	CreateEffectInstanceWithScale(iInstanceIndex, dwID, fParticleScale);
	SelectEffectInstance(iInstanceIndex);
	D3DXMATRIX mat;
	D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(c_rv3Rotation.x), D3DXToRadian(c_rv3Rotation.y), D3DXToRadian(c_rv3Rotation.z));
	mat._41 = c_rv3Position.x;
	mat._42 = c_rv3Position.y;
	mat._43 = c_rv3Position.z;
	SetEffectInstanceGlobalMatrix(mat);

	return iInstanceIndex;
}

void CEffectManager::CreateEffectInstanceWithScale(DWORD dwInstanceIndex, DWORD dwID, float fParticleScale, const D3DXVECTOR3* c_pv3MeshScale)
{
	if (!dwID)
		return;

	CEffectData* pEffect;
	if (!GetEffectData(dwID, &pEffect))
	{
		Tracef("CEffectManager::CreateEffectInstance - NO DATA :%d\n", dwID);
		return;
	}

	CEffectInstance* pEffectInstance = CEffectInstance::New();
	pEffectInstance->SetParticleScale(fParticleScale);
	if (c_pv3MeshScale)
		pEffectInstance->SetMeshScale(*c_pv3MeshScale);
	pEffectInstance->SetEffectDataPointer(pEffect);

	m_kEftInstMap.insert(TEffectInstanceMap::value_type(dwInstanceIndex, pEffectInstance));
}
