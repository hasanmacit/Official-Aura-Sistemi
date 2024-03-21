// Add to the includes:
#include "../gameLib/GameType.h"
#include "../gameLib/RaceData.h"

// Paste the following function above of the CGraphicThingInstance::DeformAll function:
void CGraphicThingInstance::RecalcAccePositionMatrixFromBoneMatrix()
{
	if (m_LODControllerVector.empty())
		return;

	CGrannyModelInstance* pModelInstance = m_LODControllerVector[0]->GetModelInstance();
	if (!pModelInstance)
		return;

	int iBoneIndex = 0;
	pModelInstance->GetBoneIndexByName("Bip01 Spine2", &iBoneIndex);
	const D3DXMATRIX* cmatBoneMatrix = (D3DXMATRIX *)pModelInstance->GetBoneMatrixPointer(iBoneIndex);
	if (cmatBoneMatrix)
	{
		D3DXVECTOR3 v3ScaleCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fAccePosX = cmatBoneMatrix->_41;
		float fAccePosY = cmatBoneMatrix->_42;
		float fAccePosZ = cmatBoneMatrix->_43;
		D3DXMatrixIdentity(&m_matScale);
		if (m_bAttachedAcceRace)
		{
			v3ScaleCenter.x = fAccePosX;
			v3ScaleCenter.y = fAccePosY;
		}
		else
		{
			v3ScaleCenter.x = fAccePosX - 18.0f;
			v3ScaleCenter.y = -40.0f;
		}
		v3ScaleCenter.z = fAccePosZ;
		D3DXQUATERNION qRot = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTransformation(&m_matScale, &v3ScaleCenter, &qRot, &m_v3ScaleAcce, NULL, NULL, NULL);
	}

	D3DXMATRIX matTemp;
	D3DXMatrixMultiply(&matTemp, &m_matScaleWorld, &m_matScale);
	m_matAbsoluteTrans = matTemp * m_mRotation;
	m_matAbsoluteTrans._41 += m_v3Position.x;
	m_matAbsoluteTrans._42 += m_v3Position.y;
	m_matAbsoluteTrans._43 += m_v3Position.z;
}

// Replace the whole CGraphicThingInstance::DeformAll function with this:
void CGraphicThingInstance::DeformAll()
{
	m_bUpdated = true;

	for (std::vector<CGrannyLODController*>::size_type i = 0; i != m_LODControllerVector.size(); i++)
	{
		CGrannyLODController* pkLOD = m_LODControllerVector[i];
		if (pkLOD && pkLOD->isModelInstance())
		{
			if (i == CRaceData::PART_ACCE)
			{
				RecalcAccePositionMatrixFromBoneMatrix();
				pkLOD->DeformAll(&m_matAbsoluteTrans);
			}
			else
				pkLOD->DeformAll(&m_worldMatrix);
		}
	}
}

// Replace the whole CGraphicThingInstance::DeformNoSkin function with this:
void CGraphicThingInstance::DeformNoSkin()
{
	m_bUpdated = true;

	for (std::vector<CGrannyLODController*>::size_type i = 0; i != m_LODControllerVector.size(); i++)
	{
		CGrannyLODController* pkLOD = m_LODControllerVector[i];
		if (pkLOD && pkLOD->isModelInstance())
		{
			if (i == CRaceData::PART_ACCE)
			{
				RecalcAccePositionMatrixFromBoneMatrix();
				pkLOD->DeformNoSkin(&m_matAbsoluteTrans);
			}
			else
				pkLOD->DeformNoSkin(&m_worldMatrix);
		}
	}
}

// Replace the whole CGraphicThingInstance::OnDeform function with this:
void CGraphicThingInstance::OnDeform()
{
	m_bUpdated = true;

	for (std::vector<CGrannyLODController*>::size_type i = 0; i != m_LODControllerVector.size(); i++)
	{
		CGrannyLODController* pkLOD = m_LODControllerVector[i];
		if (pkLOD && pkLOD->isModelInstance())
		{
			if (i == CRaceData::PART_ACCE)
			{
				RecalcAccePositionMatrixFromBoneMatrix();
				pkLOD->Deform(&m_matAbsoluteTrans);
			}
			else
				pkLOD->Deform(&m_worldMatrix);
		}
	}
}
