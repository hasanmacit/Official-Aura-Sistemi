// Add these to the bottom of the CGraphicObjectInstance class:
	public:
		void		SetScaleWorld(float x, float y, float z);
		void		SetAcceScale(float x, float y, float z);
		void		SetAcceScale(const D3DXVECTOR3& rv3Scale, BYTE bRace);

	protected:
		BYTE		m_bAttachedAcceRace;
		D3DXVECTOR3	m_v3ScaleAcce;
		D3DXMATRIX	m_matAbsoluteTrans;
		D3DXMATRIX	m_matScale;
		D3DXMATRIX	m_matScaleWorld;
