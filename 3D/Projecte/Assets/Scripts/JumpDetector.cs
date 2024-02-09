using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpDetector : MonoBehaviour
{

    public PlayerController pc;
    void OnTriggerEnter(Collider c)
    {
        if (c.gameObject.CompareTag("collision"))
        {
            pc.die();
        }
    }
    
}