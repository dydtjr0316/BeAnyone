#include "pch.h"
#include "Transform.h"

#include "ConstantBuffer.h"
#include "Device.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{
}

CTransform::~CTransform()
{
}

void CTransform::finalupdate()
{
}

void CTransform::UpdateData()
{
	static CConstantBuffer* pCB = CDevice::GetInst()->GetCB(CONST_REGISTER::b0);

	XMFLOAT4 vData = XMFLOAT4(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z, 0.f);
	UINT iOffsetPos = pCB->AddData(&vData);
	CDevice::GetInst()->SetConstBufferToRegister(pCB, iOffsetPos);
}