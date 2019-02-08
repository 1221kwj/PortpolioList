#include "stdafx.h"
#include "Program.h"

#include "003_Viewer/Freedom.h"

#include "004_Execute/Export.h"
#include "004_Execute/ModelEditor.h"

Program::Program()
{
	Context::Create();

	Context::Get()->GetMainCamera()->SetRotationDegree	( 0.0f, 0.0f );
	Context::Get()->GetMainCamera()->SetPosition		( 0.0f, 0.0f, -5.0f );

	( ( Freedom* )Context::Get()->GetMainCamera() )->SetMoveSpeed( 100.0f );

	D3DDesc desc;
	D3D::GetDesc( &desc );
	
	gpuDesc = desc.gpuDescription;

	// Executes
	executes.push_back( new Export() );
	executes.push_back( new ModelEditor() );
}

Program::~Program()
{
	for ( Execute* exe : executes )
		SAFE_DELETE( exe );

	Context::Delete();
}

void Program::Update()
{
	Context::Get()->Update();

	for ( Execute* exe : executes )
		exe->Update();
}

void Program::PreRender()
{
	for ( Execute* exe : executes )
		exe->PreRender();
}

void Program::Render()
{
	Context::Get()->GetViewport()->RSSetViewport();

	for ( Execute* exe : executes )
		exe->Render();
	
	ImGui::SliderFloat3( "Direction", ( float * )&Context::Get()->GetGlobalLight()->Direction, -1, 1 );
}

void Program::PostRender()
{
	for ( Execute* exe : executes )
		exe->PostRender();

	wstring str;
	RECT rect = { 0, 0, 300, 300 };

	str = String::Format( L"GPU Name : %s", gpuDesc.c_str() );
	DirectXWrite::RenderText( str, rect, 12 );

	rect.top += 12;
	str = String::Format( L"FPS      : %.0f", ImGui::GetIO().Framerate );
	DirectXWrite::RenderText( str, rect, 12 );

	Vector3 pos;
	rect.top += 12;
	Context::Get()->GetMainCamera()->GetPosition( &pos );
	str = String::Format( L"Position : %.0f, %.0f, %.0f", pos.x, pos.y, pos.z );
	DirectXWrite::RenderText( str, rect, 12 );

	Vector2 rot;
	rect.top += 12;
	Context::Get()->GetMainCamera()->GetRotationDegree( &rot );
	str = String::Format( L"Angle    : %.0f, %.0f", rot.x, rot.y );
	DirectXWrite::RenderText( str, rect, 12 );
}

void Program::ResizeScreen()
{
	D3DDesc desc;
	D3D::GetDesc( &desc );
	
	Context::Get()->GetPerspective()->Set( desc.Width, desc.Height );
	Context::Get()->GetViewport()	->Set( desc.Width, desc.Height );

	for ( Execute* exe : executes )
		exe->ResizeScreen();
}