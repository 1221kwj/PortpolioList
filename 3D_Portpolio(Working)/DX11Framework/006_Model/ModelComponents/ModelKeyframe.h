#pragma once

class ModelKeyframe
{
public:
	struct Transform;

	friend class ModelClip;

	ModelKeyframe();
	~ModelKeyframe();

public:
	XMFLOAT4X4 GetInterpolatedMatrix( float time, bool bRepeat );

private:
	UINT GetKeyframeIndex( float time );
	void CalcKeyframeIndex
	(
		float		time,
		bool		bRepeat,
		OUT UINT&	index1,
		OUT UINT&	index2,
		OUT float&	interpolatedTime
	);

	XMFLOAT4X4 GetInterpolatedMatrix( UINT index1, UINT index2, float t );

private:
	wstring boneName;

	float	duration;
	float	frameRate;
	UINT	frameCount;

	vector<Transform> transforms;

public:
	struct Transform
	{
		float	Time;

		Vector3 S;
		Vector4 R;
		Vector3 T;
	};
};