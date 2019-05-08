using UnityEngine;

public delegate void AttackTriggerEnterHandler(Collider other);

public class AttackCollider : MonoBehaviour
{
	public event AttackTriggerEnterHandler OnAttackEnter;
	public event AttackTriggerEnterHandler OnAttackStay;
	public event AttackTriggerEnterHandler OnAttackExit;

	private void OnTriggerEnter(Collider other)
	{
		if (OnAttackEnter != null)
			OnAttackEnter(other);
	}

	private void OnTriggerStay(Collider other)
	{
		if (OnAttackStay != null)
			OnAttackStay(other);
	}

	private void OnTriggerExit(Collider other)
	{
		if (OnAttackExit != null)
			OnAttackExit(other);
	}
}
