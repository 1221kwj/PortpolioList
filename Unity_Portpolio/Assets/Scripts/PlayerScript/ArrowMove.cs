using UnityEngine;
using System.Collections.Generic;

public class ArrowMove : MonoBehaviour
{
	private string		_poolItemArrow	= "Arrow";
	private float		_lifeTime		= 4.0f;
	private float		_elapsedTime	= 0.0f;

	private bool		_bShoot			= false;
	private Rigidbody	_arrowRb;
	private Color		_arrowColor;
	private Material	_arrowMat;

	private void Awake()
	{
		_arrowRb				= transform.GetComponent<Rigidbody>();
		_arrowRb.centerOfMass	= new Vector3(0.0f, 0.0f, 0.5f);
		_arrowRb.velocity		= Vector3.zero;

		_arrowMat	= transform.FindAllChildByName("ArrowPrefab").GetComponent<Renderer>().material;
		_arrowColor = _arrowMat.color;
	}

	private void Start () {}
	
	private void Update ()
	{
		if (_bShoot == true)
			transform.eulerAngles = SpinInAir();

		if (GetTimer() > _lifeTime)
			SetInitialize();
	}

	private float GetTimer() { return _elapsedTime += Time.deltaTime; }

	private void SetInitialize()
	{
		_bShoot			= false;
		_arrowColor.a	-= Time.deltaTime * 0.1f;

		if (_arrowColor.a <= 0.0f)
		{
			_arrowColor.a				= 0.0f;
			_elapsedTime				= 0.0f;
			_arrowRb.transform.position = Vector3.zero;
			_arrowRb.transform.rotation = Quaternion.identity;
			ObjectPool.Instance.PushToPool(_poolItemArrow, gameObject);	
		}

		_arrowMat.color = _arrowColor;
	}

	public void SetShoot(Vector3 pos, Quaternion angle)
	{
		_bShoot					= true;
		_arrowRb.useGravity		= true;
		_arrowRb.isKinematic	= false;
		_arrowColor.a			= 1.0f;
		_arrowMat.color			= _arrowColor;

		_arrowRb.transform.position = pos;
		_arrowRb.transform.rotation = angle;
		_arrowRb.AddRelativeForce(_arrowRb.transform.forward * 1500.0f);
	}

	public void OnTriggerEnter(Collider other)
	{
		if (other.name == "Player") return;
		if (other.name == "Arrow")	return;

		_arrowRb.useGravity		= false;
		_arrowRb.isKinematic	= true;
		_arrowRb.velocity		= Vector3.zero;
		
		_bShoot = false;
	}

	private Vector3 SpinInAir()
	{
		float x = _arrowRb.velocity.x;
		float y = _arrowRb.velocity.y;
		float z = _arrowRb.velocity.z;

		float c = Mathf.Sqrt(x * x + z * z);
		float f = -1.0f * Mathf.Atan2(y, c) * 180.0f / Mathf.PI;

		return new Vector3(f, transform.eulerAngles.y, transform.eulerAngles.z );
	}

	private void OnDrawGizmos()
	{
		
	}
}
