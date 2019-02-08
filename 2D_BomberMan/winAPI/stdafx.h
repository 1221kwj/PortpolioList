// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

//================================================
//####### 2017.03.20 ������� �β���� #############
//================================================
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN //MFC�� �ƴ� ���� ���α׷���
//��쿡�� WIN32_LEAN_AND_MEAN�� ������ ���� �ð��� �����Ų��.

#include <windows.h> //������ ��� ��Ŭ���

#include <stdio.h> //���Ĵٵ� ����� ������� ��Ŭ���
//printf, scanf, puts, gets.. ���
#include <tchar.h> //�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���
//TextOut, DrawText, wsprintf..���..

//������Ʈ�� �⺻������ �����ڵ���. ����, �ѱ� ��� 2����Ʈ...
//MBCS (Multi Byte Character Set) -> 
//������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ���
//WBCS (Wide Byte Character Set) ->
//��� ���ڿ��� 2����Ʈ�� ó���Ѵ�.. �����ڵ� ���..

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "utils.h"

//================================================
//############### 2017.03.20 ������ ###############
//================================================

using namespace MY_UTIL;

#define WINNAME (LPSTR)(TEXT("APIWindow"))
#define WINSTARTX 150
#define WINSTARTY 150
#define WINSIZEX 674 //14ĭ��
#define WINSIZEY 674 //14ĭ��
#define WINCENTER (PointMake(WINSIZEX / 2, WINSIZEY / 2))
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{ if(p) {delete		(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{ if(p) {delete[]	(p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) {(p)->release(); (p) = NULL;}}

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()

//================================================
//############### 2017.03.20 �������� ###############
//================================================
extern HINSTANCE	_hInstance; //���α׷� �ν��Ͻ�
extern HWND			_hWnd;		//������ �ڵ�
extern POINT		_ptMouse;	//���콺


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.