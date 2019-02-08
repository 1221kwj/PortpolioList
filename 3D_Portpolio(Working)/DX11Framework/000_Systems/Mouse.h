#pragma once

#define MAX_INPUT_MOUSE 8

class Mouse
{
public:
	static Mouse* Get();

	static void Create();
	static void Delete();

private:
	Mouse();
	~Mouse();

public:
	void SetHandle( HWND handle ) { this->handle = handle; }
	void Update();

	LRESULT InputProc( UINT message, WPARAM wParam, LPARAM lParam );

	void GetPosition( Vector3* vec )	{ *vec = position; }
	void GetMoveValue( Vector3* vec )	{ *vec = wheelMoveValue; }
	
	bool Down( DWORD button )	{ return buttonMap[ button ] == BUTTON_INPUT_STATUS_DOWN; }
	bool Up( DWORD button )		{ return buttonMap[ button ] == BUTTON_INPUT_STATUS_UP; }
	bool Press( DWORD button )	{ return buttonMap[ button ] == BUTTON_INPUT_STATUS_PRESS; }


private:
	static Mouse* instance;

	HWND	handle;
	Vector3	position; //마우스 위치

	byte	buttonStatus	[ MAX_INPUT_MOUSE ];
	byte	buttonOldStatus[ MAX_INPUT_MOUSE ];
	byte	buttonMap		[ MAX_INPUT_MOUSE ];

	Vector3 wheelStatus;
	Vector3 wheelOldStatus;
	Vector3 wheelMoveValue;

	DWORD	timeDblClk;
	DWORD	startDblClk[ MAX_INPUT_MOUSE ];
	int		buttonCount[ MAX_INPUT_MOUSE ];

	enum
	{
		MOUSE_ROTATION_NONE = 0	,
		MOUSE_ROTATION_LEFT		,
		MOUSE_ROTATION_RIGHT
	};

	enum
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN	,
		BUTTON_INPUT_STATUS_UP		,
		BUTTON_INPUT_STATUS_PRESS	,
		BUTTON_INPUT_STATUS_DBLCLK
	};
};