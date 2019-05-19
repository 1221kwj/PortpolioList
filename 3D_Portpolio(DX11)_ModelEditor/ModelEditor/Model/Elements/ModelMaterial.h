#pragma once

class ModelMaterial
{
	friend class ModelData;
	friend struct MaterialData;

public:
	virtual ~ModelMaterial();

	bool CanRender() { return shader != NULL; }
	UINT GetNumber() { return number; }
	string GetName() { return name; }

	const D3DXCOLOR& GetAmbient();
	const D3DXCOLOR& GetDiffuse();
	const D3DXCOLOR& GetNormal();
	const D3DXCOLOR& GetSpecular();
	const D3DXCOLOR& GetEmissive();
	float GetShininess();

	string GetShaderFile() { return shaderFile; }
	string GetAmbientTexture() { return ambientFile; }
	string GetDiffuseTexture() { return diffuseFile; }
	string GetNormalTexture() { return normalFile; }
	string GetSpecularTexture() { return specularFile; }
	string GetEmissiveTexture() { return emissiveFile; }

	void SetAmbient(const D3DXCOLOR& color);
	void SetDiffuse(const D3DXCOLOR& color);
	void SetNormal( const D3DXCOLOR& color );
	void SetSpecular(const D3DXCOLOR& color);
	void SetEmissive(const D3DXCOLOR& color);
	void SetShininess(const float& shininess);

	void SetShader(const string& file);
	void SetShader(const wstring& file);
	void SetAmbientTexture(const string& file);
	void SetDiffuseTexture(const string& file);
	void SetNormalTexture( const string& file );
	void SetSpecularTexture(const string& file);
	void SetEmissiveTexture(const string& file);
		 
	void SetPSBuffer();
	void ImGuiRender( bool bSelect );

private:
	ModelMaterial(const MaterialData& data);
	ModelMaterial(const ModelMaterial& copy);

	void CreateTexture(const string& file, ID3D11ShaderResourceView** view);
	
private:
	class Shader* shader;
	class MaterialBuffer* materialBuffer;

	UINT number;
	string name;
	string shaderFile;
	string ambientFile;
	string diffuseFile;
	string normalFile;
	string specularFile;
	string emissiveFile;
	ID3D11ShaderResourceView* ambientView;
	ID3D11ShaderResourceView* diffuseView;
	ID3D11ShaderResourceView* normalView;
	ID3D11ShaderResourceView* specularView;
	ID3D11ShaderResourceView* emissiveView;
	
	string	ComboSelectShaderName;
};