// Add two new parameter to the function [ float fParticleScale = 1.0f, const D3DXVECTOR3* c_pv3MeshScale = NULL ]:
// Make sure the function in the source file will look the same, and every function calls as well!
		DWORD AttachEffectByID(DWORD dwParentPartIndex, const char * c_pszBoneName, DWORD dwEffectID, const D3DXVECTOR3* c_pv3Position = NULL, float fParticleScale = 1.0f, const D3DXVECTOR3* c_pv3MeshScale = NULL);


// Below of this:
		void RefreshActorInstance();

//Add this:
		void ChangePart(DWORD dwPartIndex, DWORD dwItemIndex);
