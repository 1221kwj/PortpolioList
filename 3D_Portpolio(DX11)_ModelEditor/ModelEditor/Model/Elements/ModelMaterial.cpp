#include "stdafx.h"
#include "ModelMaterial.h"
#include "../Buffer/ModelBuffer.h"
#include "../../BinExport/FbxData.h"
#include "../../Utilities/String.h"

ModelMaterial::ModelMaterial(const MaterialData& data)
	: number				( -1 )
	, ambientFile			( "" )
	, emissiveFile			( "" )
	, diffuseFile			( "" )
	, specularFile			( "" )
	, ambientView			( NULL )
	, diffuseView			( NULL )
	, normalView			( NULL )
	, specularView			( NULL )
	, emissiveView			( NULL )
	, shader				( NULL )
	, shaderFile			( "" )
	, ComboSelectShaderName	( "" )
	
{
	materialBuffer = new MaterialBuffer();

	number = data.number;
	name = data.name;

	SetAmbient(data.ambient);
	SetDiffuse(data.diffuse);
	SetNormal( data.normal );
	SetSpecular(data.specular);
	SetEmissive(data.emissive);

	SetAmbientTexture(data.ambientFile);
	SetDiffuseTexture(data.diffuseFile);
	SetNormalTexture( data.normalFile );
	SetSpecularTexture(data.specularFile);
	SetEmissiveTexture(data.emissiveFile);

	SetShader(data.shaderFile);

}

ModelMaterial::ModelMaterial(const ModelMaterial & copy)
	: number				( -1 )
	, ambientFile			( "" )
	, emissiveFile			( "" )
	, diffuseFile			( "" )
	, normalFile			( "" )
	, specularFile			( "" )
	, ambientView			( NULL )
	, diffuseView			( NULL )
	, normalView			( NULL )
	, specularView			( NULL )
	, emissiveView			( NULL )
	, shader				( NULL )
	, shaderFile			( "" )
	, ComboSelectShaderName	( "" )
{
	materialBuffer = new MaterialBuffer();

	number = copy.number;
	name = copy.name;

	SetAmbient( copy.materialBuffer->GetAmbient() );
	SetDiffuse( copy.materialBuffer->GetDiffuse() );
	SetNormal( copy.materialBuffer->GetNormal() );
	SetSpecular( copy.materialBuffer->GetSpecular() );
	SetEmissive( copy.materialBuffer->GetEmissive() );

	SetAmbientTexture( copy.ambientFile );
	SetDiffuseTexture( copy.diffuseFile );
	SetNormalTexture( copy.normalFile );
	SetSpecularTexture( copy.specularFile );
	SetEmissiveTexture( copy.emissiveFile );

	SetShader(copy.shaderFile);
}

ModelMaterial::~ModelMaterial()
{
	SAFE_RELEASE(ambientView);
	SAFE_RELEASE(emissiveView);
	SAFE_RELEASE(diffuseView);
	SAFE_RELEASE(specularView);

	SAFE_DELETE(materialBuffer);
	SAFE_DELETE(shader);
}

const D3DXCOLOR & ModelMaterial::GetAmbient()
{
	return materialBuffer->GetAmbient();
}

const D3DXCOLOR & ModelMaterial::GetDiffuse()
{
	return materialBuffer->GetDiffuse();
}

const D3DXCOLOR & ModelMaterial::GetNormal()
{
	return materialBuffer->GetNormal();
}

const D3DXCOLOR & ModelMaterial::GetSpecular()
{
	return materialBuffer->GetSpecular();
}

const D3DXCOLOR & ModelMaterial::GetEmissive()
{
	return materialBuffer->GetEmissive();
}

float ModelMaterial::GetShininess()
{
	return materialBuffer->GetShininess();
}

void ModelMaterial::CreateTexture(const string & file, ID3D11ShaderResourceView ** view)
{
	DWORD fileValue = GetFileAttributesA(file.c_str());
	if (fileValue < 0xFFFFFFFF)
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileA
		(
			D3D::GetDevice()
			, file.c_str()
			, NULL
			, NULL
			, view
			, NULL
		);
		assert(SUCCEEDED(hr));
	}
}

void ModelMaterial::SetShader(const string & file)
{
	SAFE_DELETE(shader);

	shaderFile = file;

	if (shaderFile == "0")
	{
		shader = new Shader(Shaders + L"Model.hlsl");
		shaderFile = String::WStringToString( Shaders + L"Model.hlsl" );
	}
	else
	{
		wstring temp = String::StringToWString(file);
		shader = new Shader(temp);
	}
}

void ModelMaterial::SetShader(const wstring & file)
{
	string temp = String::WStringToString(file);

	SetShader(temp);
}


void ModelMaterial::SetAmbient(const D3DXCOLOR & color)
{
	materialBuffer->SetAmbient(color);
}

void ModelMaterial::SetDiffuse(const D3DXCOLOR & color)
{
	materialBuffer->SetDiffuse(color);
}

void ModelMaterial::SetNormal( const D3DXCOLOR & color )
{
	materialBuffer->SetNormal( color );
}

void ModelMaterial::SetSpecular(const D3DXCOLOR & color)
{
	materialBuffer->SetSpecular(color);
}

void ModelMaterial::SetEmissive(const D3DXCOLOR & color)
{
	materialBuffer->SetEmissive(color);
}

void ModelMaterial::SetShininess(const float & shininess)
{
	materialBuffer->SetShininess(shininess);
}

void ModelMaterial::SetAmbientTexture(const string & file)
{
	SAFE_RELEASE(ambientView);

	ambientFile = file;
	CreateTexture(file, &ambientView);
}

void ModelMaterial::SetDiffuseTexture(const string & file)
{
	SAFE_RELEASE(diffuseView);

	diffuseFile = file;
	CreateTexture(file, &diffuseView);
}

void ModelMaterial::SetNormalTexture( const string & file )
{
	SAFE_RELEASE( normalView );

	normalFile = file;
	CreateTexture( file, &normalView );
}

void ModelMaterial::SetSpecularTexture(const string & file)
{
	SAFE_RELEASE(specularView);

	specularFile = file;
	CreateTexture(file, &specularView);
}

void ModelMaterial::SetEmissiveTexture(const string & file)
{
	SAFE_RELEASE(emissiveView);

	emissiveFile = file;
	CreateTexture(file, &emissiveView);
}

void ModelMaterial::SetPSBuffer()
{
	// Diffuse
	if (diffuseView == NULL)
	{
		ID3D11ShaderResourceView* n[1]{ NULL };
		D3D::GetDC()->PSSetShaderResources(0, 1, n);
	}
	else
		D3D::GetDC()->PSSetShaderResources(0, 1, &diffuseView);

	// Normal
	if ( normalView == NULL )
	{
		ID3D11ShaderResourceView* n[ 1 ]{ NULL };
		D3D::GetDC()->PSSetShaderResources( 1, 1, n );
	}
	else
		D3D::GetDC()->PSSetShaderResources( 1, 1, &normalView );

	// Specular
	if ( specularView == NULL )
	{
		ID3D11ShaderResourceView* n[ 1 ]{ NULL };
		D3D::GetDC()->PSSetShaderResources( 2, 1, n );
	}
	else
		D3D::GetDC()->PSSetShaderResources( 2, 1, &specularView );

	materialBuffer->SetPSBuffer(1);
	shader->Render();
}

void ModelMaterial::ImGuiRender( bool bSelect )
{
	if ( bSelect == true )
	{
		// Shader
		ImGui::BulletText( "Shader   : " ); ImGui::SameLine();
		char temp[ MAX_PATH ];
		strcpy_s( temp, ( Path::GetFileName( shaderFile ) ).c_str() );
		ImGui::PushItemWidth( 200 );
		ImGui::InputText( "Shader Name", temp, MAX_PATH );

		if ( ImGui::BeginDragDropTarget() )
		{
			if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( "_SHADERNAME", ImGuiCond_Once ) )
			{
				memcpy( temp, payload->Data, sizeof( temp ) );
				shaderFile = string( "../_Shaders/" ) + string( temp );
				SetShader( shaderFile );
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::Separator();

		// Diffuse
		ImGui::BulletText( "Diffuse  : " ); ImGui::SameLine();
		strcpy_s( temp, ( Path::GetFileName( diffuseFile ) ).c_str() );
		ImGui::PushItemWidth( 200 );
		ImGui::InputText( "DiffuseName", temp, MAX_PATH );
		if ( ImGui::BeginDragDropTarget() )
		{
			if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( "_TEXTURENAME", ImGuiCond_Once ) )
			{
				memcpy( temp, payload->Data, sizeof( temp ) );
				diffuseFile = string( "../_Contents/Textures/" ) + string( temp );
				SetDiffuseTexture( diffuseFile );
			}
			ImGui::EndDragDropTarget();
		}

		D3DXCOLOR diffuseColor = materialBuffer->GetDiffuse();
		ImGui::ColorEdit4( "DiffuseColor", diffuseColor );
		{
			materialBuffer->SetDiffuse( diffuseColor );
		}
		ImGui::Separator();

		// Normal
		ImGui::BulletText( "Normal   : " ); ImGui::SameLine();
		strcpy_s( temp, ( Path::GetFileName( normalFile ) ).c_str() );
		ImGui::PushItemWidth( 200 );
		ImGui::InputText( "NormalName", temp, MAX_PATH );
		if ( ImGui::BeginDragDropTarget() )
		{
			if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( "_TEXTURENAME", ImGuiCond_Once ) )
			{
				memcpy( temp, payload->Data, sizeof( temp ) );
				normalFile = string( "../_Contents/Textures/" ) + string( temp );
				SetNormalTexture( normalFile );
			}
			ImGui::EndDragDropTarget();
		}

		D3DXCOLOR normalColor = materialBuffer->GetNormal();
		ImGui::ColorEdit4( "NormalColor", normalColor );
		{
			materialBuffer->SetNormal( normalColor );
		}
		ImGui::Separator();

		// Specular
		ImGui::BulletText( "Specular : " ); ImGui::SameLine();
		strcpy_s( temp, ( Path::GetFileName( specularFile ) ).c_str() );
		ImGui::PushItemWidth( 200 );
		ImGui::InputText( "SpecularName", temp, MAX_PATH );
		if ( ImGui::BeginDragDropTarget() )
		{
			if ( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload( "_TEXTURENAME", ImGuiCond_Once ) )
			{
				memcpy( temp, payload->Data, sizeof( temp ) );
				specularFile = string( "../_Contents/Textures/" ) + string( temp );
				SetSpecularTexture( specularFile );
			}
			ImGui::EndDragDropTarget();
		}

		D3DXCOLOR specularColor = materialBuffer->GetSpecular();
		ImGui::ColorEdit4( "SpecularColor", specularColor );
		{
			materialBuffer->SetSpecular( specularColor );
		}
		ImGui::Separator();

		// TODO : Add Ambient, Add Emssive, Add Shiness
	}
}
