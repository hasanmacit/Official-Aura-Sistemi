// Check the function and make the changes for the scale via compare:
void CActorInstance::ProcessMotionEventEffectEvent(const CRaceMotionData::TMotionEventData * c_pData)
{
	if (CRaceMotionData::MOTION_EVENT_TYPE_EFFECT != c_pData->iType)
		return;

	const CRaceMotionData::TMotionEffectEventData * c_pEffectData = (const CRaceMotionData::TMotionEffectEventData *)c_pData;

	const D3DXVECTOR3 c_v3Scale = GetScale();
	if (c_pEffectData->isIndependent)
	{
		int iIndex = CEffectManager::Instance().CreateEffectWithScale(c_pEffectData->dwEffectIndex, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), c_v3Scale.x);

		D3DXMATRIX matLocalPosition;
		D3DXMatrixTranslation(&matLocalPosition, c_pEffectData->v3EffectPosition.x, c_pEffectData->v3EffectPosition.y, c_pEffectData->v3EffectPosition.z);

		D3DXMATRIX matWorld;
		matWorld = matLocalPosition;
		matWorld *= m_worldMatrix;

		CEffectManager::Instance().SelectEffectInstance(iIndex);
		CEffectManager::Instance().SetEffectInstanceGlobalMatrix(matWorld);
		return;
	}

	if (c_pEffectData->isAttaching)
	{
		if (c_pEffectData->isFollowing)
		{
			const char* szAttachingBoneName = c_pEffectData->strAttachingBoneNames[0].c_str();
			if (!c_pEffectData->strAttachingBoneNames.empty())
			{
				for (BYTE j = 0; j < c_pEffectData->strAttachingBoneNames.size(); j++)
				{
					int iBoneIndex;
					if (FindBoneIndex(0, c_pEffectData->strAttachingBoneNames[j].c_str(), &iBoneIndex))
					{
						szAttachingBoneName = c_pEffectData->strAttachingBoneNames[j].c_str();
						break;
					}
				}
			}
			else
				return;

			AttachEffectByID(0, szAttachingBoneName, c_pEffectData->dwEffectIndex, &c_pEffectData->v3EffectPosition, c_v3Scale.x, &c_v3Scale);
		}
		else
		{
			int iBoneIndex;
			DWORD dwPartIndex = 0;
			if (FindBoneIndex(dwPartIndex, c_pEffectData->strAttachingBoneNames[0].c_str(), &iBoneIndex))
			{
				D3DXMATRIX * pBoneMat;
				GetBoneMatrix(dwPartIndex, iBoneIndex, &pBoneMat);

				D3DXMATRIX matLocalPosition;
				D3DXMatrixTranslation(&matLocalPosition, c_pEffectData->v3EffectPosition.x, c_pEffectData->v3EffectPosition.y, c_pEffectData->v3EffectPosition.z);

				/////////////////////////////////////////////////////////////////////
				D3DXMATRIX matWorld;
				matWorld = *pBoneMat;
				matWorld *= matLocalPosition;
				matWorld *= m_worldMatrix;
				/////////////////////////////////////////////////////////////////////

				int iIndex = CEffectManager::Instance().CreateEffect(c_pEffectData->dwEffectIndex,
														c_pEffectData->v3EffectPosition,
														D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				CEffectManager::Instance().SelectEffectInstance(iIndex);
				CEffectManager::Instance().SetEffectInstanceGlobalMatrix(matWorld);
			}
		}
	}
	else
	{
		AttachEffectByID(0, NULL, c_pEffectData->dwEffectIndex, &c_pEffectData->v3EffectPosition, c_v3Scale.x, &c_v3Scale);
	}
}
