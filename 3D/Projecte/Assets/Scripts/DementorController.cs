using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class DementorController : MonoBehaviour
{
    public float playerSpeed;
    public bool isRotating = false;
    public bool rotateLeft;
    public int dirTurn;
    public bool gira = true;
    public bool baja = false;
    bool dead = false;
    bool lento = false;
    public PlayerController pc;
    bool flash = false;
    public Image image;
    float trans = 0;
    
    // Start is called before the first frame update
    void Start()
    {
        playerSpeed = 18f; //12.5
        rotateLeft = false;
        dirTurn = 1; //Recto / 0-> Horizontal
    }

    void Update()
    {
        if (flash) {
            trans += 5*Time.deltaTime;
            Color currentColor = image.color;
            currentColor.a = trans;
            image.color = currentColor;
            pc.win();
            string sceneName = "FinalWin";
            SceneManager.LoadScene(sceneName);
        }
    }

    public void activaFlash()
    {
        flash = true;
    }

    public void noGires()
    {
        dead = true;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (isRotating && gira && !dead)
        {
            if (rotateLeft)
            {
                transform.Rotate(0, -90, 0);
                if (dirTurn == 1) dirTurn = 0;
                else dirTurn = 1;
            } 
            else
            {
                transform.Rotate(0, 90, 0);
                if (dirTurn == 1) dirTurn = 0;
                else dirTurn = 1;
            }
            gira = false;
        }

        else if (baja)
        {
            transform.Translate(new Vector3(0,-10*Time.deltaTime,0));
        }
        transform.Translate(new Vector3(0,0,playerSpeed*Time.deltaTime));
    }
}
