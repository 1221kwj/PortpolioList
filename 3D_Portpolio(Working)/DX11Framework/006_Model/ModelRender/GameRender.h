#pragma once

class GameRender
{
public:
	GameRender();
	virtual ~GameRender();

	void SetEnable( bool val );
	bool GetEnable();
	vector<function<void( bool )>> Enabled;

	void SetVisible( bool val );
	bool GetVisible();
	vector<function<void( bool )>> Visibled;

	void SetRootAxis( XMFLOAT4X4& matrix );
	void SetRootAxisDegree( Vector3& rotation );
	void SetRootAxisRadian( Vector3& rotation );
	void GetRootAxis( XMFLOAT4X4* matrix );

	void GetWorld( XMFLOAT4X4* matrix );

	void SetPosition( Vector3& vec );
	void SetPosition( float x, float y, float z );
	void GetPosition( Vector3* vec );

	void SetScale( Vector3& vec );
	void SetScale( float x, float y, float z );
	void GetScale( Vector3* vec );

	void SetRotation( Vector3& vec );
	void SetRotation( float x, float y, float z );
	void SetRotationDegree( Vector3& vec );
	void SetRotationDegree( float x, float y, float z );
	void GetRotation( Vector3* vec );
	void GetRotationDegree( Vector3* vec );


	void GetDirection( Vector3* vec );
	void GetUp( Vector3* vec );
	void GetRight( Vector3* vec );

	void GetTransformed( XMFLOAT4X4* matrix );

	virtual void Update();
	virtual void Render();

private:
	void UpdateWorld();

protected:
	bool enable;
	bool visible;

	XMFLOAT4X4 rootAxis;

private:
	XMFLOAT4X4 world;

	Vector3 position;
	Vector3 scale;
	Vector3 rotation;

	Vector3 direction;
	Vector3 up;
	Vector3 right;
};