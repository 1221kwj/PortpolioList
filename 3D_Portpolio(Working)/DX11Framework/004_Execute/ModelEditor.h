#pragma once

class ModelEditor : public Execute
{
public:
	ModelEditor();
	~ModelEditor();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void ResizeScreen();

private:
	class Sky*		sky;
	class Terrain*	terrain;
};