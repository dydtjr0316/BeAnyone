#pragma once

class CCamera;
class CLight3D;

//class CBlendState;
//class CDepthStencilState;
//class CRenderTarget24;


#include "Ptr.h"
#include "Texture.h"

class CRenderMgr
{
	SINGLE( CRenderMgr );

private:
	Ptr<CTexture>			m_pRenderTargetTex;
	Ptr<CTexture>			m_pDepthStencilTex;

	tResolution				m_tResolution;

	vector<CCamera*>		m_vecCam;

	HWND					m_hWnd;
	bool					m_bWindowed;

	/*CRenderTarget24* m_arrRT[(UINT)RT_TYPE::END];
	CMRT* m_arrMRT[(UINT)MRT_TYPE::END];*/

	//tLight2DInfo			m_tLight2DInfo;

	vector<CLight3D*>		m_vecLight3D;

public:
	void init( HWND _hWnd, const tResolution& _res, bool _bWindow );
	void render();
	void render_tool();

private:
	void CreateSamplerState();
	void CreateBlendState();
	void CreateDepthStencilState();

	void UpdateLight3D();
	void render_lights();
	void merge_light();

public:
	int RegisterLight3D( CLight3D* _pLight3D ) {
		if (m_vecLight3D.size() >= 100)
			return -1;
		m_vecLight3D.push_back( _pLight3D );
		return (int)m_vecLight3D.size() - 1;
	}

	CCamera* GetMainCam();
	CCamera* GetCamera( int _iIdx ) { return m_vecCam[_iIdx]; }
	void RegisterCamera( CCamera* _pCam ) { m_vecCam.push_back( _pCam ); }
	void ClearCamera() { m_vecCam.clear(); }
	CCamera* getMain() { return nullptr; };

	tResolution GetResolution() { return m_tResolution; }
	HWND GetHwnd() { return m_hWnd; }

	friend class CSceneMgr;
};


