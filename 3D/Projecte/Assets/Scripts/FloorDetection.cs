using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloorDetection : MonoBehaviour
{
    public PlayerController pc;
    public SceneSpawn sp;
    public CromosST cst;
    public CameraController cc;
    public DementorController dc;
    bool sali = true;
    bool outsideMap = false;
    public Material mat;
    public Renderer[] renderers;
    int baldosas = 0;
    bool pinta = true;
    bool godMode = false;
    public PatronusCont patronus;
    public AudioClip soundClip;
    bool teclapress = false;

    void Update(){
        if (Input.GetKeyUp(KeyCode.G))
        {
            teclapress = false;
        }

        if (Input.GetKey(KeyCode.G) && !teclapress)
        {
            godMode = !godMode;
            teclapress = true;
        }
    }

    public void ChangeObjectsMaterial()
    {
        // Cambiar el material de cada objeto en el array de renderizadores
        renderers[baldosas].material = mat;
    }

    void OnCollisionEnter(Collision c)
    {
        if (pc.alreadyJump > 0)
        {
            pc.anim.SetBool("ground", true);
            pc.alreadyJump = 0;
            pc.anim.SetBool("jump", false);
            pc.anim.SetBool("jumpA", false);
        }
     
        if (!c.gameObject.CompareTag("Floor") && !c.gameObject.CompareTag("Puente")&& outsideMap)
        {
            if (c.gameObject.CompareTag("startPat"))
            {
                AudioSource audioSource = GetComponent<AudioSource>();
                if (audioSource == null)
                {
                    audioSource = gameObject.AddComponent<AudioSource>();
                }
                audioSource.clip = soundClip;
                audioSource.Play();   
            }

            else if (c.gameObject.CompareTag("Finish"))
            {
                cc.stopCamera();
                patronus.move = true;   
            }
            else{
                cc.stopCamera();
                dc.noGires();
                pc.teFuiste();
            }        
        }
        
    }

    void OnCollisionExit(Collision c)
    {
        if (c.gameObject.CompareTag("Floor"))
        {
            outsideMap = true;
        }    
    }

    void OnTriggerEnter(Collider c)
    {
        if (c.gameObject.CompareTag("WI") || c.gameObject.CompareTag("WZ") || c.gameObject.CompareTag("BO") || c.gameObject.CompareTag("DR") || c.gameObject.CompareTag("VP") 
         || c.gameObject.CompareTag("GI") || c.gameObject.CompareTag("QU") || c.gameObject.CompareTag("HG") || c.gameObject.CompareTag("BE") || c.gameObject.CompareTag("GB"))
        {
            Debug.Log("Cromo");
            cst.updateCromo(c.gameObject.tag);
        }

        pc.canJump = false;


        if ((c.gameObject.CompareTag("TurnLeft") || c.gameObject.CompareTag("TurnRight") || c.gameObject.CompareTag("godLeft") || c.gameObject.CompareTag("godRight")) && sali)
        {
            sp.sumaGiro();
            sali = false;
        }

         if (godMode) {
            if (c.gameObject.CompareTag("jump"))
            {
                pc.salta();
            }

            if (c.gameObject.CompareTag("godLeft"))
            {
                pc.gira = true;
                pc.canJump = false;  
                if (pc.alreadyJump == 0)
                { 
                    pc.isRotating = true;
                    pc.rotateLeft = true;
                    pc.dirTurn = -1;
                    if (pinta)
                    {
                        ChangeObjectsMaterial();
                        ++baldosas;
                        pinta = false;
                        pc.sumaDist();
                    }
                } 
            }
            
            else if (c.gameObject.CompareTag("godRight"))
            {
                pc.gira = true;
                pc.canJump = false;  
                if (pc.alreadyJump == 0)
                { 
                    pc.isRotating = true;
                    pc.rotateLeft = false;
                    pc.dirTurn = 1;
                    if (pinta)
                    {
                        ChangeObjectsMaterial();
                        ++baldosas;
                        pinta = false;
                        pc.distancia++;
                    }
                } 
            }
        }
    }

    void OnTriggerExit(Collider c)
    {
        pc.canJump = true;
        pc.isRotating = false;
        if (godMode)
        {
            if (c.gameObject.CompareTag("godLeft") || c.gameObject.CompareTag("godRight"))
                pc.gira = true;
        }
        else
        {
            if (c.gameObject.CompareTag("TurnLeft") || c.gameObject.CompareTag("TurnRight"))
                pc.gira = true;
        }
        sali = true;
        pinta = true;
    }

    void OnTriggerStay(Collider c){
        if (c.gameObject.CompareTag("TurnLeft") || c.gameObject.CompareTag("godLeft"))
        {
           pc.canJump = false;  
           if (Input.GetKey("space") && pc.alreadyJump == 0 && !godMode)
            { 
                pc.isRotating = true;
                pc.rotateLeft = true;
                pc.dirTurn = -1;
                if (pinta)
                {
                    ChangeObjectsMaterial();
                    ++baldosas;
                    pinta = false;
                    pc.sumaDist();
                }
            } 
        }
        else if (c.gameObject.CompareTag("TurnRight") || c.gameObject.CompareTag("godRight"))
        {
           pc.canJump = false;  
           if (Input.GetKey("space") && pc.alreadyJump == 0 && !godMode)
            { 
                pc.isRotating = true;
                pc.rotateLeft = false;
                pc.dirTurn = 1;
                if (pinta)
                {
                    ChangeObjectsMaterial();
                    ++baldosas;
                    pinta = false;
                    pc.distancia++;
                }
            } 
        }
        else{
            pc.canJump = true;   
        }
    }
    
}