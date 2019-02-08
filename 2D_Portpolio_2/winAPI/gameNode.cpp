#include "StdAfx.h"
#include "gameNode.h"

gameNode::gameNode(void)
{
}

gameNode::~gameNode(void)
{
}

HRESULT gameNode::init(void) //init, setup, create...
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	Sound1 = LoadWAV(_hWnd, "bossBGM.wav");
	Sound2 = LoadWAV(_hWnd, "slashSound.WAV");
	return S_OK;
}

HRESULT gameNode::init(bool mangerInit) //init, setup, create...
{
	_hdc = GetDC(_hWnd);
	_managerInit = mangerInit;

	if (_managerInit)
	{
		KEYMANAGER->init();		//Ű �Ŵ��� ����
		IMAGEMANAGER->init();	//�̹��� �Ŵ��� ����
		TIMEMANAGER->init();	//Ÿ�ӸŴ��� ����
	}

	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
		//���� �̱��� ����
		RND->releaseSingleton();

		//Ű �Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();

		//�̹��� �Ŵ��� �̱��� ����
		IMAGEMANAGER->releaseSingleton();

		//Ÿ�� �Ŵ��� �̱��� ����
		TIMEMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

//������Ʈ (����� ���� ���� ��ġ �ݿ�...) == WM_TIMER
void gameNode::update(void)
{
}

//���� (ȭ�� ���� �� ��� ����Ѵ�) == WM_PAINT
void gameNode::render(void)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, 
		WPARAM wParam, LPARAM lParam)
{
	switch ( iMessage )
	{
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));
		break;
		case WM_KEYDOWN:
			switch ( wParam )
			{
				//ESCŰ.....
				case VK_ESCAPE:
					PostMessage( hWnd, WM_DESTROY, 0, 0 );
				break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
		break;
	}

	//������ ���ν������� ó������ ���� ������ �޽��� ó���Ѵ�.
	return ( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
}
