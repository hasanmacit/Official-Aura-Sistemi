// In the CEffectMeshInstance::OnRender function find this code:
		D3DXVECTOR3 Position;
		m_pMeshScript->GetPosition(m_fLocalTime, Position);
		m_matWorld._41 = Position.x;
		m_matWorld._42 = Position.y;
		m_matWorld._43 = Position.z;
		m_matWorld = m_matWorld * *mc_pmatLocal;
		STATEMANAGER.SetTransform(D3DTS_WORLD, &m_matWorld);

// And replace it with this one:
		D3DXVECTOR3 Position;
		m_pMeshScript->GetPosition(m_fLocalTime, Position);
		D3DXMATRIX matTemp;
		D3DXMatrixTransformation(&matTemp, 0, 0, &m_v3MeshScale, 0, 0, 0);
		m_matWorld._41 += Position.x;
		m_matWorld._42 += Position.y;
		m_matWorld._43 += Position.z;
		D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &matTemp);
		m_matWorld = m_matWorld * *mc_pmatLocal;
		STATEMANAGER.SetTransform(D3DTS_WORLD, &m_matWorld);

