// Add this to the top of the file after the stdafx.h:
#ifdef ENABLE_AURA_SYSTEM
#include "../EffectLib/EffectManager.h"
#endif

// Extend the CItemData::GetUseTypeString function with this:
#ifdef ENABLE_AURA_SYSTEM
		case USE_PUT_INTO_AURA_SOCKET:
			return DEF_STR(USE_PUT_INTO_AURA_SOCKET);
#endif

// Add the followings anywhere you want to:
#ifdef ENABLE_AURA_SYSTEM
void CItemData::SetAuraScaleTableData(BYTE byJob, BYTE bySex, float fMeshScaleX, float fMeshScaleY, float fMeshScaleZ, float fParticleScale)
{
	m_AuraScaleTable.v3MeshScale[bySex][byJob].x = fMeshScaleX;
	m_AuraScaleTable.v3MeshScale[bySex][byJob].y = fMeshScaleY;
	m_AuraScaleTable.v3MeshScale[bySex][byJob].z = fMeshScaleZ;
	m_AuraScaleTable.fParticleScale[bySex][byJob] = fParticleScale;
}

D3DXVECTOR3& CItemData::GetAuraMeshScaleVector(BYTE byJob, BYTE bySex)
{
	return m_AuraScaleTable.v3MeshScale[bySex][byJob];
}

float CItemData::GetAuraParticleScale(BYTE byJob, BYTE bySex)
{
	return m_AuraScaleTable.fParticleScale[bySex][byJob];
}

void CItemData::SetAuraEffectID(const char* szAuraEffectPath)
{
	if (szAuraEffectPath)
		CEffectManager::Instance().RegisterEffect2(szAuraEffectPath, &m_dwAuraEffectID);
}
#endif

// Add the followings to the bottom of the CItemData::Clear function:
#ifdef ENABLE_AURA_SYSTEM
	memset(&m_AuraScaleTable, 0, sizeof(m_AuraScaleTable));
	m_dwAuraEffectID = 0;
#endif
