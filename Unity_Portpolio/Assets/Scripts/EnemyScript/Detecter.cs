using UnityEngine;

public class Detecter : MonoBehaviour
{
	private bool		_bDetect	= false;
	private Transform	_target		= null;

	private void Start ()	{}
	
	void Update ()			{}

	private void OnTriggerStay(Collider other)
	{
		if (other.gameObject.tag == "Knight")
		{
			_bDetect	= true;
			_target		= other.transform;
		}
	}

	private void OnTriggerExit(Collider other)
	{
		_bDetect	= true;
		_target		= null;
	}

	public bool			Detect		{ get { return _bDetect; } }
	public Transform	TargetTrans	{ get { return _target; } }
}
