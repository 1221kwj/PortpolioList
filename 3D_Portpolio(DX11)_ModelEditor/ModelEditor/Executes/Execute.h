#pragma once

#include "../Viewer/Camera.h"
#include "../Viewer/Perspective.h"
#include "../Viewer/Viewport.h"

struct ExecuteValues
{
	struct GuiSettings* GuiSettings;

	class GlobalLightBuffer* GlobalLight;
	class ViewProjectionBuffer* ViewProjection;

	class Perspective* Perspective;
	class Viewport* Viewport;
	class Camera* MainCamera;
};

class Execute
{
public:
	Execute(ExecuteValues* settings)
	{
		this->values = settings;
	}

	virtual void Update() = 0;

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void ResizeScreen() = 0;

protected:
	ExecuteValues* values;
};