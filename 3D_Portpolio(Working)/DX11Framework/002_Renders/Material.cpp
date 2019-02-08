#include "stdafx.h"
#include "Material.h"

Material::Material()
	: shader		( NULL )
	, diffuseMap	( NULL )
	, specularMap	( NULL )
	, normalMap		( NULL )
	, buffer		( NULL )
{
	color.Ambient	= Vector4::ColorZero();
	color.Diffuse	= Vector4::ColorZero();
	color.Specular	= Vector4::ColorZero();
	color.Shininess = 0.0f;
}

Material::Material( wstring shaderFile )
	: shader		( NULL )
	, diffuseMap	( NULL )
	, specularMap	( NULL )
	, normalMap		( NULL )
{
	assert( shaderFile.length() > 0 );

	color.Ambient	= Vector4::ColorZero();
	color.Diffuse	= Vector4::ColorZero();
	color.Specular	= Vector4::ColorZero();
	color.Shininess = 0.0f;

	SetShader( shaderFile );
}

Material::~Material()
{
	SAFE_DELETE( shader );

	SAFE_DELETE( buffer );
	SAFE_DELETE( diffuseMap );
	SAFE_DELETE( specularMap );
	SAFE_DELETE( normalMap );
}

void Material::SetShader( string file )
{
	SetShader( String::ToWString( file ) );
}

void Material::SetShader( wstring file )
{
	SAFE_DELETE( shader );

	if ( file.length() > 0 )
	{
		shader = new Shader( file );
		buffer = new CBuffer( shader, "CB_Material", &color, sizeof( ColorDesc ) );

		if ( diffuseMap != NULL )
			shader->GetAsShaderResource( "DiffuseMap" )	->SetResource( diffuseMap->GetSRV() );

		if ( specularMap != NULL )
			shader->GetAsShaderResource( "SpecularMap" )->SetResource( specularMap->GetSRV() );

		if ( normalMap != NULL )
			shader->GetAsShaderResource( "NormalMap" )	->SetResource( normalMap->GetSRV() );
	}
}

void Material::SetAmbient( Vector4 & ambient )
{
	if ( color.Ambient == ambient || buffer == NULL ) return;

	color.Ambient = ambient;
	buffer->Change();
}

void Material::SetAmbient( float r, float g, float b, float a )
{
	SetAmbient( Vector4( r, g, b, a ) );
}

void Material::SetDiffuse( Vector4 & diffuse )
{
	if ( color.Diffuse == diffuse || buffer == NULL ) return;

	color.Diffuse = diffuse;
	buffer->Change();
}

void Material::SetDiffuse( float r, float g, float b, float a )
{
	SetDiffuse( Vector4( r, g, b, a ) );
}

void Material::SetSpecular( Vector4 & specular )
{
	if ( color.Specular == specular || buffer == NULL ) return;

	color.Specular = specular;
	buffer->Change();
}

void Material::SetSpecular( float r, float g, float b, float a )
{
	SetSpecular( Vector4( r, g, b, a ) );
}

void Material::SetShininess( float val )
{
	if ( color.Shininess == val || buffer == NULL ) return;

	color.Shininess = val;
	buffer->Change();
}

void Material::SetDiffuseMap( string file, D3DX11_IMAGE_LOAD_INFO * info )
{
	SetDiffuseMap( String::ToWString( file ), info );
}

void Material::SetDiffuseMap( wstring file, D3DX11_IMAGE_LOAD_INFO * info )
{
	if ( diffuseMap != NULL )
		if ( diffuseMap->GetFile() == file ) return;

	SAFE_DELETE( diffuseMap );
	diffuseMap = new Texture( file, info );

	if ( shader != NULL )
		shader->GetAsShaderResource( "DiffuseMap" )->SetResource( diffuseMap->GetSRV() );
}

void Material::SetSpecularMap( string file, D3DX11_IMAGE_LOAD_INFO * info )
{
	SetSpecularMap( String::ToWString( file ), info );
}

void Material::SetSpecularMap( wstring file, D3DX11_IMAGE_LOAD_INFO * info )
{
	if ( specularMap != NULL )
		if ( specularMap->GetFile() == file ) return;

	SAFE_DELETE( specularMap );
	specularMap = new Texture( file, info );

	if ( shader != NULL )
		shader->GetAsShaderResource( "SpecularMap" )->SetResource( specularMap->GetSRV() );
}

void Material::SetNormalMap( string file, D3DX11_IMAGE_LOAD_INFO * info )
{
	SetNormalMap( String::ToWString( file ), info );
}

void Material::SetNormalMap( wstring file, D3DX11_IMAGE_LOAD_INFO * info )
{
	if ( normalMap != NULL )
		if ( normalMap->GetFile() == file ) return;

	SAFE_DELETE( normalMap );
	normalMap = new Texture( file, info );

	if ( shader != NULL )
		shader->GetAsShaderResource( "NormalMap" )->SetResource( normalMap->GetSRV() );
}

void Material::Clone( Material ** clone )
{
	Material* material	= new Material();
	material->name		= name;

	if ( this->shader != NULL )
		material->SetShader( shader->GetFile() );

	material->SetDiffuse	( GetDiffuse() );
	material->SetSpecular	( GetSpecular() );

	if ( diffuseMap != NULL )
		material->SetDiffuseMap( diffuseMap->GetFile() );

	if ( specularMap != NULL )
		material->SetSpecularMap( specularMap->GetFile() );

	if ( normalMap != NULL )
		material->SetNormalMap( normalMap->GetFile() );

	material->SetShininess( GetShininess() );

	*clone = material;
}