#pragma once

class Time
{
public:
	static Time* Get();

	static void Create();
	static void Delete();

	static bool  Stopped()	{ return bTimerStopped; }
	static float Delta()	{ return bTimerStopped ? 0.0f : timeElapsed; }

private:
	Time();
	~Time();

public:
	void Update	();

	void Start	();
	void Stop	();

	float FPS()		const { return framePerSecond; }
	float Running() const { return runningTime; }

private:
	static Time* instance;		///< �̱��� ��ü

	static bool  bTimerStopped;	///< Ÿ�̸� ����
	static float timeElapsed;	///< ���� ���������κ��� ����ð�


	INT64 ticksPerSecond;		///< �ʴ� ƽī��Ʈ
	INT64 currentTime;			///< ���� �ð�
	INT64 lastTime;				///< �����ð�
	INT64 lastFPSUpdate;		///< ������ FPS ������Ʈ �ð�
	INT64 fpsUpdateInterval;	///< fps ������Ʈ ����

	UINT  frameCount;			///< ������ ��
	float runningTime;			///< ���� �ð�
	float framePerSecond;		///< FPS
};