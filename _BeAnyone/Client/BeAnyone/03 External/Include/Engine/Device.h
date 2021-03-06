#pragma once

class CConstantBuffer;
class CTexture;

class CDevice
{
	SINGLE(CDevice);

public:
	HWND			m_hWnd;
	tResolution		m_tResolution;
	bool			m_bWindowed;

private:
	ComPtr<ID3D12Fence>						m_pFence;
	ComPtr<IDXGIFactory>					m_pFactory;
	ComPtr<ID3D12Device>					m_pDevice;
	ComPtr<ID3D12CommandQueue>				m_pCommandQueue;

	// 렌더링 커맨드 리스트
	ComPtr<ID3D12CommandAllocator>			m_pCmdListAlloc;
	ComPtr<ID3D12GraphicsCommandList>		m_pCommandList;

	// 리소스 로딩 커맨드 리스트
	ComPtr<ID3D12CommandAllocator>			m_pCmdListAllocRes;
	ComPtr<ID3D12GraphicsCommandList>		m_pCommandListRes;

	// SwapChain
	static const int						SwapChainBufferCount = 2;
	UINT									m_iCurTargetIdx = 0;
	
	ComPtr<IDXGISwapChain>					m_pSwapChain;
	
	ComPtr<ID3D12Resource>					m_pSwapChainBuffer[SwapChainBufferCount];
	ComPtr<ID3D12Resource>					m_pDepthStencilBuffer;

	// View
	ComPtr<ID3D12DescriptorHeap>			m_pRtvHeap;
	ComPtr<ID3D12DescriptorHeap>			m_pDsvHeap;

	vector<ComPtr<ID3D12DescriptorHeap>>	m_vecDummyDescriptor;
	UINT									m_iCurDummyIdx;
	ComPtr<ID3D12DescriptorHeap>			m_pInitDescriptor;

	UINT m_iRtvDescriptorSize = 0;
	UINT m_iDsvDescriptorSize = 0;
	UINT m_iCbvSrvUavDescriptorSize = 0;

	vector<D3D12_STATIC_SAMPLER_DESC>		m_vecSamplerDesc;
	D3D12_VIEWPORT							m_tScreenViewport;
	D3D12_RECT								m_tScissorRect;

	// fence
	HANDLE									m_hFenceEvent;
	UINT64									m_iFenceValue = 0;

	vector<CConstantBuffer*>				m_vecCB;

private:
	ComPtr<ID3D12RootSignature>	m_arrSig[(UINT)ROOT_SIG_TYPE::END];

public:
	int initDirect3D(HWND _hWnd, const tResolution& _res, bool _bWindow);

	void CreateConstBuffer(const wstring& _strName, size_t _iBufferOffset,
		size_t _iMaxCount, CONST_REGISTER _eRegisterNum, bool _bGlobal = false);

	void render_start(float(&_arrFloat)[4]);

	void render_present();
	void FlushCommandQueue();

	void SetConstBufferToRegister(CConstantBuffer* _pCB, UINT _iOffset);
	void SetGlobalConstBufferToRegister(CConstantBuffer* _pCB, UINT _iOffset);
	void SetTextureToRegister(CTexture* _pTex, TEXTURE_REGISTER _eRegister);

	

	void UpdateTable();
	void ExcuteResourceLoad();

private:
	void CreateCommandObjects();	// Command
	void CreateSwapChain();			// Swap Chain
	void CreateRtvAndDsvDescriptorHeaps();	// DescriptorHeaps
	void CreateView();				// View
	void CreateViewPort();			// ViewPort
	void CreateRootSignature();
	void CreateSamplerDesc();

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;

public:
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return m_pCommandList; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdListRes() { return m_pCommandListRes; }
	ComPtr<ID3D12Device> GetDevice() { return m_pDevice; }
	ComPtr<ID3D12RootSignature> GetRootSignature(ROOT_SIG_TYPE _eType) { return m_arrSig[(UINT)_eType]; }
	CConstantBuffer* GetCB(CONST_REGISTER _eRegister) { return m_vecCB[(UINT)_eRegister]; }
};

