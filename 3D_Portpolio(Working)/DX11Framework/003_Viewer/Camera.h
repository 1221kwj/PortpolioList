#pragma once

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void GetPosition		( Vector3* vec )				{ *vec		= position; }
	void SetPosition		( float x, float y, float z )	{ position	= Vector3( x, y, z ); View(); }
	
	void GetRotation		( Vector2* vec )				{ *vec = rotation; }
	void GetRotationDegree	( Vector2* vec )				{ *vec = rotation * 180.0f / XM_PI; }

	void SetRotation		( float x, float y )			{ rotation = Vector2( x, y )					; Rotation(); }
	void SetRotationDegree	( float x, float y )			{ rotation = Vector2( x, y ) * XM_PI / 180.0f	; Rotation(); }
	
	void GetForward			( Vector3* vec )				{ *vec = forward; }
	void GetRight			( Vector3* vec )				{ *vec = right; }
	void GetUp				( Vector3* vec )				{ *vec = up; }

	void GetMatrix			( XMFLOAT4X4* view )			{ *view	= matView; }

	virtual void Update() = 0;

	Vector3 Direction( class Viewport* vp, class Perspective* perspective );

protected:
	virtual void Move();
	virtual void Rotation();
	virtual void View();

private:
	Vector3 position;
	Vector2 rotation;

	Vector3 forward;
	Vector3 right;
	Vector3 up;

	XMFLOAT4X4 matRotation;
	XMFLOAT4X4 matView;
};