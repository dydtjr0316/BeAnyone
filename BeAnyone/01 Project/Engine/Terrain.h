//#pragma once
//#include "Component.h"
//
//#include "Ptr.h"
//#include "Mesh.h"
//#include "Material.h"
//#include "Texture.h"
//
//class CTerrain :
//	public CComponent
//{
//private:
//	UINT			m_iFaceX;
//	UINT			m_iFaceZ;
//	float			m_fMaxTess;
//
//	Ptr<CTexture>	m_pHeightMap;
//
//	Vec2			m_vBrushScale;
//
//	UINT			m_iBrushIdx;
//	UINT			m_iTileIdx;
//
//public:
//	void init();
//	virtual void update();
//	virtual void finalupdate();
//
//
//private:
//	void ChangeFaceCount( UINT _iFaceX, UINT _iFaceZ );
//	void CreateTerrainMesh();
//	Vec2 GetCollisionPos();
//
//public:
//	virtual void SaveToScene( FILE* _pFile );
//	virtual void LoadFromScene( FILE* _pFile );
//
//public:
//	CLONE( CTerrain );
//
//public:
//	CTerrain();
//	virtual ~CTerrain();
//};
//
