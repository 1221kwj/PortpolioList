using UnityEngine;

public class CameraMovement : MonoBehaviour
{
	private Vector3 lastMouse = new Vector3(0, 0, 0);

	void Start () {}
	
	void Update ()
	{
		lastMouse = Input.mousePosition - lastMouse;
		lastMouse = new Vector3(-lastMouse.y * 0.8f, lastMouse.x * 0.8f, 0);
		lastMouse = new Vector3(transform.eulerAngles.x + lastMouse.x, transform.eulerAngles.y + lastMouse.y, 0);
		transform.eulerAngles = lastMouse;
		lastMouse = Input.mousePosition;

		float x = Input.GetAxis("Horizontal");
		float z = Input.GetAxis("Vertical");

		float speedAdj = 1.0f;

		if (Input.GetKey(KeyCode.LeftShift)) speedAdj = 5.0f;

		if		(Input.GetKey(KeyCode.E)) { transform.Translate(Vector3.up		* Time.deltaTime * 5.0f); }
		else if (Input.GetKey(KeyCode.Q)) { transform.Translate(Vector3.down	* Time.deltaTime * 5.0f); }

		transform.position += transform.forward * z * Time.deltaTime * 5.0f * speedAdj;
		transform.position += transform.right * x * Time.deltaTime * 5.0f * speedAdj;
	}

	public void SetCameraPosition(Vector3 pos, Vector3 eulerAngle)
	{
		transform.position		= pos;
		transform.eulerAngles	= eulerAngle;
	}
}
