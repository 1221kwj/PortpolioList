#pragma once
#include "ModelKeyframe.h"

class ModelClip
{
public:
	ModelClip( wstring file );
	~ModelClip();

	void Reset();

	XMFLOAT4X4 GetKeyframeMatrix( class ModelBone* bone, float time );
	void UpdateKeyframe( class ModelBone* bone, float time );

	void LockRoot	( bool val )	{ bLockRoot = val; }
	void Repeat		( bool val )	{ bRepeat	= val; }
	void Speed		( float  val )	{ speed		= val; }
	void StartTime	( float val )	{ playTime	= val; }

private:
	wstring name;

	float	duration;
	float	frameRate;
	UINT	frameCount;

	bool	bLockRoot;
	bool	bRepeat;
	float	speed;
	float	playTime;

	typedef pair<wstring, ModelKeyframe *> Pair;
	unordered_map<wstring, ModelKeyframe *> keyframeMap;
};