#pragma once

class Render2D
{
public:
	Render2D( wstring shaderFile = L"" );
	virtual ~Render2D();

	void SetPosition( float x, float y );
	void SetPosition( Vector2 vec );

	void SetScale( float x, float y );
	void SetScale( Vector2 vec );

	Vector2 GetScale() { return scale; }

	void Update();
	virtual void Render();

	void SRV( ID3D11ShaderResourceView* srv );

private:
	void UpdateWorld();

private:
	Shader*			shader;

	ID3D11Buffer*	vertexBuffer;

	XMFLOAT4X4		view;
	XMFLOAT4X4		orthographic;

	Vector2			position;
	Vector2			scale;
};