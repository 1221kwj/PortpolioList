#pragma once

class Material
{
private:
	class Buffer;

public:
	Material();
	Material( wstring shaderFile );
	~Material();

	void	Name( wstring val ) { name = val; }
	wstring Name()				{ return name; }

	Shader* GetShader() { return shader; }
	void SetShader( string file );
	void SetShader( wstring file );

	Vector4 GetAmbient() { return color.Ambient; }
	void SetAmbient( Vector4& ambient );
	void SetAmbient( float r, float g, float b, float a = 1.0f );

	Vector4 GetDiffuse() { return color.Diffuse; }
	void SetDiffuse( Vector4& diffuse );
	void SetDiffuse( float r, float g, float b, float a = 1.0f );

	Vector4 GetSpecular() { return color.Specular; }
	void SetSpecular( Vector4& specular );
	void SetSpecular( float r, float g, float b, float a = 1.0f );

	float GetShininess() { return color.Shininess; }
	void  SetShininess( float val );

	Texture* GetDiffuseMap() { return diffuseMap; }
	void SetDiffuseMap( string file , D3DX11_IMAGE_LOAD_INFO* info = NULL );
	void SetDiffuseMap( wstring file, D3DX11_IMAGE_LOAD_INFO* info = NULL );

	Texture* GetSpecularMap() { return specularMap; }
	void SetSpecularMap( string file , D3DX11_IMAGE_LOAD_INFO* info = NULL );
	void SetSpecularMap( wstring file, D3DX11_IMAGE_LOAD_INFO* info = NULL );

	Texture* GetNormalMap() { return normalMap; }
	void SetNormalMap( string file , D3DX11_IMAGE_LOAD_INFO* info = NULL );
	void SetNormalMap( wstring file, D3DX11_IMAGE_LOAD_INFO* info = NULL );

public:
	void Clone( Material** clone );

private:
	wstring		name;
	Shader*		shader;

	Texture*	diffuseMap;
	Texture*	specularMap;
	Texture*	normalMap;

private:
	struct ColorDesc
	{
		Vector4 Ambient;
		Vector4 Diffuse;
		Vector4 Specular;

		float Shininess;
		float Padding[ 3 ];
	} color;
	
	CBuffer* buffer;
};