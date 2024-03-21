// Replace this function: CInstanceBase::AttachSpecialEffect (Or check the differences and make it fit for you!)
void CInstanceBase::AttachSpecialEffect(DWORD effect)
{
	__AttachEffect(effect);
}
// With this:
void CInstanceBase::AttachSpecialEffect(DWORD effect, float fScale)
{
	__AttachEffect(effect, fScale);
}

// Replace this function: CInstanceBase::CreateSpecialEffect (Or check the differences and make it fit for you!)
void CInstanceBase::CreateSpecialEffect(DWORD iEffectIndex)
{
	const D3DXMATRIX & c_rmatGlobal = m_GraphicThingInstance.GetTransform();

	DWORD dwEffectIndex = CEffectManager::Instance().GetEmptyIndex();
	DWORD dwEffectCRC = ms_adwCRCAffectEffect[iEffectIndex];
	CEffectManager::Instance().CreateEffectInstance(dwEffectIndex, dwEffectCRC);
	CEffectManager::Instance().SelectEffectInstance(dwEffectIndex);
	CEffectManager::Instance().SetEffectInstanceGlobalMatrix(c_rmatGlobal);
}
// With this:
void CInstanceBase::CreateSpecialEffect(DWORD iEffectIndex, float fScale)
{
	const D3DXMATRIX & c_rmatGlobal = m_GraphicThingInstance.GetTransform();

	DWORD dwEffectIndex = CEffectManager::Instance().GetEmptyIndex();
	DWORD dwEffectCRC = ms_adwCRCAffectEffect[iEffectIndex];
	CEffectManager::Instance().CreateEffectInstanceWithScale(dwEffectIndex, dwEffectCRC, fScale);
	CEffectManager::Instance().SelectEffectInstance(dwEffectIndex);
	CEffectManager::Instance().SetEffectInstanceGlobalMatrix(c_rmatGlobal);
}

// In the function CInstanceBase::__EffectContainer_AttachEffect replace this line:
	DWORD dwEftID=__AttachEffect(dwEftKey);
// With this:
	DWORD dwEftID=__AttachEffect(dwEftKey, m_GraphicThingInstance.GetScale().x);

// Replace or make the differences about the scale in this function: CInstanceBase::__AttachEffect
DWORD CInstanceBase::__AttachEffect(UINT eEftType, float fScale)
{
	// 2004.07.17.levites.isShow를 ViewFrustumCheck로 변경
	//if (IsAffect(AFFECT_INVISIBILITY))
	if (IsInvisibility() && !__IsMainInstance())
		return 0;

	if (eEftType>=EFFECT_NUM)
		return 0;

	if (ms_astAffectEffectAttachBone[eEftType].empty())
	{
		return m_GraphicThingInstance.AttachEffectByID(0, NULL, ms_adwCRCAffectEffect[eEftType], (const D3DXVECTOR3*)NULL, fScale);
	}
	else
	{
		std::string & rstrBoneName = ms_astAffectEffectAttachBone[eEftType];
		const char * c_szBoneName;
		// 양손에 붙일 때 사용한다.
		// 이런 식의 예외 처리를 해놓은 것은 캐릭터 마다 Equip 의 Bone Name 이 다르기 때문.
		if (0 == rstrBoneName.compare("PART_WEAPON"))
		{
			if (m_GraphicThingInstance.GetAttachingBoneName(CRaceData::PART_WEAPON, &c_szBoneName))
			{
				return m_GraphicThingInstance.AttachEffectByID(0, c_szBoneName, ms_adwCRCAffectEffect[eEftType]);
			}
		}
		else if (0 == rstrBoneName.compare("PART_WEAPON_LEFT"))
		{
			if (m_GraphicThingInstance.GetAttachingBoneName(CRaceData::PART_WEAPON_LEFT, &c_szBoneName))
			{
				return m_GraphicThingInstance.AttachEffectByID(0, c_szBoneName, ms_adwCRCAffectEffect[eEftType]);
			}
		}
		else
		{
			return m_GraphicThingInstance.AttachEffectByID(0, rstrBoneName.c_str(), ms_adwCRCAffectEffect[eEftType], (const D3DXVECTOR3*)NULL, fScale);
		}
	}

	return 0;
}
