#pragma once
#include "Component.h"

class CTransform :
	public CComponent

{
private:
	XMFLOAT3	m_vLocalPos;	// GameObect 좌표
	XMFLOAT3	m_vLocalRot;	// GameObject 크기
	XMFLOAT3	m_vLocalScale;	// GameObject 회전량

	XMFLOAT3	m_vLocalDir[(UINT)DIR_TYPE::END]; // GameObject 의 Front, Up, Right 방향
	XMFLOAT3	m_vWorldDir[(UINT)DIR_TYPE::END]; // GameObject 의 Front, Up, Right 방향

	XMMATRIX	m_matWorld;

public:
	void SetLocalPos(const XMFLOAT3& _vPos) { m_vLocalPos = _vPos; }
	const XMFLOAT3& GetLocalPos() { return m_vLocalPos; }

public:
	virtual void finalupdate();

	// Transform 정보를 상수데이터 및 레지스터로 전달한다.
	void UpdateData();

public:
	CTransform();
	virtual ~CTransform();
};

