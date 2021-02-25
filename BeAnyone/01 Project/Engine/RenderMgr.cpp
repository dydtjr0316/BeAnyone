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
	// �ʱ�ȭ
	float arrColor[4] = {0.0f,0.0f, 0.1f, 1.f};
	CDevice::GetInst()->render_start( arrColor );

	// ���� ���� ������Ʈ
	/*UpdateLight2D();
	UpdateLight3D();*/

	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->render();
	}

	// ���
	CDevice::GetInst()->render_present();
}

void CRenderMgr::render_tool() {
	// �ʱ�ȭ
	float arrColor[4] = {0.f, 0.f, 0.f, 1.f};
	//Clear(arrColor);

	// ���� ���� ������Ʈ
	/*UpdateLight2D();
	UpdateLight3D();*/
}

void CRenderMgr::CreateSamplerState() {

}

void CRenderMgr::CreateBlendState() {

}

void CRenderMgr::CreateDepthStencilState() {
}

