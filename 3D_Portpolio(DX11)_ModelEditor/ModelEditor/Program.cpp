#include "stdafx.h"
#include "Program.h"

#include "./Viewer/FirstPerson.h"

#include "./Executes/Execute.h"
#include "./Executes/ExeEnvironment.h"
#include "./Executes/ExeModel.h"
#include "./Executes/ExeGui.h"

Program::Program()
{
	States::Create();

	D3DDesc desc;
	D3D::GetDesc(&desc);

	values = new ExecuteValues();
	values->GuiSettings = new GuiSettings();
	values->GlobalLight = new GlobalLightBuffer();
	values->ViewProjection = new ViewProjectionBuffer();
	values->Perspective = new Perspective(desc.Width, desc.Height);
	values->Viewport = new Viewport(desc.Width, desc.Height);
	values->MainCamera = new FirstPerson();

	values->MainCamera->SetPosition(-6.68f, 139.46f, 348.95f);
	values->MainCamera->SetRotation( D3DXVECTOR2( 0.07f, 3.14f ) );
	
	executes.push_back(new ExeEnvironment(values));
	executes.push_back(new ExeModel(values));
	executes.push_back(new ExeGui(values));
}

Program::~Program()
{
	for (Execute* exe : executes)
		SAFE_DELETE(exe);

	SAFE_DELETE(values->GuiSettings);
	SAFE_DELETE(values->GlobalLight);
	SAFE_DELETE(values->ViewProjection);
	SAFE_DELETE(values->Perspective);
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values->Viewport);
	SAFE_DELETE(values);
	
	States::Delete();
}

void Program::Update()
{
	for (Execute* exe : executes)
		exe->Update();
}

void Program::PreRender()
{
	values->MainCamera->Update();

	for (Execute* exe : executes)
		exe->PreRender();
}

void Program::Render()
{
	D3DXMATRIX view, projection;
	values->MainCamera->GetMatrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);

	D3DXVECTOR3 cameraPosition;
	values->MainCamera->GetPosition( &cameraPosition );
	values->ViewProjection->SetViewPosition( cameraPosition );

	values->ViewProjection->SetVSBuffer(0);

	values->GlobalLight->SetPSBuffer(0);

	for (Execute* exe : executes)
		exe->Render();
}

void Program::PostRender()
{
	for (Execute* exe : executes)
		exe->PostRender();
}

void Program::ResizeScreen()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);
	
	values->Perspective->Set(desc.Width, desc.Height);
	values->Viewport->Set(desc.Width, desc.Height);

	for (Execute* exe : executes)
		exe->ResizeScreen();
}
