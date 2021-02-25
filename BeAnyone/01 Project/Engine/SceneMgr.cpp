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

//#include "Animator2D.h"
//#include "Animation2D.h"
//#include "Collider2D.h"
//#include "Light2D.h"
//#include "Light3D.h"
//#include "CollisionMgr.h"
//#include "EventMgr.h"
#include "PlayerScript.h"
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

	// Test Scene 생성
	m_pCurScene = new CScene;
	m_pCurScene->SetName( L"Test Scene" );

	// Layer 이름 지정
	m_pCurScene->GetLayer( 0 )->SetName( L"Default" );

	CGameObject* pObject = nullptr;

	// Camera Object 생성
	pObject = new CGameObject;
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CCamera );
	pObject->AddComponent( new CToolCamScript );

	pObject->Camera()->SetProjType( PROJ_TYPE::PERSPECTIVE );
	pObject->Camera()->SetFar( 100000.f );
	pObject->Camera()->SetLayerAllCheck();

	m_pCurScene->GetLayer( 0 )->AddGameObject( pObject );

	// temp 오브젝트 생성
	pObject = new CGameObject;
	pObject->AddComponent( new CTransform );
	pObject->AddComponent( new CMeshRender );

	// Transform 설정
	pObject->Transform()->SetLocalPos( Vec3( 0.f, 0.f, 500.f ) );
	pObject->Transform()->SetLocalScale( Vec3( 150.f, 150.f, 1.f ) );

	// MeshRender 설정
	pObject->MeshRender()->SetMesh( CResMgr::GetInst()->FindRes<CMesh>( L"RectMesh" ) );
	pObject->MeshRender()->SetMaterial( CResMgr::GetInst()->FindRes<CMaterial>( L"TestMtrl" ) );
	pObject->MeshRender()->GetSharedMaterial()->SetData( SHADER_PARAM::TEX_0, pTex.GetPointer() );

	// Script 설정
	pObject->AddComponent( new CPlayerScript );

	// AddGameObject
	m_pCurScene->GetLayer( 0 )->AddGameObject( pObject );

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

