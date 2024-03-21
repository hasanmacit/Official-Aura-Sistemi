// Add the following function anywhere you want to:
void CActorInstance::ChangePart(DWORD dwPartIndex, DWORD dwItemIndex)
{
	m_adwPartItemID[dwPartIndex] = dwItemIndex;
}

// As in the header file here make sure the parameters are at the same position!
// Original part, what you need to replace or modify:
DWORD CActorInstance::AttachEffectByID(DWORD dwParentPartIndex, const char * c_pszBoneName, DWORD dwEffectID, const D3DXVECTOR3 * c_pv3Position)
{
	TAttachingEffect ae;
	ae.iLifeType = EFFECT_LIFE_INFINITE;
	ae.dwEndTime = 0;
	ae.dwModelIndex = dwParentPartIndex;
	ae.dwEffectIndex = CEffectManager::Instance().GetEmptyIndex();
	ae.isAttaching = TRUE;
	if (c_pv3Position)
	{
		D3DXMatrixTranslation(&ae.matTranslation, c_pv3Position->x, c_pv3Position->y, c_pv3Position->z);
	}
	else
	{
		D3DXMatrixIdentity(&ae.matTranslation);
	}
	CEffectManager& rkEftMgr=CEffectManager::Instance();
	rkEftMgr.CreateEffectInstance(ae.dwEffectIndex, dwEffectID);

	if (c_pszBoneName)
	{

// Like this way:
DWORD CActorInstance::AttachEffectByID(DWORD dwParentPartIndex, const char * c_pszBoneName, DWORD dwEffectID, const D3DXVECTOR3 * c_pv3Position, float fParticleScale, const D3DXVECTOR3* c_pv3MeshScale)
{
	TAttachingEffect ae;
	ae.iLifeType = EFFECT_LIFE_INFINITE;
	ae.dwEndTime = 0;
	ae.dwModelIndex = dwParentPartIndex;
	ae.dwEffectIndex = CEffectManager::Instance().GetEmptyIndex();
	ae.isAttaching = TRUE;
	if (c_pv3Position)
	{
		D3DXMatrixTranslation(&ae.matTranslation, c_pv3Position->x, c_pv3Position->y, c_pv3Position->z);
	}
	else
	{
		D3DXMatrixIdentity(&ae.matTranslation);
	}
	CEffectManager& rkEftMgr=CEffectManager::Instance();
	if (c_pv3MeshScale)
		rkEftMgr.CreateEffectInstanceWithScale(ae.dwEffectIndex, dwEffectID, fParticleScale, c_pv3MeshScale);
	else
		rkEftMgr.CreateEffectInstanceWithScale(ae.dwEffectIndex, dwEffectID, fParticleScale);

	if (c_pszBoneName)
	{
