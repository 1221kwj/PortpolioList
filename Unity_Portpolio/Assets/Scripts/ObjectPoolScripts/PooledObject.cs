using UnityEngine;
using System.Collections.Generic;

[System.Serializable]
public class PooledObject
{
	public string		_poolItemName = string.Empty;
	public GameObject	_prefab = null;
	public int			_poolCount = 0;

	[SerializeField] private List<GameObject> _poolList = new List<GameObject>();

	public void Initialize(Transform parent = null)
	{
		for (int i = 0;i<_poolCount;i++)
		{
			_poolList.Add(CreateItem(parent));
		}
	}

	public void PushToPool(GameObject item, Transform parent = null)
	{
		item.transform.SetParent(parent);
		item.SetActive(false);
		_poolList.Add(item);
	}

	public GameObject PopFromPool(Transform parent = null)
	{
		if (_poolList.Count == 0)
			_poolList.Add(CreateItem(parent));

		GameObject item = _poolList[0];
		_poolList.RemoveAt(0);

		return item;
	}

	private GameObject CreateItem(Transform parent = null)
	{
		GameObject item = Object.Instantiate(_prefab) as GameObject;
		item.name = _poolItemName;
		item.transform.SetParent(parent);
		item.SetActive(false);

		return item;
	}
}
