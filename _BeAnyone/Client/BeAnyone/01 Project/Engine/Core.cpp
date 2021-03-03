#include "pch.h"
#include "Core.h"

#include "Device.h"
#include "KeyMgr.h"
// #include "TimeMgr.h"
#include "ResMgr.h"

#include "SceneMgr.h"
#include "RenderMgr.h"

#include "PathMgr.h"
#include "ConstantBuffer.h"

CCore::CCore()
	: m_hMainHwnd(nullptr)
{
}

CCore::~CCore()
{
	TestRelease();
}

int CCore::init(HWND _hWnd, const tResolution& _resolution, bool _bWindow)
{
	m_hMainHwnd = _hWnd;
	ChangeWindowSize(m_hMainHwnd, _resolution);
	ShowWindow(_hWnd, true);

	if (FAILED(CDevice::GetInst()->initDirect3D (_hWnd, _resolution, _bWindow)))
	{
		return E_FAIL;
	}

	// ��� ���� �����
	CDevice::GetInst()->CreateConstBuffer(L"TRANSFORM_MATRIX", sizeof(tTransform), 512, CONST_REGISTER::b0);
	CDevice::GetInst()->CreateConstBuffer(L"MATERIAL_PARAM", sizeof(tMtrlParam), 512, CONST_REGISTER::b1);
	CDevice::GetInst()->CreateConstBuffer(L"ANIM2D", sizeof(tMtrlParam), 512, CONST_REGISTER::b2);

	// �Ŵ��� �ʱ�ȭ
	CPathMgr::init();
	CKeyMgr::GetInst()->init();
	// CTimeMgr::GetInst()->init();

	CResMgr::GetInst()->init();

	CSceneMgr::GetInst()->init();
	CRenderMgr::GetInst()->init(_hWnd, _resolution, _bWindow);

	// TestInit();

	return S_OK;
}

void CCore::ChangeWindowSize(HWND _hWnd, const tResolution& _resolution)
{
	RECT rt = { 0, 0, (int)_resolution.fWidth, (int)_resolution.fHeight };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CCore::progress()
{
    CKeyMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	CSceneMgr::GetInst()->update();
	// TestUpdate();
}

void CCore::lateupdate()
{

}

void CCore::finalupdate()
{

}

void CCore::render()
{
	CRenderMgr::GetInst()->render();
	// TestRender();
}