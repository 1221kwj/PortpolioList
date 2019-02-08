#include "StdAfx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image(void)
: _imageInfo(NULL),
_fileName(NULL),
_tran(FALSE),
_transColor(RGB(0, 0, 0))
{
}

image::~image(void)
{
}

//�� ��Ʈ�� �����
HRESULT image::init(int width, int height)
{
	//�� �ʱ�ȭ �Ҷ� ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	_imageInfo						= new IMAGE_INFO;
	_imageInfo->loadType			= LOAD_EMPTY;
	_imageInfo->resID				= 0;
	_imageInfo->hMemDC				= CreateCompatibleDC(hdc);
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش� (ȭ��DC�� ����)

	_imageInfo->hBit				= (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit				= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x					= 0;
	_imageInfo->y					= 0;
	_imageInfo->width				= width;
	_imageInfo->height				= height;

	_fileName = NULL;

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_tran = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ���� �����ϸ�...
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� ���� (���Ϸκ��� �д´�)
HRESULT image::init(const char* fileName, int width, int height, BOOL tran, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ �Ҷ� ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo						= new IMAGE_INFO;
	_imageInfo->loadType			= LOAD_RESOURCE;
	_imageInfo->resID				= 0;
	_imageInfo->hMemDC				= CreateCompatibleDC(hdc);
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش� (ȭ��DC�� ����)

	_imageInfo->hBit				= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit				= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x					= 0;
	_imageInfo->y					= 0;
	_imageInfo->width				= width;
	_imageInfo->height				= height;


	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_tran = tran;
	_transColor = transColor;

	//���ҽ� ���� �����ϸ�...
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL tran, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ �Ҷ� ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo						= new IMAGE_INFO;
	_imageInfo->loadType			= LOAD_RESOURCE;
	_imageInfo->resID				= 0;
	_imageInfo->hMemDC				= CreateCompatibleDC(hdc);
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش� (ȭ��DC�� ����)

	_imageInfo->hBit				= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit				= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x					= x - (width / 2);
	_imageInfo->y					= y - (height / 2);
	_imageInfo->width				= width;
	_imageInfo->height				= height;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_tran = tran;
	_transColor = transColor;

	//���ҽ� ���� �����ϸ�...
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//�̹��� + ������ ���� �ʱ���
HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL tran, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ �Ҷ� ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo						= new IMAGE_INFO;
	_imageInfo->loadType			= LOAD_RESOURCE;
	_imageInfo->resID				= 0;
	_imageInfo->hMemDC				= CreateCompatibleDC(hdc);
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش� (ȭ��DC�� ����)

	_imageInfo->hBit				= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit				= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x					= x - (width / 2);
	_imageInfo->y					= y - (height / 2);
	_imageInfo->currentFrameX		= 0;
	_imageInfo->currentFrameY		= 0;
	_imageInfo->maxFrameX			= frameX - 1;
	_imageInfo->maxFrameY			= frameY - 1;
	_imageInfo->width				= width;
	_imageInfo->height				= height;
	_imageInfo->frameWidth			= width / frameX;
	_imageInfo->frameHeight			= height / frameY;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_tran = tran;
	_transColor = transColor;

	//���ҽ� ���� �����ϸ�...
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL tran, COLORREF transColor)
{
	//���� ��ΰ� �߸� �Ǿ��ٸ�
	if (fileName == NULL) return E_FAIL;

	//�� �ʱ�ȭ �Ҷ� ���...
	if (_imageInfo != NULL) release();

	//DC���´�
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����
	_imageInfo						= new IMAGE_INFO;
	_imageInfo->loadType			= LOAD_RESOURCE;
	_imageInfo->resID				= 0;
	_imageInfo->hMemDC				= CreateCompatibleDC(hdc);
	//��Ʈ���� ����ϱ� ���ؼ� �޸� DC�� ����� �ش� (ȭ��DC�� ����)

	_imageInfo->hBit				= (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit				= (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x					= 0;
	_imageInfo->y					= 0;
	_imageInfo->currentFrameX		= 0;
	_imageInfo->currentFrameY		= 0;
	_imageInfo->maxFrameX			= frameX - 1;
	_imageInfo->maxFrameY			= frameY - 1;
	_imageInfo->width				= width;
	_imageInfo->height				= height;
	_imageInfo->frameWidth			= width / frameX;
	_imageInfo->frameHeight			= height / frameY;

	//���� ��� �̸� �����Ѵ�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//���� DC�����Ѵ�
	ReleaseDC(_hWnd, hdc);

	//�����÷� �����Ѵ�
	_tran = tran;
	_transColor = transColor;

	//���ҽ� ���� �����ϸ�...
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	return S_OK;
}

//����
void image::release(void)
{
	if (_imageInfo)
	{
		//�̹��� �����Ѵ�
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ �����Ѵ� (���� �̸�)
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//���� �÷� �ʱ�ȭ
		_tran = false;
		_transColor = RGB(0, 0, 0);
	}
}

//���� Ű ����
void image::setTransColor(BOOL tran, COLORREF transColor)
{
	_tran = tran;
	_transColor = transColor;
}

//����
void image::render(HDC hdc)
{
	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			(int)_imageInfo->x,		//����� ��ǥ ������ x
			(int)_imageInfo->y,		//����� ��ǥ ������ y
			_imageInfo->width,		//����� ũ�� width
			_imageInfo->height,		//����� ũ�� height
			_imageInfo->hMemDC,		//������ DC
			0,						//���� �������� x
			0,						//���� �������� y
			_imageInfo->width,		//����� ���������Ѵ� width
			_imageInfo->height,		//����� ���������Ѵ� height
			_transColor				//���翡�� ������ ���� ���� (�÷�Ű)
			);
	}
	else
	{
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			_imageInfo->width,		//����� ũ�� width
			_imageInfo->height,		//����� ũ�� height
			_imageInfo->hMemDC,		//������ DC
			0,						//���� �������� x
			0,						//���� �������� y
			_imageInfo->width,		//����� ���������Ѵ� width
			_imageInfo->height,		//����� ���������Ѵ� height
			_transColor				//���翡�� ������ ���� ���� (�÷�Ű)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

void image::render(HDC hdc, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			(int)_imageInfo->x,		//����� ��ǥ ������ x
			(int)_imageInfo->y,		//����� ��ǥ ������ y
			_imageInfo->width,		//����� ũ�� width
			_imageInfo->height,		//����� ũ�� height
			_imageInfo->hMemDC,		//������ DC
			sourX,					//���� �������� x
			sourY,					//���� �������� y
			sourWidth,				//����� ���������Ѵ� width
			sourHeight,				//����� ���������Ѵ� height
			_transColor				//���翡�� ������ ���� ���� (�÷�Ű)
			);
	}
	else
	{
		BitBlt(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ x
			destY,					//����� ��ǥ ������ y
			sourWidth,				//����� ũ�� width
			sourHeight,				//����� ũ�� height
			_imageInfo->hMemDC,		//������ DC
			sourX,					//���� �������� x
			sourY,					//���� �������� y
			sourWidth,				//����� ���������Ѵ� width
			sourHeight,				//����� ���������Ѵ� height
			_transColor				//���翡�� ������ ���� ���� (�÷�Ű)
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

//������ ����
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(hdc, destX, destY,					
			_imageInfo->frameWidth, _imageInfo->frameHeight,				
			_imageInfo->hMemDC,		
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,					
			_imageInfo->frameWidth,				
			_imageInfo->frameHeight,				
			_transColor				
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if (currentFrameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if (_tran)
	{
		//TransparentBlt
		GdiTransparentBlt(hdc, destX, destY,					
			_imageInfo->frameWidth, _imageInfo->frameHeight,				
			_imageInfo->hMemDC,		
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,					
			_imageInfo->frameWidth,				
			_imageInfo->frameHeight,				
			_transColor				
			);
	}
	else
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, 
			_imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
		//bitblt DC���� �������� ���� ��Ӻ��縦 ���ش�
	}
}

