#include "stdafx.h"
#include "ModelAnimation.h"

ModelAnimation::ModelAnimation(const AnimationData & data)
{
	name = data.name;

	startIndex = data.startIndex;
	keyFrameCount = data.keyFrameCount;

	frameRate = data.frameRate;
	defaultFrameRate = data.frameRate;
}

ModelAnimation::~ModelAnimation()
{

}
