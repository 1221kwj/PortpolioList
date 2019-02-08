#pragma once

class Sky
{
public:
	Sky( wstring cubeFile );
	~Sky();

	void Update();
	void Render();

	ID3D11ShaderResourceView* GetSRV() { return srv; }
	
private:
	Material*					material;
	MeshSphere*					sphere;
	
	ID3D11ShaderResourceView*	srv;
};