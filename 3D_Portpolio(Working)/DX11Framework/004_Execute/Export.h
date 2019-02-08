#pragma once

class Export : public Execute
{
public:
	Export();
	~Export() {}

	void Update()		{}
	void PreRender()	{}
	void Render()		{}
	void PostRender()	{}
	void ResizeScreen() {}
};