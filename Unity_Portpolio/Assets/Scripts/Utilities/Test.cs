using UnityEngine;
using UnityEngine.AI;

public class Test : MonoBehaviour {

	// Use this for initialization
	void Start () {
		Transform goal = GameObject.FindGameObjectWithTag("FailureCondition").transform;

		NavMeshAgent agent = GetComponent<NavMeshAgent>();
		agent.destination = goal.position;
		agent.speed = 5.0f;
		agent.velocity = transform.forward * 2.0f;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
