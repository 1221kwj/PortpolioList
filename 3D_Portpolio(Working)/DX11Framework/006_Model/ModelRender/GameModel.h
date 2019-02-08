#pragma once
#include "GameRender.h"

#include "../ModelComponents/Model.h"
#include "../ModelComponents/ModelBone.h"
#include "../ModelComponents/ModelMesh.h"

class GameModel : public GameRender
{
public:
	GameModel
	(
		wstring matFolder,
		wstring matFile,
		wstring meshFolder,
		wstring meshFile
	);
	virtual ~GameModel();

	void SetVelocity( Vector3& vec );
	void GetVelocity( Vector3* vec );

	virtual void Update();
	virtual void Render();

	Model* GetModel() { return model; }

	void SetShader( wstring shaderName );

	void SetDiffuse( float r, float g, float b, float a = 1.0f );
	void SetDiffuse( Vector4& color );
	void SetDiffuseMap( wstring file );

	void SetSpecular( float r, float g, float b, float a = 1.0f );
	void SetSpecular( Vector4& color );
	void SetSpecularMap( wstring file );

	void SetNormalMap( wstring file );

	void SetShininess( float val );

protected:
	void CalcPosition();

protected:
	Model*				model;
	Shader*				shader;
	Vector3				velocity;

	vector<XMFLOAT4X4>	boneTransforms;
};