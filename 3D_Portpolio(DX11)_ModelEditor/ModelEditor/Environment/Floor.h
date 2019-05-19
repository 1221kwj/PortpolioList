#pragma once

class FloorBuffer : public ShaderBuffer
{
public:
	FloorBuffer() : ShaderBuffer(&Data, sizeof(Struct))
	{
		Data.Color = D3DXCOLOR(0xFFBBC0CC);
	}

	struct Struct
	{
		D3DXCOLOR Color;
	};

	Struct Data;
};

class Floor
{
public:
	Floor();
	~Floor();

	void Update();
	void Render();
	void PostRender(GuiSettings* settings);

private:
	wstring modelFile;
	Model* model;

	wstring shaderFile;
	Shader* shader;
	FloorBuffer* floorBuffer;

	D3DXMATRIX world;
};