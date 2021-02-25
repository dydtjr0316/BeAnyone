#include "pch.h"
#include "global.h"

D3D12_RASTERIZER_DESC g_arrRSDesc[(UINT)RS_TYPE::END] =
{
	D3D12_RASTERIZER_DESC
	{
		  D3D12_FILL_MODE_SOLID // FillMode
		, D3D12_CULL_MODE_BACK	//CullMode
		, FALSE //FrontCounterClockwise
		, D3D12_DEFAULT_DEPTH_BIAS //DepthBias
		, D3D12_DEFAULT_DEPTH_BIAS_CLAMP //DepthBiasClamp
		, D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS	//SlopeScaledDepthBias
		, TRUE	//DepthClipEnable
		, FALSE	//MultisampleEnable
		, FALSE	//AntialiasedLineEnable
		, 0		//ForcedSampleCount
		, D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF	//ConservativeRaster
	},
};

D3D12_BLEND_DESC g_arrBlendDesc[(UINT)BLEND_TYPE::END] =
{
	D3D12_BLEND_DESC{
		FALSE ,  // AlphaToCoverageEnable
		FALSE , // IndependentBlendEnable

		D3D12_RENDER_TARGET_BLEND_DESC
		{
			FALSE,FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL,
		},
	}
};

D3D12_DEPTH_STENCIL_DESC g_arrDepthStencilDesc[(UINT)DEPTH_STENCIL_TYPE::END] =
{
	// LESS
	D3D12_DEPTH_STENCIL_DESC{
		TRUE,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS,
	},

	//LESS_EQUAL,
	D3D12_DEPTH_STENCIL_DESC{
		TRUE,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
	},

	//GRATER,
	D3D12_DEPTH_STENCIL_DESC{
		TRUE,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_GREATER,
	},

	//GRATER_EQUAL,
	D3D12_DEPTH_STENCIL_DESC{
		FALSE,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_NEVER,
	},

	//NO_DEPTHTEST, ���� �׽�Ʈ X, ���̱�� o
	D3D12_DEPTH_STENCIL_DESC{
		FALSE,
		D3D12_DEPTH_WRITE_MASK_ALL,
		D3D12_COMPARISON_FUNC_LESS,
	},

	// NO_DEPTHTEST_NO_WRITE, �����׽�Ʈ X, ���̱�� X
	D3D12_DEPTH_STENCIL_DESC{
		FALSE,
		D3D12_DEPTH_WRITE_MASK_ZERO,
	},

	//LESS_NO_WRITE, // �����׽�Ʈ o (Less), ���̱�� X
	D3D12_DEPTH_STENCIL_DESC{
		TRUE,
		D3D12_DEPTH_WRITE_MASK_ZERO,
		D3D12_COMPARISON_FUNC_LESS,
	}
};