#pragma once
#include "stdafx.h"
#include "../../BinExport/FbxData.h"

class ModelAnimation
{
	friend class ModelData;
	friend struct AnimationData;

public:
	virtual ~ModelAnimation();

	string GetName() const { return name; }
	int GetKeyFrameCount() const { return keyFrameCount; }
	float GetFrameRate() const { return frameRate; }
	float GetDefaultFrameRate() const { return defaultFrameRate; }

	void SetFrameRate(const float& frameRate) { this->frameRate = frameRate; }
	void ResetFrameRate() { frameRate = defaultFrameRate; }

private:
	ModelAnimation(const AnimationData& data);

private:
	string name;

	int	startIndex;
	int	keyFrameCount;

	float frameRate;
	float defaultFrameRate;
};