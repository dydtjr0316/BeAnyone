#pragma once
#include "Component.h"

class CTransform :
	public CComponent

{
private:
	XMFLOAT3	m_vLocalPos;	// GameObect ��ǥ
	XMFLOAT3	m_vLocalRot;	// GameObject ũ��
	XMFLOAT3	m_vLocalScale;	// GameObject ȸ����

	XMFLOAT3	m_vLocalDir[(UINT)DIR_TYPE::END]; // GameObject �� Front, Up, Right ����
	XMFLOAT3	m_vWorldDir[(UINT)DIR_TYPE::END]; // GameObject �� Front, Up, Right ����

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

