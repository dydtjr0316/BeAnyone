#pragma once
#include "Component.h"

class CTransform :
	public CComponent

{
private:
	XMFLOAT3	m_vLocalPos;
	XMFLOAT3	m_vLocalRot;
	XMFLOAT3	m_vLocalScale;

	XMMATRIX	m_matWorld;

public:
	void SetLocalPos(const XMFLOAT3& _vPos) { m_vLocalPos = _vPos; }
	const XMFLOAT3& GetLocalPos() { return m_vLocalPos; }

public:
	virtual void finalupdate();

	// Transform ������ ��������� �� �������ͷ� �����Ѵ�.
	void UpdateData();

public:
	CTransform();
	virtual ~CTransform();
};

