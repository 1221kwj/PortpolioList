using UnityEngine;

public static class AnimHelper
{
	public static float GetExecTime(this AnimationClip clip, int frame)
	{
		float totalFrame = (int)(clip.frameRate * clip.length) - 1.0f;
		return (frame / totalFrame) * clip.length;
	}

	public static AnimationClip GetClip(this Animator animator, string name)
	{
		AnimationClip[] clips = animator.runtimeAnimatorController.animationClips;

		for (int i = 0; i < clips.Length; i++)
		{
			if (clips[i].name == name)
				return clips[i];
		}

		return null;
	}

	public static AnimationEvent AddEvent(this AnimationClip clip, string funcName, int frame)
	{
		float execTime = GetExecTime(clip, frame);

		AnimationEvent e = new AnimationEvent()
		{
			time = execTime,
			functionName = funcName,
		};
		clip.AddEvent(e);

		return e;
	}
}
