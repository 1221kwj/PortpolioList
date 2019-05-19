#pragma once

enum class AnimationMode : UINT
{
	Play = 0, Pause, Stop,
};

class ModelAnimationController
{
	friend class ModelData;
	typedef vector<pair<string, class ModelAnimation*>> AnimationArray;

public:
	virtual ~ModelAnimationController();

	class ModelAnimation* GetCurrentAnimation();
	class ModelAnimation* GetAnimation(int index);
	UINT GetAnimationCount() const { UINT count = animations.size(); return count; }

	int GetCurrentKeyFrame() const { return currentKeyFrame; }
	int GetNextKeyFrame() const { return nextKeyFrame; }
	float GetKeyFrameFactor() const { return keyFrameFactor; }
	int GetCurrentTotalKeyFrame();

	const AnimationMode& GetAnimationMode() const { return mode; }
	bool GetUseQuaternionKeyFrames() const { return useQuaternionKeyFrames; }

	void SetCurrentAnimation(string animationName);
	void SetCurrentAnimation(int index);
	void SetCurrentKeyFrame(int keyFrame);
	void SetUseQuaternionKeyFrames(bool use) { useQuaternionKeyFrames = use; }

	void DeleteAnimation( int index );
		 
	void Play() { mode = AnimationMode::Play; }
	void Pause() { mode = AnimationMode::Pause; }
	void Stop() 
	{ 
		mode = AnimationMode::Stop;
		frameTimer = 0.0f;
		SetCurrentKeyFrame( 0 );
	}
		 
	void Update();

private:
	ModelAnimationController();

private:
	int currentKeyFrame;
	int nextKeyFrame;
	float keyFrameFactor;
	bool useQuaternionKeyFrames;

	float frameTimer;

	enum class AnimationMode mode;
	
	AnimationArray animations;
	class ModelAnimation* currentAnimation;
};