#include "stdafx.h"
#include "KeyMgr.h"

#include "Device.h"
#include "RenderMgr.h"

#define CAMERA_ROTATE_DIVIDE 20.f

// KEY_TYPE �� �����ϴ� ����Ű
int arrVK[(UINT)KEY_TYPE::KEY_END] =
{
	VK_UP,		// KEY_UP,
	VK_DOWN,	// KEY_DOWN,
	VK_LEFT,	// KEY_LEFT,
	VK_RIGHT,	// KEY_RIGHT,

	VK_SPACE,   // KEY_SPACE,
	VK_RETURN,  // KEY_ENTER,
	VK_LSHIFT,  // KEY_LSHIFT,
	VK_LCONTROL, // KEY_LCTRL,
	VK_MENU,	// KEY_LALT,
	VK_ESCAPE,	// KEY_ESC,

	'1',//KEY_1,
	'2',//KEY_2,
	'3',//KEY_3,
	'4',//KEY_4,
	'5',//KEY_5,
	'6',//KEY_6,
	'7',//KEY_7,
	'8',//KEY_8,
	'9',//KEY_9,
	'0',//KEY_0,

	'Q',		// KEY_Q,
	'W',
	'S',
	'A',
	'D',
	'E',
	'Z',
	'Y',

	VK_LBUTTON,
	VK_RBUTTON,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (UINT i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
	{
		m_vecKey.push_back(tKeyState{ KEY_STATE::STATE_NONE, false });
	}
}

void CKeyMgr::update()
{
	// ���� �����찡 Active(Ȱ��ȭ, ��Ŀ��) ���°� �ƴ϶��, 
	// ��� Ű ���¸� �ʱ���·� �����Ѵ�.
	HWND hActive = GetActiveWindow();

	if (nullptr == hActive)
	{
		for (UINT i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
		{
			m_vecKey[i].bPrevPress = false;
			m_vecKey[i].eState = KEY_STATE::STATE_NONE;
		}
		return;
	}

	// �����찡 Ȱ�����¶�� Ű�� ���������� update �Ѵ�.
	for (UINT i = 0; i < (UINT)KEY_TYPE::KEY_END; ++i)
	{
		// ���� Ű�� �����ִ�.
		if (GetAsyncKeyState(arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPress) // ���� �����ӿ� �����־���.
			{
				m_vecKey[i].eState = KEY_STATE::STATE_HOLD;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::STATE_TAB;
			}
			m_vecKey[i].bPrevPress = true;
		}
		else // Ű�� ������ ���� ����
		{
			if (m_vecKey[i].bPrevPress) // ���� �����ӿ� �����־���.
			{
				m_vecKey[i].eState = KEY_STATE::STATE_AWAY;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::STATE_NONE;
			}
			m_vecKey[i].bPrevPress = false;
		}
	}

	// ���콺 ��ǥ	
	m_ptOldMouse = m_ptMouse;
	GetCursorPos(&m_ptMouse);
	ScreenToClient(CRenderMgr::GetInst()->GetHwnd(), &m_ptMouse);

	m_vDragDir = Vec2((float)(m_ptMouse.x - m_ptOldMouse.x)/ CAMERA_ROTATE_DIVIDE, (float)(m_ptOldMouse.y - m_ptMouse.y) / CAMERA_ROTATE_DIVIDE);
}