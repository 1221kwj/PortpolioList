#pragma once

class SkyBuffer : public ShaderBuffer
{
public:
	SkyBuffer() : ShaderBuffer(&Data, sizeof(Struct))
	{
		Data.Apex = D3DXCOLOR(0.0f, 0.05f, 0.6f, 1.0f);
		Data.Center = D3DXCOLOR(0.0f, 0.5f, 0.8f, 1.0f);
		Data.Height = 2.0f;
	}

	struct Struct
	{
		D3DXCOLOR Center;
		D3DXCOLOR Apex;
		float Height;
		float Padding[3];
	};

	Struct Data;
};

class Sky
{
public:
	Sky();
	~Sky();

	void Update(Camera* camera);
	void Render();
	void PostRender(GuiSettings* settings);

private:
	wstring modelFile;
	Model* model;

	wstring shaderFile;
	Shader* shader;
	SkyBuffer* skyBuffer;

	D3DXMATRIX world;

	ID3D11RasterizerState* clockState;
	ID3D11RasterizerState* countClockState;
	ID3D11DepthStencilState* depthOnState;
	ID3D11DepthStencilState* depthOffState;
};