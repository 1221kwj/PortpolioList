using System.Collections.Generic;
using UnityEngine;

public static class TransChildByName
{
	public static Transform FindChildByName(this Transform parent, string name)
	{
		for (int i = 0; i < parent.childCount; i++)
		{
			Transform child = parent.GetChild(i);

			if (child.gameObject.name == name)
				return child;
		}

		return null;
	}
}

public static class TransAllChildByName
{
	public static Transform FindAllChildByName(this Transform parent, string name)
	{
		Transform[] transforms = parent.GetComponentsInChildren<Transform>();
		for (int i = 0; i < transforms.Length; i++)
		{
			if (transforms[i].name == name)
				return transforms[i];
		}

		return null;
	}
}

public static class TransAllChildsByName
{
	public static Transform[] FindAllChildsByName(this Transform parent, string name)
	{
		List<Transform> list = new List<Transform>();
		Transform[] transforms = parent.GetComponentsInChildren<Transform>();
		for (int i = 0; i < transforms.Length; i++)
		{
			if (transforms[i].name == name)
				list.Add(transforms[i]);
		}

		if (list.Count > 0)
			return list.ToArray();

		return null;
	}
}
