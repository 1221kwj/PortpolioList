#pragma once

class Program;
class APIWindow
{
public:
	APIWindow();
	~APIWindow();

	WPARAM Run();

private:
	static LRESULT CALLBACK WndProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	static Program* program;
};