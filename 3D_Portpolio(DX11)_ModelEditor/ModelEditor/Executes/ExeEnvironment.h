#pragma once
#include "Execute.h"

class ExeEnvironment : public Execute
{
public:
	ExeEnvironment(ExecuteValues* values);
	~ExeEnvironment();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void ResizeScreen();

private:
	class Sky* sky;
	class Floor* floor;
};