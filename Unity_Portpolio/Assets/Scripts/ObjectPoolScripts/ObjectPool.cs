using UnityEngine;
using System.Collections.Generic;

public class ObjectPool : Singleton<ObjectPool>
{
	public List<PooledObject> _objectPool = new List<PooledObject>();

	private void Awake()
	{
		for (int i = 0; i < _objectPool.Count; i++)
		{
			_objectPool[i].Initialize(transform);
		}
	}

	public bool PushToPool(string itemName, GameObject item, Transform parent = null)
	{
		PooledObject pool = GetPoolItem(itemName);

		if (pool == null) return false;

		pool.PushToPool(item, parent == null ? transform : parent);

		return true;
	}

	public GameObject PopFromPool(string itemName, Transform parent = null)
	{
		PooledObject pool = GetPoolItem(itemName);

		if (pool == null) return null;

		return pool.PopFromPool(parent);
	}

	public PooledObject GetPoolItem(string itemName)
	{
		for (int i = 0; i < _objectPool.Count; i++)
		{
			if (_objectPool[i]._poolItemName.Equals(itemName))
				return _objectPool[i];
		}

		Debug.LogWarning("There's no matched pool list.");

		return null;
	}
}
