using UnityEngine;
using System.Collections;
using UnityEngine.AI;

public class EnemyCtl : MonoBehaviour
{
	private enum EnemyState { Idle = 0, Move, Attack, Dying }

	private EnemyState		_state				= EnemyState.Idle;

	private Animator		_animator			= null;

	private AttackCollider	_attackCollider		= null;
	private CapsuleCollider _swordCollider		= null;
	private NavMeshAgent	_agent				= null;

	private Detecter		_detecter;

	private Transform		_targetTrans		= null;
	private Transform		_failureCondition	= null;

	private Vector3			_direction			= Vector3.zero;
	private Vector3			_prevPosition		= Vector3.zero;

	private bool			_bDeath				= false;
	private bool			_bAttack			= false;
	private bool			_bDetect			= false;

	private float			_moveVel			= 4.0f;
	private float			_reAttackTime		= 1.5f;
	private float			_attackRange		= 2.0f;
	private float			_targetDist			= 0.0f;
	private float			_damage				= 20.0f;

	private void Awake()
	{
		_animator = GetComponent<Animator>();
		_detecter = transform.FindAllChildByName("Detecter").GetComponent<Detecter>();

		Transform swordTrans = transform.FindAllChildByName("SwordCapsule");

		_attackCollider = swordTrans.GetComponent<AttackCollider>();
		_attackCollider.OnAttackEnter += Attacking;

		_swordCollider = swordTrans.GetComponent<CapsuleCollider>();
		_swordCollider.enabled = false;

		_failureCondition = GameObject.FindGameObjectWithTag("FailureCondition").transform;

		_animator = GetComponent<Animator>();

		_animator.SetBool("bMove", false);

		AnimationClip clip = null;
		clip = _animator.GetClip("SkeletonWarrior_Attack");
		clip.AddEvent("OnEnableCollider"	, 8);
		clip.AddEvent("OnDisableCollider"	, 11);
		clip.AddEvent("OnEndAttack"			, 28);
	}

	private void Start()
	{
		_state			= EnemyState.Idle;
		_prevPosition	= transform.position;

		_agent				= GetComponent<NavMeshAgent>();
		_agent.isStopped	= false;
		_agent.destination	= _failureCondition.position;
		_agent.velocity		= transform.forward * 4.0f;
	}

	private void OnEnableCollider()
	{
		_swordCollider.enabled = true;
	}

	private void OnDisableCollider()
	{
		_swordCollider.enabled = false;
	}

	private void OnEndAttack()
	{
		if (_targetDist < _attackRange)
			StartCoroutine(CoEndAttack());
		else
			OnFinishAttack();
	}

	private IEnumerator CoEndAttack()
	{
		float start = 0.0f;

		while (true)
		{
			yield return null;

			if (start > _reAttackTime) break;

			start += Time.deltaTime;

			if (_targetDist > _attackRange)
			{
				_state = EnemyState.Move;

				_animator.SetBool("bMove", true);

				Vector3 forward = transform.forward * _moveVel * Time.deltaTime;
				transform.Translate(forward, Space.World);
			}
		}

		OnFinishAttack();
	}

	private void OnFinishAttack()
	{
		_bAttack = false;

		_state = EnemyState.Move;
	}

	private void Attacking(Collider other)
	{
		if (other.tag == "Knight")
			other.SendMessage("Damaged", _damage);
	}

	
	private void Update ()
	{
		if (_bDeath == true) return;

		CheckSpeed();

		_bDetect = _detecter.Detect;
		_animator.SetBool("bDetect", _bDetect);

		if (_bDetect == true)
			_targetTrans = _detecter.TargetTrans;
		else
			_targetTrans = null;

		LookAtCharacter();

		switch (_state)
		{
			case EnemyState.Idle:	Idling(); break;
			case EnemyState.Move:	Moving(); break;
			case EnemyState.Attack: Attack(); break;
		}
	}

	private void CheckSpeed()
	{
		float dist = Vector3.Distance(_prevPosition, transform.position);

		if (dist > 1e-3f)
		{
			if (_animator.GetBool("bMove") == false)
				_animator.SetBool("bMove", true);
		}
		else
		{
			if (_animator.GetBool("bMove") == true)
				_animator.SetBool("bMove", false);
		}

		_prevPosition = transform.position;
	}

	private void Idling()
	{
		if (_bDetect == true && _targetTrans != null)
		{
			_agent.isStopped = true;

			if (_targetDist < _attackRange)
				_state = EnemyState.Idle;
			else
				_state = EnemyState.Move;
		}
	}

	private void Moving()
	{
		if (_bDetect == true && _targetTrans != null)
		{
			Idling();

			if (_targetDist <= _attackRange)
			{
				_state = EnemyState.Attack;
			}
			else
			{
				Vector3 forward = this.transform.forward * _moveVel * Time.deltaTime;
				transform.Translate(forward, Space.World);
			}
		}
		else
		{
			if (_agent.isStopped == true)
			{
				_agent.isStopped	= false;
				_agent.ResetPath();
				_agent.destination	= _failureCondition.position;
				_agent.velocity		= transform.forward * _moveVel * Time.deltaTime;
				_state				= EnemyState.Move;
			}
		}
	}

	private void Attack()
	{
		if (_bAttack == true) return;

		_animator.SetTrigger("tAttack");
		_bAttack = true;
	}
	
	private void LookAtCharacter()
	{
		if (_targetTrans == null) return;

		Vector3 pos			= transform.position;
		Vector3 targetPos	= _targetTrans.position;

		pos.y		= targetPos.y = 0.0f;
		_direction	= targetPos - pos;

		_direction.Normalize();

		_targetDist = Vector3.Distance(pos, targetPos);

		Quaternion target = Quaternion.LookRotation(_direction);

		transform.rotation	= Quaternion.RotateTowards(this.transform.rotation, target, 10);
	}

	private void Damaged()
	{
		Renderer[] renderers = GetComponentsInChildren<Renderer>();

		for (int i = 0; i < renderers.Length; i++)
			renderers[i].material.color = Color.red;
	}

	private void OnDrawGizmos()
	{
		Gizmos.color = Color.blue;
		Gizmos.DrawWireSphere(transform.position, _attackRange);

		Gizmos.color = Color.red;
		Gizmos.DrawWireSphere(transform.position, 8.0f);
	}

	private void OnGUI()
	{
		//GUI.TextArea(new Rect(0, 20, 200, 20), "State	: " + _state.ToString());
		//GUI.TextArea(new Rect(0, 40, 200, 20), "Move	: " + _animator.GetBool("bMove").ToString());
		//GUI.TextArea(new Rect(0, 60, 200, 20), "Detect	: " + _animator.GetBool("bDetect").ToString());
		//
		//if (_targetTrans != null)
		//	GUI.TextArea(new Rect(0, 80, 200, 20), "TargetPos : " + _targetTrans.position.ToString());
	}

	public bool GetDeath { get { return _bDeath; } }
}
