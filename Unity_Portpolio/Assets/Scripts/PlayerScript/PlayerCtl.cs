using UnityEngine;

public class PlayerCtl : MonoBehaviour
{
	#region CodeParameter
	//[Range(30.0f, 100.0f),	SerializeField]	private float _attack			= 30.0f;
	[Range(1.0f, 10.0f),	SerializeField] private float _walkVel	= 2.0f;
	[Range(5.0f, 20.0f),	SerializeField] private float _runVel	= 5.0f;

	[SerializeField] private Animator _crossHairAnim;

	enum CombatState { SWORD = 1, BOW, NONE, DYING }
	
	private Animator		_animator;
	private GameObject		_playerCamera;
	private GameObject		_mainCamera;

	private bool			_bCameraChange;
	private bool			_bAttack;
	private float			_hp;
	private Color			_bodyColor	= new Color(1.0f, 1.0f, 1.0f, 123.0f / 255.0f);

	private GameObject		_sword;
	private GameObject		_bow;

	private Transform		_swordAttachSlot;
	private Transform		_swordTakeSlot;
	private Transform		_bowAttachSlot;
	private Transform		_bowTakeSlot;
	private Transform		_arrowHandleSlot;

	private string			_arrowName;
	private CombatState		_combatState;

	#endregion

	#region Initialize
	private void Awake()
	{
		CameraSetting	();
		AnimSetting		();

		_bAttack					= false;
		_sword						= GameObject.FindWithTag		("Weapon_Sword");
		_bow						= GameObject.FindWithTag		("Weapon_Bow");
		_swordAttachSlot			= transform.FindAllChildByName	("SwordAttachSlot");
		_swordTakeSlot				= transform.FindAllChildByName	("SwordTakeSlot");
		_bowAttachSlot				= transform.FindAllChildByName	("BowAttachSlot");
		_bowTakeSlot				= transform.FindAllChildByName	("BowTakeSlot");
		_arrowHandleSlot			= transform.FindAllChildByName	("ArrowHandleSlot");

		_hp							= 200.0f;

		_arrowName					= "Arrow";
		_combatState				= CombatState.NONE;
	}

	private void Start() {}

	private void CameraSetting()
	{
		Cursor.visible = false;
		_bCameraChange = true;

		_mainCamera		= GameObject.FindGameObjectWithTag("MainCamera");
		_playerCamera	= GameObject.FindGameObjectWithTag("PlayerCamera");

		_mainCamera.SetActive(false);
		_playerCamera.SetActive(true);
	}

	private void AnimSetting()
	{
		_bAttack	= false;
		_animator	= GetComponent<Animator>();

		AnimationClip clip = null;
		clip = _animator.GetClip("Hit");

		clip = _animator.GetClip("A_SwordDraw_01");
		clip.AddEvent("OnSwordChangeCombo1End", 10);

		clip = _animator.GetClip("A_SwordDraw_02");
		clip.AddEvent("OnSwordDraw2SwordTrans", 1);
		clip.AddEvent("OnSwordChangeCombo2End", 21);

		clip = _animator.GetClip("A_SwordSheath_01");
		clip.AddEvent("OnSwordChangeCombo1End", 34);

		clip = _animator.GetClip("A_SwordSheath_02");
		clip.AddEvent("OnSwordChangeCombo2End", 23);
		clip.AddEvent("OnSwordSheath2SwordTrans", 1);

		clip = _animator.GetClip("A_SwordSlash");
		clip.AddEvent("OnSwordSlashEnter", 15);
		clip.AddEvent("OnSwordSlashEnd", 44);

		clip = _animator.GetClip("A_BowDraw");
		clip.AddEvent("OnBowDrawTrans", 8);
		clip.AddEvent("OnBowDrawEnd", 32);

		clip = _animator.GetClip("A_BowSheath");
		clip.AddEvent("OnBowSheathTrans", 12);
		clip.AddEvent("OnBowSheathEnd", 36);

		clip = _animator.GetClip("A_BowArrowDraw");
		clip.AddEvent("OnArrowDrawEnd", 29);

		clip = _animator.GetClip("A_BowShoot");
		clip.AddEvent("OnArrowShootEnd", 20);
	}

	private void OnSwordChangeCombo1End()
	{
		_animator.SetInteger("iSwordChangeCombo", 0);
	}

	private void OnSwordChangeCombo2End()
	{
		_animator.SetInteger("iSwordChangeCombo", -1);

		int nextState	= _animator.GetInteger("NextCombatState");
		_combatState	= (CombatState)nextState;
		_animator.SetInteger("CurrentCombatState", nextState);
	}

	private void OnSwordDraw2SwordTrans()
	{
		_sword.transform.parent				= _swordTakeSlot;
		_sword.transform.localPosition		= Vector3.zero;
		_sword.transform.localEulerAngles	= Vector3.zero;
	}

	private void OnSwordSheath2SwordTrans()
	{
		_sword.transform.parent				= _swordAttachSlot;
		_sword.transform.localPosition		= Vector3.zero;
		_sword.transform.localEulerAngles	= Vector3.zero;
	}

	private void OnSwordSlashEnter()
	{
		_sword.transform.GetComponent<CapsuleCollider>().enabled = true;
	}

	private void OnSwordSlashEnd()
	{
		_bAttack = false;
		_sword.transform.GetComponent<CapsuleCollider>().enabled = false;
	}

	private void OnBowDrawTrans()
	{
		_bow.transform.parent			= _bowTakeSlot;
		_bow.transform.localPosition	= Vector3.zero;
		_bow.transform.localEulerAngles = Vector3.zero;
	}

	private void OnBowDrawEnd()
	{
		int nextState	= _animator.GetInteger("NextCombatState");
		_combatState	= (CombatState)nextState;
		_animator.SetInteger("CurrentCombatState", nextState);
	}

	private void OnBowSheathTrans()
	{
		_bow.transform.parent			= _bowAttachSlot;
		_bow.transform.localPosition	= Vector3.zero;
		_bow.transform.localEulerAngles = Vector3.zero;
	}

	private void OnBowSheathEnd()
	{
		int nextState	= _animator.GetInteger("NextCombatState");
		_combatState	= (CombatState)nextState;
		_animator.SetInteger("CurrentCombatState", nextState);
	}

	private void OnArrowDrawEnd()
	{
		GameObject	arrow	= ObjectPool.Instance.PopFromPool(_arrowName);
		Vector3		pos		= _arrowHandleSlot.position;
		Quaternion	angle	= Quaternion.Euler
		(
			new Vector3
			(
				_playerCamera.transform.eulerAngles.x,
				transform.eulerAngles.y,
				transform.eulerAngles.z
			)
		);

		arrow.SetActive(true);
		arrow.GetComponent<ArrowMove>().SetShoot(pos, angle);

		_animator.SetInteger("iBowCombo", 0);
	}

	private void OnArrowShootEnd()
	{
		_animator.SetInteger("iBowCombo", -1);
		_bAttack = false;
	}
	#endregion

	private void Update()
	{
		// 프리 카메라 변환
		ChangeCamera();

		// 애니메이션이 없을 때 아무런 작동 하지 않게 만듦
		if (_animator == null) return;
		
		// 무기 변환
		CombatStateChange();

		// 공격
		if (_bAttack == false) Attack();
		
		// 이동
		if (_bAttack == false && _bCameraChange == true) Move();
	}

	private void CombatStateChange()
	{
		int currentState = _animator.GetInteger("CurrentCombatState");

		if (Input.GetButtonDown("ChangeWeapon_01") == true && currentState != 1)
		{
			_animator.SetTrigger("tWeaponChange");
			_animator.SetInteger("NextCombatState", 1);
		}
		else if (Input.GetButtonDown("ChangeWeapon_02") == true && currentState != 2)
		{
			_animator.SetTrigger("tWeaponChange");
			_animator.SetInteger("NextCombatState", 2);
		}
		else if (Input.GetButtonDown("ChangeWeapon_03") == true && currentState != 3)
		{
			_animator.SetTrigger("tWeaponChange");
			_animator.SetInteger("NextCombatState", 3);
		}
	}

	private void Move()
	{
		float x = Input.GetAxis("Horizontal");
		float z = Input.GetAxis("Vertical");

		float speed = 0.0f;

		Vector3 position = transform.position;

		if (Mathf.Abs(x) > 0.0f || Mathf.Abs(z) > 0.0f)
		{
			_animator.SetBool("bWalk", true);
			speed = _walkVel;

			if (_crossHairAnim != null)
				_crossHairAnim.SetBool("bWalk", true);
		}
		else
		{
			_animator.SetBool("bWalk", false);
			if (_crossHairAnim != null)
				_crossHairAnim.SetBool("bWalk", false);
		}

		if (Input.GetButton("Run") == true)
		{
			_animator.SetBool("bRun", true);
			speed = _runVel;

			if (_crossHairAnim != null)
				_crossHairAnim.SetBool("bRun", true);
		}
		else
		{
			_animator.SetBool("bRun", false);

			if (_crossHairAnim != null)
				_crossHairAnim.SetBool("bRun", false);
		}

		_animator.SetFloat("Vel_X", x);
		_animator.SetFloat("Vel_Z", z);

		position += transform.forward * z * Time.deltaTime * speed;
		position += transform.right	* x * Time.deltaTime * speed;

		transform.position = position;
	}

	private void ChangeCamera()
	{
		if (Input.GetButtonDown("ChangeCamera") == true)
		{
			if (_bCameraChange == true)
			{
				_mainCamera.SetActive(true);
				_playerCamera.SetActive(false);

				CameraMovement camMove = _mainCamera.GetComponent<CameraMovement>();
				camMove.SetCameraPosition(_playerCamera.transform.position, _playerCamera.transform.eulerAngles);

				_bCameraChange = false;
			}
			else
			{
				_mainCamera.SetActive(false);
				_playerCamera.SetActive(true);
				_bCameraChange = true;
			}
		}
	}

	public bool GetCameraActive()
	{
		return _bCameraChange;
	}

	private void Attack()
	{
		if (Input.GetButtonDown("Attack") == true && _combatState != CombatState.NONE)
		{
			_bAttack = true;
			_animator.SetTrigger("tAttack");

			if (_crossHairAnim != null)
				_crossHairAnim.SetTrigger("tAttack");
		}
	}

	private void Damaged(float damage)
	{
		_animator.SetTrigger("tHit");

		Renderer[] renderers = GetComponentsInChildren<Renderer>();

		for (int i = 0; i < renderers.Length; i++)
			renderers[i].material.color = Color.red;

		_hp -= damage;

		Invoke("ChangeColor", 0.25f);

		if (_hp <= 0) _hp = 0;
	}

	private void OnGUI()
	{
		GUI.TextArea(new Rect(Screen.width - 200, 0, 200, 20), _hp.ToString());
	}

	private void ChangeColor()
	{
		Renderer[] renderers = GetComponentsInChildren<Renderer>();

		for (int i = 0; i < renderers.Length; i++)
			renderers[i].material.color = _bodyColor;
	}
}
