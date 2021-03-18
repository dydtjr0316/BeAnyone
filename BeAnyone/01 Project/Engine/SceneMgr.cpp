#include "pch.h"
#include "SceneMgr.h"

#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"

#include "ResMgr.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Camera.h"

#include "Device.h"
#include "Core.h"

#include "MeshRenderer.h"
#include "ToolCamScript.h"
#include "RenderMgr.h"
#include "Terrain.h"
//#include "Animator2D.h"
//#include "Animation2D.h"
//#include "Collider2D.h"
#include "Light3D.h"
//#include "CollisionMgr.h"
//#include "EventMgr.h"
#include "PlayerScript.h"
#include "GridScript.h"
//#include "MonsterScript.h"

CScene* CSceneMgr::GetCurScene() {
	return m_pCurScene;
}

void CSceneMgr::ChangeScene( CScene* _pNextScene ) {
	SAFE_DELETE( m_pCurScene );
	m_pCurScene = _pNextScene;
}

CSceneMgr::CSceneMgr()
	: m_pCurScene( nullptr ) {
}

CSceneMgr::~CSceneMgr() {
	SAFE_DELETE( m_pCurScene );
}

void CSceneMgr::init() {

	// Texture 로드
	Ptr<CTexture> pTex = CResMgr::GetInst()->Load<CTexture>( L"TestTex", L"Texture\\cookie.png" );
	Ptr<CTexture> pColor = CResMgr::GetInst()->Load<CTexture>( L"Tile", L"Texture\\Tile\\TILE_03.tga" );
	Ptr<CTexture> pNormal = CResMgr::GetInst()->Load<CTexture>( L"Tile_n", L"Texture\\Tile\\TILE_03_N.tga" );

	Ptr<CTexture> pDiffuseTargetTex = CResMgr::GetInst()->FindRes<CTexture>( L"DiffuseTargetTex" );
	Ptr<CTexture> pNormalTargetTex = CResMgr::GetInst()->FindRes<CTexture>( L"NormalTargetTex" );
	Ptr<CTexture> pPositionTargetTex = CResMgr::GetInst()->FindRes<CTexture>( L"PositionTargetTex" );

	// Test Scene 생성
	m_pCurScene = new CScene;
	m_pCurScene->SetName( L"Test Scene" );

	// Layer 이름 지정
	m_pCurScene->GetLayer( 0 )->SetName( L"Default" );

	CGameObject* pObject = nullptr;

	// Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName( L"MainCam" );
	pMainCam->AddComponent( new CTransform );
	pMainCam->AddComponent( new CCamera );
	pMainCam->AddComponent( new CToolCamScript );

	pMainCam->Camera()->SetProjType( PROJ_TYPE::PERSPECTIVE );
	pMainCam->Camera()->SetFar( 1000000.f );
	pMainCam->Camera()->SetLayerAllCheck();

	m_pCurScene->GetLayer( 0 )->AddGameObject( pMainCam );

	// 3D Light Object
	pObject = new CGameObject;
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CLight3D );

	pObject->Light3D()->SetLightPos( Vec3( 0.f, 500.f, 1000.f ) );
	pObject->Light3D()->SetLightType( LIGHT_TYPE::DIR );
	pObject->Light3D()->SetDiffuseColor( Vec3( 1.f, 1.f, 1.f ) );
	pObject->Light3D()->SetSpecular( Vec3( 0.3f, 0.3f, 0.3f ) );
	pObject->Light3D()->SetAmbient( Vec3( 0.1f, 0.1f, 0.1f ) );
	pObject->Light3D()->SetLightDir( Vec3( 1.f, -1.f, 1.f ) );
	pObject->Light3D()->SetLightRange( 1000.f );

	pObject->Transform()->SetLocalPos( Vec3( -1000.f, 1000.f, -1000.f ) );
	m_pCurScene->GetLayer( 0 )->AddGameObject( pObject );

	// temp 오브젝트 생성
	pObject = new CGameObject;
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CMeshRender );
	pObject->AddComponent( new CPlayerScript );

	// Transform 설정
	pObject->Transform()->SetLocalPos( Vec3( 300.f, 400.f, 700.f ) );
	pObject->Transform()->SetLocalScale( Vec3( 150.f, 150.f, 150.f ) );

	// MeshRender 설정
	pObject->MeshRender()->SetMesh( CResMgr::GetInst()->FindRes<CMesh>( L"SphereMesh" ) );
	pObject->MeshRender()->SetMaterial( CResMgr::GetInst()->FindRes<CMaterial>( L"TestMtrl" ) );
	pObject->MeshRender()->GetSharedMaterial()->SetData( SHADER_PARAM::TEX_0, pTex.GetPointer() );
	pObject->MeshRender()->GetSharedMaterial()->SetData( SHADER_PARAM::TEX_1, pNormal.GetPointer() );

	// AddGameObject
	m_pCurScene->GetLayer( 0 )->AddGameObject( pObject );

	// Grid 오브젝트 생성
	// ====================
	pObject = new CGameObject;
	pObject->SetName( L"Grid" );
	pObject->FrustumCheck( false );
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CMeshRender );
	pObject->AddComponent( new CGridScript );

	// Transform 설정
	pObject->Transform()->SetLocalScale( Vec3( 100000.f, 100000.f, 1.f ) );
	pObject->Transform()->SetLocalRot( Vec3( XM_PI / 2.f, 0.f, 0.f ) );

	// MeshRender 설정
	pObject->MeshRender()->SetMesh( CResMgr::GetInst()->FindRes<CMesh>( L"RectMesh" ) );
	pObject->MeshRender()->SetMaterial( CResMgr::GetInst()->FindRes<CMaterial>( L"GridMtrl" ) );

	// Script 설정	
	pObject->GetScript<CGridScript>()->SetToolCamera( pMainCam );
	pObject->GetScript<CGridScript>()->SetGridColor( Vec3( 0.8f, 0.2f, 0.2f ) );

	// AddGameObject
	m_pCurScene->GetLayer( 0 )->AddGameObject( pObject );

	// Terrain
	// ========
	pObject = new CGameObject;
	pObject->SetName( L"Terrain" );
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CMeshRender );
	pObject->AddComponent( new CTerrain );

	pObject->FrustumCheck( false );
	pObject->Transform()->SetLocalPos( Vec3( 0.f, 100.f, 0.f ) );
	pObject->Transform()->SetLocalScale( Vec3( 50.f, 300.f, 50.f ) );
	pObject->MeshRender()->SetMaterial( CResMgr::GetInst()->FindRes<CMaterial>( L"TerrainMtrl" ) );
	pObject->Terrain()->init();

	m_pCurScene->FindLayer( L"Default" )->AddGameObject( pObject );

	// Script 설정
	//pObject->AddComponent( new CPlayerScript );

	m_pCurScene->awake();
	m_pCurScene->start();
}

void CSceneMgr::update() {
	m_pCurScene->update();
	m_pCurScene->lateupdate();

	// rendermgr 카메라 초기화
	CRenderMgr::GetInst()->ClearCamera();

	m_pCurScene->finalupdate();

	// 충돌 처리
	//CCollisionMgr::GetInst()->update();
}

void CSceneMgr::update_tool() {
	// rendermgr 카메라 초기화
	CRenderMgr::GetInst()->ClearCamera();
	m_pCurScene->finalupdate();
}

void CSceneMgr::FindGameObjectByTag( const wstring& _strTag, vector<CGameObject*>& _vecFindObj ) {
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		const vector<CGameObject*>& vecObject = m_pCurScene->GetLayer( i )->GetObjects();
		for (size_t j = 0; j < vecObject.size(); ++j)
		{
			if (_strTag == vecObject[j]->GetName())
			{
				_vecFindObj.push_back( vecObject[j] );
			}
		}
	}
}

bool Compare( CGameObject* _pLeft, CGameObject* _pRight ) {
	return (_pLeft->Transform()->GetWorldPos().z < _pRight->Transform()->GetWorldPos().z);
}

//void CSceneMgr::FindGameObjectByPoint(POINT _point, vector<CGameObject*>& _vecFindObj, CCamera* _pToolCam)
//{
//	CCamera* pCam = _pToolCam;
//	if (CCore::GetInst()->GetSceneMod() == SCENE_MOD::SCENE_PLAY)
//	{
//		pCam = CRenderMgr::GetInst()->GetCamera(0);
//	}
//
//	tResolution tRes = CRenderMgr::GetInst()->GetResolution();
//	Vec3 vPickPos = Vec3((float)_point.x - (tRes.fWidth / 2.f), (tRes.fHeight / 2.f) - (float)_point.y, 0.f);
//	vPickPos *= pCam->GetScale(); 
//	vPickPos += pCam->Transform()->GetWorldPos();
//
//	for (int i = 0; i < MAX_LAYER; ++i)
//	{
//		const vector<CGameObject*>& vecObject = m_pCurScene->GetLayer(i)->GetObjects();
//		for (size_t j = 0; j < vecObject.size(); ++j)
//		{
//			if (vecObject[j]->Transform()->IsCasting(vPickPos))
//			{
//				_vecFindObj.push_back(vecObject[j]);
//			}
//		}
//	}
//
//	sort(_vecFindObj.begin(), _vecFindObj.end(), Compare);
//}

