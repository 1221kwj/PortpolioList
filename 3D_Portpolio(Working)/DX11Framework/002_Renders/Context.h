#pragma once

class CBuffer;

struct PointLightDesc
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;

	Vector3 Position;
	float	Range;

	Vector3 Attenuation;
	float	Padding;
};

struct SpotLightDesc
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;

	Vector3 Position;
	float	Padding;

	Vector3 Direction;
	float	Spot;

	Vector3 Attenuation;
	float	Padding2;
};

class Context
{
private:
	struct GlobalLight;

public:
	static void Create();
	static void Delete();

	static Context* Get();

private:
	Context();
	~Context();

public:
	void Update();
	void AddShader( Shader* shader );

	class Perspective* GetPerspective();
	void ChangePerspective();

	GlobalLight* GetGlobalLight();
	void ChangeGlobalLight();

	void AddPointLight( PointLightDesc& light );
	void AddSpotLight( SpotLightDesc& light );

	class Viewport* GetViewport();
	class Camera*	GetMainCamera();

private:
	static Context*		instance;

private:
	class Perspective*	perspective;
	class Viewport*		viewport;
	class Camera*		mainCamera;

private:
	// ======================================================================
	//								PerFrame
	// ======================================================================
	struct PerFrame
	{
		XMFLOAT4X4	View;

		Vector3		ViewDirection;
		float		Time;
		
		Vector3		ViewPosition;
		float		Padding;
	};
	PerFrame perFrame;
	map<Shader*, CBuffer*> perFrameMap;

	// ======================================================================
	//								Projection
	// ======================================================================
	struct Projection
	{
		XMFLOAT4X4 Project;
	};
	Projection projection;
	map<Shader*, CBuffer*> projectionMap;

	// ======================================================================
	//								GlobalLight
	// ======================================================================
	struct GlobalLight
	{
		Vector4 Ambient		= Vector4(  0.2f,  0.2f,  0.2f, 1.0f );
		Vector4 Diffuse		= Vector4(  0.5f,  0.5f,  0.5f, 1.0f );
		Vector4 Specular	= Vector4(  0.5f,  0.5f,  0.5f, 1.0f );
		Vector3 Direction	= Vector3( -1.0f, -1.0f, -1.0f );

		float Padding;
	};
	GlobalLight light;
	map<Shader*, CBuffer*> lightMap;

	// ======================================================================
	//								PointLight
	// ======================================================================
	struct PointLightBuffer
	{
		PointLightDesc	Lights[ 16 ];
		int				Count = 0;

		float			Padding[ 3 ];
	};
	PointLightBuffer pointLight;
	map<Shader*, CBuffer*> pointLightMap;

	// ======================================================================
	//								SpotLight
	// ======================================================================
	struct SpotLightBuffer
	{
		SpotLightDesc	Lights[ 16 ];
		int				Count = 0;

		float			Padding[ 3 ];
	};
	SpotLightBuffer spotLight;
	map<Shader*, CBuffer*> spotLightMap;
};



