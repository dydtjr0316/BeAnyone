#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "Camera.h"

#include "SceneMgr.h"
#include "ConstantBuffer.h"

#include "TimeMgr.h"
#include "EventMgr.h"

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
	/*UpdateLight2D();
	UpdateLight3D();*/

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
	/*UpdateLight2D();
	UpdateLight3D();*/
}

void CRenderMgr::CreateSamplerState() {

}

void CRenderMgr::CreateBlendState() {

}

void CRenderMgr::CreateDepthStencilState() {
}

