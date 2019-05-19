#include "stdafx.h"
#include "ExeModel.h"

#include "./Model/Model.h"
#include "./Model/ModelPart.h"
#include "./Model/ModelSkeleton.h"
#include "./Model/Elements/ModelAnimation.h"
#include "./Model/ModelAnimationController.h"

#include "../BinExport/FbxLoader.h"
#include "../BinExport/ModelData.h"

#include "./Model/Gizmos/Gizmos.h"
#include "./Model/Gizmos/GizmosCapsule.h"

#include "../Utilities/Path.h"

ExeModel::ExeModel( ExecuteValues* values )
	: Execute				( values )
	, mData					( NULL )
	, values				( values )
	, materialsCheck		( false )
	, boneListCheck			( false )
	, animationCheck		( false )
	, modelProperty			( -1 )
	, ComboSelectModelName	( "" )
	, ComboSelectModelCount	( -1 )
	, shaderIndex			( -1 )
	, selectModelPartCount	( -1 )
{
	ExploreFolder( true, Shaders, "*.hlsl", shaderName );
	ExploreFolder( true, Textures, "*.png", textureName );
	ExploreFolder( false, Textures, "*.jpg", textureName );
	ExploreFolder( false, Textures, "*.bmp", textureName );
	ExploreFolder( true, AnimationFolder, "*.anim", animName );
}

ExeModel::~ExeModel()
{
	for ( Model* m : modelList )
		SAFE_DELETE( m );
	modelList.clear();

	SAFE_DELETE( mData );
}

void ExeModel::Update()
{
	for ( Model* m : modelList )
		m->Update();

	if ( Keyboard::Get()->Press( VK_CONTROL ) )
	{
		if ( Keyboard::Get()->Down( 'R' ) ) OpenConvertDialog();
		else if ( Keyboard::Get()->Down( 'O' ) ) OpenMeshDialog();
		else if ( Keyboard::Get()->Down( 'M' ) ) OpenModelDialog();
		else if ( Keyboard::Get()->Down( 'S' ) ) SaveModelDialog();
	}
}

void ExeModel::PreRender()
{

}

void ExeModel::Render()
{
	for ( Model* m : modelList )
		m->Render();
}

void ExeModel::PostRender()
{
	// FPS, POSITION, ROTATE
	D3DXVECTOR3 pos;
	D3DXVECTOR2 rot;
	values->MainCamera->GetPosition( &pos );
	values->MainCamera->GetRotation( &rot );

	// ImGui Render
	ImGui::Begin( "Window" );
	ImGui::SameLine();
	ImGui::Text( "POSITION : (%5.2f, %5.2f, %5.2f), ROTATE : (%5.2f, %5.2f)", pos.x, pos.y, pos.z, rot.x, rot.y );
	ImGui::End();
	
	MenuBarImGui();
	ModelEditorImGui();
	ListBoxImGui();

	if ( mData != NULL ) mData->RenderAnimBoneList();
}

void ExeModel::ResizeScreen()
{
}

void ExeModel::MenuBarImGui()
{
	if ( ImGui::BeginMainMenuBar() )
	{
		if ( ImGui::BeginMenu( "File" ) )
		{
			if ( ImGui::MenuItem( "Convert to Binary Mesh", "Ctrl+R" ) ) OpenConvertDialog();
			ImGui::Separator();
			if ( ImGui::MenuItem( "Open Binary Mesh", "Ctrl+O" ) ) OpenMeshDialog();
			if ( ImGui::MenuItem( "Open Binary Model", "Ctrl+M" ) ) OpenModelDialog();
			if ( ImGui::MenuItem( "Save Binary Mesh", "Ctrl+S" ) ) SaveModelDialog();
			ImGui::Separator();
			if ( ImGui::MenuItem( "Exit Program", "Alt+F4" ) ) PostQuitMessage( 0 );
			ImGui::EndMenu();
		}//if(BeiginMenu)

		ImGui::EndMainMenuBar();
	}
}

void ExeModel::ModelEditorImGui()
{
	D3DDesc desc;
	D3D::GetDesc( &desc );

	// Model List
	ImGui::SetNextWindowPos( ImVec2( 5, 20 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 150 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "Model List", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	{
		if ( ImGui::BeginCombo( "Model", ComboSelectModelName.c_str() ) )
		{
			for ( int i = 0; i < ( int )modelList.size(); i++ )
			{
				char flags[MAX_PATH];
				sprintf_s( flags, "%d. ", i );
				string selectName = string( flags ) + modelList[ i ]->GetName();
				if ( ImGui::Selectable( selectName.c_str() ) )
				{
					ComboSelectModelName = selectName;
					ComboSelectModelCount = i;
					selectModelPartCount = -1;
				}
			}
			ImGui::EndCombo();
		}
		
		ImGui::BulletText( "World Transform" );
		{
			if ( ComboSelectModelCount > -1 )
				modelList[ ComboSelectModelCount ]->ImGuiWorldTransform();
		}
	}
	ImGui::End();
	// Model List

	// Part List 
	ImGui::SetNextWindowPos( ImVec2( 5, 175 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 100 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "Parts List", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	{
		if ( ComboSelectModelCount > -1 )
		{
			int modelPartCount = modelList[ ComboSelectModelCount ]->GetModelPartSize();

			for ( int i = 0; i < modelPartCount; i++ )
			{
				ModelPart* part = modelList[ ComboSelectModelCount ]->GetModelPart( i );
				if ( ImGui::Selectable( part->GetName().c_str(), selectModelPartCount == i ) )
					selectModelPartCount = i;
				else
					modelList[ ComboSelectModelCount ]->GetModelPart( i )->ImGuiRender( false );
			}

			if ( selectModelPartCount > -1 )
				modelList[ ComboSelectModelCount ]->GetModelPart( selectModelPartCount )->ImGuiRender( true );
		}
	}
	ImGui::End();
	// Part List

	// Bone List
	ImGui::SetNextWindowPos( ImVec2( 5, 280 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 200 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "Bone List" );
	{
		if ( ComboSelectModelCount > -1 )
			modelList[ ComboSelectModelCount ]->ImGuiBoneRender();
	}
	ImGui::End();
	// Bone List

	// Animation List
	ImGui::SetNextWindowPos( ImVec2( 5, 485 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 200 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "Animation List" );
	{
		if ( ComboSelectModelCount > -1 )
			modelList[ ComboSelectModelCount ]->ImGuiAnimRender();
	}
	ImGui::End();
	// Animation List
}

void ExeModel::ListBoxImGui()
{
	D3DDesc desc;
	D3D::GetDesc( &desc );
	
	ImGui::SetNextWindowPos( ImVec2( desc.Width - 305, 20 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, desc.Height - 30 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "List Box", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	{
		// Shader List
		ImGui::BulletText( "Shader List" );
		ImGui::BeginChild( "ShaderList", ImVec2( 280, 120 ), true );
		{
			for ( size_t i = 0; i < shaderName.size(); i++ )
			{
				ImGui::Selectable( shaderName[ i ].c_str() );
				if ( ImGui::BeginDragDropSource() )
				{
					ImGui::SetDragDropPayload
					( 
						"_SHADERNAME",					// 저장 될 유일한 곳을 결정하는 곳
						shaderName[ i ].c_str(),		// 저장 될 데이터
						shaderName[ i ].length() + 1,	// 저장 될 데이터의 사이즈
						ImGuiCond_Once					// 이건 각 해당한 ENUM문을 참고하자
					);
					ImGui::Text( shaderName[ i ].c_str() );
					ImGui::EndDragDropSource();
				}
			}
		}
		ImGui::EndChild(); 

		if ( ImGui::Button( "ShaderList Refresh", ImVec2( 280, 25 ) ) )
			ExploreFolder( true, Shaders, "*.hlsl", shaderName );

		ImGui::Separator();

		// Texture List
		ImGui::BulletText( "Texture List" );
		ImGui::BeginChild( "TextureList", ImVec2( 280, 120 ), true );
		{
			for ( size_t i = 0; i < textureName.size(); i++ )
			{
				ImGui::Selectable( textureName[ i ].c_str() );
				if ( ImGui::BeginDragDropSource() )
				{
					ImGui::SetDragDropPayload
					(
						"_TEXTURENAME",					// 저장 될 유일한 곳을 결정하는 곳
						textureName[ i ].c_str(),		// 저장 될 데이터
						textureName[ i ].length() + 1,	// 저장 될 데이터의 사이즈
						ImGuiCond_Once					// 이건 각 해당한 ENUM문을 참고하자
					);
					ImGui::Text( textureName[ i ].c_str() );
					ImGui::EndDragDropSource();
				}
			}
		}
		ImGui::EndChild();

		if ( ImGui::Button( "Texture Refresh", ImVec2( 280, 25 ) ) )
		{
			ExploreFolder( true, Textures, "*.png", textureName );
			ExploreFolder( false, Textures, "*.jpg", textureName );
			ExploreFolder( false, Textures, "*.bmp", textureName );
		}

		ImGui::Separator();

		// Binary Animation List
		ImGui::BulletText( "BinAnimation List" );
		if ( ImGui::Button( "Convert To Bin Animation File", ImVec2( 280, 25 ) ) )
			ConvertToBinAnimation();

		ImGui::BeginChild( "AnimationList", ImVec2( 280, 120 ), true );
		{
			for ( size_t i = 0; i < animName.size(); i++ )
			{
				ImGui::Selectable( animName[ i ].c_str() );
				if ( ImGui::BeginDragDropSource() )
				{
					ImGui::SetDragDropPayload
					(
						"_ANIMATIONNAME",			
						animName[ i ].c_str(),		
						animName[ i ].length() + 1,	
						ImGuiCond_Once				
					);
					ImGui::Text( animName[ i ].c_str() );
					ImGui::EndDragDropSource();
				}
			}
		}
		ImGui::EndChild();

		if ( ImGui::Button( "AnimationList Refresh", ImVec2( 280, 25 ) ) )
			ExploreFolder( true, AnimationFolder, "*.anim", animName );

		ImGui::Separator();
	}
	ImGui::End();
}

void ExeModel::ConvertToBinAnimation()
{
	OpenAnimDialog();
}

void ExeModel::OpenConvertDialog( wstring file )
{
	D3DDesc desc;
	D3D::GetDesc( &desc );

	if ( file.length() < 1 )
	{
		function<void( wstring )> func = bind( &ExeModel::OpenConvertDialog, this, placeholders::_1 );
		Path::OpenFileDialog( L"", Path::FbxModelFilter, FbxModels, func, desc.Handle );
	}
	else
	{
		selectedFbxFile = file;
		{
			wstring fileName = Path::GetFileNameWithoutExtension( file );

			function<void( wstring )> func = bind( &ExeModel::Convert, this, placeholders::_1 );
			Path::SaveFileDialog( fileName, Path::BinMeshFilter, MeshModels, func, desc.Handle );
		}
		selectedFbxFile = L"";
	}
}

void ExeModel::Convert( wstring file )
{
	if ( selectedFbxFile.length() < 1 ) return;

	wstring saveFile = file + L".mesh";
	FbxLoader::Convert( selectedFbxFile, saveFile );

	D3DDesc desc;
	D3D::GetDesc( &desc );
	MessageBox( desc.Handle, L"변환 완료!", L"성공", MB_OK );
}



void ExeModel::OpenMeshDialog( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &ExeModel::OpenMeshDialog, this, placeholders::_1 );
		Path::OpenFileDialog( L"", Path::BinMeshFilter, MeshModels, func, desc.Handle );
	}
	else
	{
		Model* newModel = NULL;
		FbxLoader::LoadBinaryOnlyMesh( file, &newModel );
		modelList.push_back( newModel );
	}
}

void ExeModel::OpenModelDialog( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &ExeModel::OpenModelDialog, this, placeholders::_1 );
		Path::OpenFileDialog( L"", Path::BinModelFilter, BinModels, func, desc.Handle );
	}
	else
	{
		Model* newModel = NULL;
		FbxLoader::LoadBinary( file, &newModel );
		modelList.push_back( newModel );
	}
}

void ExeModel::OpenAnimDialog( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &ExeModel::OpenAnimDialog, this, placeholders::_1 );
		Path::OpenFileDialog( L"", Path::FbxModelFilter, FbxModels, func, desc.Handle );
	}
	else
	{
		SAFE_DELETE( mData );
		wstring name = Path::GetFileName( file );
		mData = FbxLoader::LoadFbxAnimation( file, name );
	}
}

void ExeModel::SaveModelDialog( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &ExeModel::SaveModelDialog, this, placeholders::_1 );
		Path::SaveFileDialog( file, Path::BinModelFilter, BinModels, func, desc.Handle );
	}
	else
	{
		file += L".model";
		FbxLoader::WriteBinary( file, modelList[ 0 ] );
	}
}

void ExeModel::ExploreFolder( bool bRefresh, string folderName, string extention, vector<string>& list )
{
	if (bRefresh == true ) list.clear();

	folderName += extention;
	struct _finddata_t fd;
	intptr_t handle;

	if ( ( handle = _findfirst( folderName.c_str(), &fd ) ) == -1L )
	{
		_findclose( handle );
		return;
	}
	assert( SUCCEEDED( handle ) );

	do
	{
		list.push_back( fd.name );
	} while ( _findnext( handle, &fd ) == 0 );
	_findclose( handle );
}

void ExeModel::ExploreFolder( bool bRefresh, wstring folderName, string extention, vector<string>& list )
{
	if ( bRefresh == true ) list.clear();

	string temp = String::WStringToString( folderName );
	string sFolderName = temp + extention;

	struct _finddata_t fd;
	intptr_t handle;

	if ( ( handle = _findfirst( sFolderName.c_str(), &fd ) ) == -1L )
	{
		_findclose( handle );
		return;
	}
	
	assert( SUCCEEDED( handle ) );

	do
	{
		list.push_back( fd.name );
	} while ( _findnext( handle, &fd ) == 0 );
	_findclose( handle );
}
