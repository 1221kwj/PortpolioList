#include "stdafx.h"
#include "ExeGui.h"

ExeGui::ExeGui(ExecuteValues* values)
	: Execute(values)
{
	
}

ExeGui::~ExeGui()
{

}

void ExeGui::Update()
{
	if (Keyboard::Get()->Press(VK_CONTROL))
	{
		if (Keyboard::Get()->Down(VK_F2))
			ChangeShowEnvironmentWindow();

		if (Keyboard::Get()->Down(VK_F11))
			ChangeShowSystemInfoWindow();

		if (Keyboard::Get()->Down(VK_F12))
			ChangeShowDemoWindow();
	}
}

void ExeGui::PreRender()
{

}

void ExeGui::Render()
{
	
}

void ExeGui::PostRender()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Environment", "Ctrl+F2"))
				ChangeShowEnvironmentWindow();

			if (ImGui::MenuItem("Demo", "Ctrl+F11"))
				ChangeShowSystemInfoWindow();

			if (ImGui::MenuItem("Demo", "Ctrl+F12"))
				ChangeShowDemoWindow();

			ImGui::EndMenu();
		}//if(BeiginMenu)

		ImGui::EndMainMenuBar();
	}

	if (values->GuiSettings->bShowSystemInfoWindow == true)
	{
		ImGui::Begin("System Info", &values->GuiSettings->bShowSystemInfoWindow);
		ImGui::LabelText("FPS", "%4d", (int)ImGui::GetIO().Framerate);
		ImGui::End();
	}

	if (values->GuiSettings->bShowDemoWindow == true)
	{
		ImGui::ShowDemoWindow(&values->GuiSettings->bShowDemoWindow);
	}
}

void ExeGui::ResizeScreen()
{

}

void ExeGui::ChangeShowDemoWindow()
{
	values->GuiSettings->bShowDemoWindow = !values->GuiSettings->bShowDemoWindow;
}

void ExeGui::ChangeShowEnvironmentWindow()
{
	values->GuiSettings->bShowEnvironmentWindow = !values->GuiSettings->bShowEnvironmentWindow;
}

void ExeGui::ChangeShowSystemInfoWindow()
{
	values->GuiSettings->bShowSystemInfoWindow = !values->GuiSettings->bShowSystemInfoWindow;
}
