// Replace the initialization of the scale in the CGraphicObjectInstance::Clear function with this:
	m_v3Scale.x = m_v3Scale.y = m_v3Scale.z = 1.0f;

// Paste the followings at the bottom of the (same) ::Clear function before the OnClear:
	m_v3ScaleAcce.x = m_v3ScaleAcce.y = m_v3ScaleAcce.z = 0.0f;
	m_bAttachedAcceRace = 0;
	D3DXMatrixIdentity(&m_matAbsoluteTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matScaleWorld);

// In the CGraphicObjectInstance::Transform function replace the first line to this:
	m_worldMatrix = m_matScaleWorld * m_mRotation;

// Paste the following functions anywhere you want:
void CGraphicObjectInstance::SetScaleWorld(float x, float y, float z)
{
	m_v3Scale.x = x;
	m_v3Scale.y = y;
	m_v3Scale.z = z;
	D3DXMatrixScaling(&m_matScaleWorld, x, y, z);
}

void CGraphicObjectInstance::SetAcceScale(float x, float y, float z)
{
	m_v3ScaleAcce.x = x;
	m_v3ScaleAcce.y = y;
	m_v3ScaleAcce.z = z;
}

void CGraphicObjectInstance::SetAcceScale(const D3DXVECTOR3& rv3Scale, BYTE bRace)
{
	m_v3ScaleAcce = rv3Scale;
	m_bAttachedAcceRace = bRace;
}

// Replace the scale in the CGraphicObjectInstance::Initialize function with this:
	m_v3Scale.x = m_v3Scale.y = m_v3Scale.z = 1.0f;

// Add these before the OnInitialize in the CGraphicObjectInstance::Initialize function:
	m_v3ScaleAcce.x = m_v3ScaleAcce.y = m_v3ScaleAcce.z = 0.0f;
	D3DXMatrixIdentity(&m_matAbsoluteTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matScaleWorld);
