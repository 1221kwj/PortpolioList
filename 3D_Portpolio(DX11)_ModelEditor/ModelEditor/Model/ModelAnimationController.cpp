#include "stdafx.h"
#include "ModelAnimationController.h"
#include "./Elements/ModelAnimation.h"

ModelAnimationController::ModelAnimationController()
	: currentKeyFrame(0)
	, nextKeyFrame(0)
	, keyFrameFactor(0.0f)
	, frameTimer(0.0f)
	, useQuaternionKeyFrames(true)
	, mode(AnimationMode::Stop)
	, currentAnimation(NULL)
{
}

ModelAnimationController::~ModelAnimationController()
{
	for (pair<string, ModelAnimation*> temp : animations)
		SAFE_DELETE(temp.second);
}

ModelAnimation * ModelAnimationController::GetCurrentAnimation()
{
	if (currentAnimation == NULL)
		return NULL;

	return currentAnimation;
}

ModelAnimation * ModelAnimationController::GetAnimation(int index)
{
	if (index < 0 || index >= (INT)animations.size())
		return NULL;
	else
		return animations[index].second;
}

int ModelAnimationController::GetCurrentTotalKeyFrame()
{
	if ( currentAnimation == NULL ) return 0;
	return currentAnimation->GetKeyFrameCount();
}

void ModelAnimationController::SetCurrentAnimation(string animationName)
{
	int count = -1;
	for (size_t i = 0; i < animations.size(); i++)
	{
		if (animations[i].first == animationName)
		{
			count = i;
			break;
		}
	}

	if (count != -1)
		currentAnimation = animations[count].second;
	else
		currentAnimation = NULL;

	Stop();
}

void ModelAnimationController::SetCurrentAnimation(int index)
{
	if ( currentAnimation == animations[ index ].second ) return;

	if (index < 0 || index >= (int)animations.size())
		currentAnimation = NULL;
	else
		currentAnimation = animations[index].second;

	Stop();
}

void ModelAnimationController::SetCurrentKeyFrame(int keyFrame)
{
	//Stop();
	currentKeyFrame = (keyFrame) % currentAnimation->GetKeyFrameCount();
	nextKeyFrame = (currentKeyFrame + 1) % currentAnimation->GetKeyFrameCount();

	keyFrameFactor = 0.0f;
}

void ModelAnimationController::DeleteAnimation( int index )
{
	Stop();
	SAFE_DELETE( animations[ index ].second );
	animations.erase( animations.begin() + index );
}

void ModelAnimationController::Update()
{
	if (currentAnimation == NULL || mode != AnimationMode::Play) return;

	frameTimer += Time::Delta();

	float invFrameRate = 1.0f / currentAnimation->GetFrameRate();
	while (frameTimer > invFrameRate)
	{
		currentKeyFrame = (currentKeyFrame + 1) % currentAnimation->GetKeyFrameCount();
		nextKeyFrame = (currentKeyFrame + 1) % currentAnimation->GetKeyFrameCount();

		frameTimer -= invFrameRate;
	}

	keyFrameFactor = frameTimer / invFrameRate;
}