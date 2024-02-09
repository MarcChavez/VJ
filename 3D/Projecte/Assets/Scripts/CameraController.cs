using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public Transform pc;
    public Vector3 offset;
    public bool muevete = true;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (muevete) transform.position = pc.position+offset;
    }

    public void stopCamera()
    {
        muevete = false;
    }
}
