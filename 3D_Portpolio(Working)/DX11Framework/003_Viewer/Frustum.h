#pragma once

class Frustum
{
public:
	Frustum( float zFar, class Camera* camera = NULL, class Perspective* perspective = NULL );
	~Frustum();

	void ZFar( float val ) { zFar = val; }
	void Update();

	void GetPlanes( OUT Vector4* plane );

	bool ContainPoint	( Vector3& position );
	bool ContainRect
	( 
		float xCenter,
		float yCenter,
		float zCenter,
		float xSize,
		float ySize,
		float zSize
	);
	bool ContainRect	( Vector3 center, Vector3 size );
	bool ContainCube	( Vector3& center, float radius );

private:
	Vector4				planes[ 6 ];

	float				zFar;

	class Camera*		camera;
	class Perspective*	perspective;
};