#include "stdafx.h"
#include "ExeEnvironment.h"
#include "../Environment/Sky.h"
#include "../Environment/Floor.h"

ExeEnvironment::ExeEnvironment(ExecuteValues* values)
	: Execute(values)
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	sky = new Sky();
	floor = new Floor();
}

ExeEnvironment::~ExeEnvironment()
{
	SAFE_DELETE(floor);
	SAFE_DELETE(sky);
}

void ExeEnvironment::Update()
{
	sky->Update(values->MainCamera);
	floor->Update();
}

void ExeEnvironment::PreRender()
{
	
}

void ExeEnvironment::Render()
{
	sky->Render();
	floor->Render();
}

void ExeEnvironment::PostRender()
{
	if (values->GuiSettings->bShowEnvironmentWindow == true)
	{
		ImGui::Begin("Environment", &values->GuiSettings->bShowEnvironmentWindow);
		ImGui::Text("Light");
		ImGui::Separator();

		ImGui::SliderFloat3("Direction", (float *)&values->GlobalLight->Data.Direction, -1, 1);
		ImGui::End();
	}

	sky->PostRender(values->GuiSettings);
	floor->PostRender(values->GuiSettings);
}

void ExeEnvironment::ResizeScreen()
{
	
}
