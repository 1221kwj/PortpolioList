using UnityEngine;
using System.Collections.Generic;

public class TPSCamera : MonoBehaviour
{
	private Transform	_player;
	private Transform	_camera;

	private float	_targetHeight		= 2.3f;
	private float	_defaultDist		= 1.4f;
	private float	_rightOffset		= 0.2f;
	private float	_mouseXSensitive	= 0.6f;
	private float	_mouseYSensitive	= 0.6f;
	private float	_yMinAngle			= -40.0f;
	private float	_yMaxAngle			=  80.0f;

	private int		_frameCounter		= 0;
	private float	_timeCounter		= 0.0f;
	private float	_lastFramerate		= 0.0f;
	private float	_refreshTime		= 0.5f;

	private Vector2 _mouse				= Vector2.zero;

	private void Awake()
	{
		_player				= FindObjectOfType<PlayerCtl>().transform;

		transform.position	= Vector3.zero;
		transform.position	= _player.position;

		_camera				= GameObject.FindGameObjectWithTag("PlayerCamera").transform;
		_camera.position	= Vector3.zero;
		_camera.rotation	= Quaternion.identity;

		_camera.position	= transform.position + new Vector3(0.0f, _targetHeight, 0.0f) - (transform.forward - transform.right * _rightOffset) * _defaultDist;
	}

	void Update ()
	{
		// Frame
		if (_timeCounter < _refreshTime)
		{
			_timeCounter += Time.deltaTime;
			_frameCounter++;
		}
		else
		{
			_lastFramerate = (float)_frameCounter / _timeCounter;
			_frameCounter = 0;
			_timeCounter = 0.0f;
		}

		if (FindObjectOfType<PlayerCtl>().GetCameraActive() == false) return;

		transform.position = _player.position;

		float x = Input.GetAxis("Mouse X");
		float y = Input.GetAxis("Mouse Y");
		
		RotateCamera(x, y);
	}

	private void RotateCamera(float x, float y)
	{
		_mouse.x +=  x * _mouseXSensitive;
		_mouse.y += -y * _mouseYSensitive;
		_mouse.y = Mathf.Clamp(_mouse.y, _yMinAngle, _yMaxAngle);

		if (_mouse.x > 360.0f)	_mouse.x -= 360.0f;
		if (_mouse.x <   0.0f)	_mouse.x += 360.0f;

		transform.eulerAngles = new Vector3(_mouse.y, _mouse.x, 0.0f);

		_player.eulerAngles = new Vector3(0.0f, transform.eulerAngles.y, 0.0f);

		_camera.eulerAngles = transform.eulerAngles;
		_camera.position = _player.position + new Vector3(0.0f, _targetHeight, 0.0f) - (transform.forward - transform.right * _rightOffset) * _defaultDist;
	}

	private void OnGUI()
	{
		GUI.TextArea(new Rect(0, 0, 200, 20), "Frame : " + _lastFramerate.ToString());
	}
}
