#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Light3D.h"

#include "SceneMgr.h"

#include "TimeMgr.h"
#include "EventMgr.h"
#include "ResMgr.h"

CRenderMgr::CRenderMgr()
{

}

CRenderMgr::~CRenderMgr() {
}

void CRenderMgr::init( HWND _hWnd, const tResolution& _res, bool _bWindow ) {
	m_hWnd = _hWnd;
	m_tResolution = _res;
	m_bWindowed = _bWindow;

	CreateSamplerState();

	CreateBlendState();

	CreateDepthStencilState();
}

void CRenderMgr::render() {
	// 초기화
	float arrColor[4] = {0.0f,0.0f, 0.1f, 1.f};
	CDevice::GetInst()->render_start( arrColor );

	// 광원 정보 업데이트
	UpdateLight3D();

	// Render Light
	//render_lights();

	// Merge (Diffuse Target, Diffuse Light Target, Specular Target )		
	//merge_light();

	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->render();
	}

	// 출력
	CDevice::GetInst()->render_present();
}

void CRenderMgr::render_tool() {
	// 초기화
	float arrColor[4] = {0.f, 0.f, 0.f, 1.f};
	//Clear(arrColor);

	// 광원 정보 업데이트
	UpdateLight3D();
}

void CRenderMgr::CreateSamplerState() {

}

void CRenderMgr::CreateBlendState() {

}

void CRenderMgr::CreateDepthStencilState() {
}

CCamera* CRenderMgr::GetMainCam() {
	/*if (CCore::GetInst()->GetSceneMod() == SCENE_MOD::SCENE_PLAY)
	{
		if (!m_vecCam.empty())
			return m_vecCam[0];
		return nullptr;
	}*/

	return  m_vecCam[0];
}

void CRenderMgr::UpdateLight3D() {
	static CConstantBuffer* pLight3DBuffer = CDevice::GetInst()->GetCB( CONST_REGISTER::b4 );

	tLight3DInfo tLight3DArray;

	for (size_t i = 0; i < m_vecLight3D.size(); ++i)
	{
		const tLight3D& info = m_vecLight3D[i]->GetLight3DInfo();
		tLight3DArray.arrLight3D[i] = info;
	}
	tLight3DArray.iCurCount = (UINT)m_vecLight3D.size();

	UINT iOffsetPos = pLight3DBuffer->AddData( &tLight3DArray );
	CDevice::GetInst()->SetConstBufferToRegister( pLight3DBuffer, iOffsetPos );
}

void CRenderMgr::render_lights() {

	// 광원을 그린다.
	CCamera* pMainCam = CRenderMgr::GetInst()->GetMainCam();
	if (nullptr == pMainCam)
		return;

	// 메인 카메라 시점 기준 View, Proj 행렬로 되돌린다.
	g_transform.matView = pMainCam->GetViewMat();
	g_transform.matProj = pMainCam->GetProjMat();
	g_transform.matViewInv = pMainCam->GetViewMatInv();

	for (size_t i = 0; i < m_vecLight3D.size(); ++i)
	{
		m_vecLight3D[i]->Light3D()->render();
	}

	m_vecLight3D.clear();
	//m_arrMRT[(UINT)MRT_TYPE::LIGHT]->TargetToResBarrier();

	//// SwapChain MRT 셋팅
	//UINT iIdx = CDevice::GetInst()->GetSwapchainIdx();
	//m_arrMRT[(UINT)MRT_TYPE::SWAPCHAIN]->OMSet( 1, iIdx );
}

void CRenderMgr::merge_light() {
	// ========================
	// Merge (Diffuse + Lights)
	// ========================
	static Ptr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>( L"RectMesh" );
	static Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>( L"MergeLightMtrl" );

	pMtrl->UpdateData();
	pRectMesh->render();
}