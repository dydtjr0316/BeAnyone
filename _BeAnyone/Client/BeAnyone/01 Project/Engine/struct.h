#pragma once

struct tResolution
{
	float fWidth;
	float fHeight;
};

// 정점 구조체
struct VTX
{
	XMFLOAT3 vPos;
	XMFLOAT4 vColor;
	XMFLOAT2 vUV;
};

struct tTransform
{
	XMFLOAT4 vOffset;
};
