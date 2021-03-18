#include "pch.h"
#include "Terrain.h"

#include "RenderMgr.h"

#include "Camera.h"
#include "Transform.h"

#include "ResMgr.h"
#include "MeshRenderer.h"
#include "Shader.h"

void CTerrain::init() {
	ChangeFaceCount( m_iFaceX, m_iFaceZ );

	Ptr<CMaterial> pMtrl = MeshRender()->GetSharedMaterial();
	pMtrl->SetData( SHADER_PARAM::INT_1, &m_iFaceX );
	pMtrl->SetData( SHADER_PARAM::INT_2, &m_iFaceZ );

	// 높이맵 텍스쳐 Create
	m_pHeightMap = CResMgr::GetInst()->Load<CTexture>( L"HeightMap", L"Texture\\Terrain\\HeightMap_01.png" );
	Vec2 vHeightMapRes = Vec2( m_pHeightMap->Width(), m_pHeightMap->Height() );

	// 타일 텍스쳐
	Ptr<CTexture> pTile = CResMgr::GetInst()->FindRes<CTexture>( L"Texture\\Tile\\TILE_01.tga" );
	Ptr<CTexture> pTile_n = CResMgr::GetInst()->FindRes<CTexture>( L"Texture\\Tile\\TILE_01_N.tga" );

	pMtrl->SetData( SHADER_PARAM::TEX_2, m_pHeightMap.GetPointer() );
	pMtrl->SetData( SHADER_PARAM::VEC2_0, &vHeightMapRes );
	pMtrl->SetData( SHADER_PARAM::FLOAT_0, &m_fMaxTess );


}

void CTerrain::ChangeFaceCount( UINT _iFaceX, UINT _iFaceZ ) {
	m_iFaceX = _iFaceX;
	m_iFaceZ = _iFaceZ;

	CreateTerrainMesh();
}

void CTerrain::CreateTerrainMesh() {
	vector<VTX> vecVtx;
	vector<UINT> vecIdx;

	Ptr<CMesh> pMesh = nullptr;

	// =============	
	// Terrain Mesh		
	// =============	
	pMesh = new CMesh;

	VTX v;

	for (UINT i = 0; i < m_iFaceZ + 1; ++i)
	{
		for (UINT j = 0; j < m_iFaceX + 1; ++j)
		{
			v.vPos = Vec3( (float)j, 0.f, (float)i );
			v.vColor = Vec4( 1.f, 1.f, 1.f, 1.f );
			v.vUV = Vec2( (float)j, (float)(m_iFaceZ - i) );
			v.vNormal = Vec3( 0.f, 1.f, 0.f );
			v.vTangent = Vec3( 1.f, 0.f, 0.f );
			v.vBinormal = Vec3( 0.f, 0.f, 1.f );
			vecVtx.push_back( v );
		}
	}

	for (UINT i = 0; i < m_iFaceZ; ++i)
	{
		for (UINT j = 0; j < m_iFaceX; ++j)
		{
			// 0       
			// | \  
			// 2--1 
			vecIdx.push_back( (m_iFaceX + 1) * (i + 1) + j );
			vecIdx.push_back( (m_iFaceX + 1) * i + j + 1 );
			vecIdx.push_back( (m_iFaceX + 1) * i + j );

			// 1--2
			//  \ |
			//	  0
			vecIdx.push_back( (m_iFaceX + 1) * (i)+(j + 1) );
			vecIdx.push_back( (m_iFaceX + 1) * (i + 1) + j );
			vecIdx.push_back( (m_iFaceX + 1) * (i + 1) + j + 1 );
		}
	}

	pMesh->Create( sizeof( VTX ), (UINT)vecVtx.size(), (BYTE*)vecVtx.data()
				   , DXGI_FORMAT_R32_UINT, (UINT)vecIdx.size(), (BYTE*)vecIdx.data() );

	Ptr<CMesh> pOriginMesh = CResMgr::GetInst()->FindRes<CMesh>( L"TerrainMesh" );
	if (nullptr != pOriginMesh)
	{
		CResMgr::GetInst()->DestroyResource<CMesh>( L"TerrainMesh" );
	}

	CResMgr::GetInst()->AddRes<CMesh>( L"TerrainMesh", pMesh );

	MeshRender()->SetMesh( pMesh );
}