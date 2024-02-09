using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DementorGira : MonoBehaviour
{
    public DementorController pc;

    bool gira = false;
    int sum = 0;

    void OnTriggerEnter(Collider c)
    {
        if (c.gameObject.CompareTag("patronus"))
        {
            pc.activaFlash();
        }
        if (c.gameObject.CompareTag("godLeft") && !gira)
        {
            pc.isRotating = true;
            pc.rotateLeft = true;
            pc.dirTurn = -1;
            gira = true;
        }
        else if (c.gameObject.CompareTag("godRight") && !gira)
        {
            pc.isRotating = true;
            pc.rotateLeft = false;
            pc.dirTurn = 1;
            gira = true;
        }

        if (c.gameObject.CompareTag("Puente"))
        {
             pc.baja = true;
        } 
    }

    void OnTriggerExit(Collider c)
    {
        pc.isRotating = false;
        pc.gira = true;
        gira = false;  
    }
}