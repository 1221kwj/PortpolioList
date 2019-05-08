using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnEnemy : MonoBehaviour
{
	[SerializeField] GameObject enemy;



	private float _spawnTime = 3.0f;
	private int _limitSpawnCount = 5;
	private int _currentSpawnCount = 0;

	// Use this for initialization
	void Start ()
	{
		//InvokeRepeating("Spawn", _spawnTime, _spawnTime);
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Input.GetKeyDown(KeyCode.Space))
			Spawn();
	}

	private void Spawn()
	{
		if (enemy == null) return;

		if (_currentSpawnCount >= _limitSpawnCount) return;

		Vector3 pos = transform.position;
		pos += Vector3.forward * Random.Range(-5.0f, 5.0f);
		pos += Vector3.right * Random.Range(-5.0f, 5.0f);

		Instantiate(enemy, pos, transform.rotation);

		_currentSpawnCount++;
	}

	private void OnDrawGizmos()
	{
		Gizmos.color = Color.red;
		Gizmos.DrawWireSphere(transform.position, 2.0f);
	}
}
