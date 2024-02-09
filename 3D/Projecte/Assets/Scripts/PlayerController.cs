using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayerController : MonoBehaviour
{
    
    private CharacterController controller;
    public bool verticalMove;
    public float playerSpeed;
    public float velocidadRotacion = 250.0f;
    public Animator anim;
    public Text textoCanvas;
    public Image image;
    public Rigidbody rb;
    public AudioClip soundClip;
    
    public float fuerzaSalto = 50f;
    public bool Jump;
    public bool ground;
    public bool isRotating = false;
    public bool Spacepressed;
    public bool rotateLeft;
    public int alreadyJump;
    public bool canJump;
    public int dirTurn;
    bool dead = false;
    public bool gira = true;
    public int distancia = 0;
    float cuenta = 0.0f;
    bool startCuenta = false;
    bool godMode = false;
    int action = 0;
    public float trans = 0;
    bool teclapress = false;
    
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        fuerzaSalto = 200f;
        Spacepressed = false;
        alreadyJump = 0;
        rotateLeft = false;
        canJump = true;
        Jump = false;
        playerSpeed = 18f; //12.5 
    }

    public void teFuiste()
    {
        startCuenta = true;
    }

    // Update is called once per frame
    void Update()
    {

        if (startCuenta)
            cuenta += Time.deltaTime;
        
        if (cuenta >= 4.0f)
        {
            trans += 5*Time.deltaTime;
            Color currentColor = Color.black;;
            currentColor.a = trans;
            image.color = currentColor;
            if (trans >= 2.5f)
            {
                if (PlayerPrefs.GetInt("Score") < distancia) PlayerPrefs.SetInt("Score", distancia);
                PlayerPrefs.SetInt("Puntos", distancia);
                string sceneName = "FinalDead";
                SceneManager.LoadScene(sceneName);
            }
        }

        if ((int)transform.rotation.eulerAngles.y == 0 || (int)transform.rotation.eulerAngles.y == 180)
            verticalMove = true;
        else if ((int)transform.rotation.eulerAngles.y == 90 || (int)transform.rotation.eulerAngles.y == 270)
            verticalMove = false;

        anim.SetFloat("velX", Time.deltaTime*playerSpeed);

        if (Input.GetKeyUp("space"))
        {
            Jump = false;
            Spacepressed = false;
        }

        if (Input.GetKeyUp(KeyCode.G))
        {
            teclapress = false;
        }

        if (Input.GetKey(KeyCode.G) && !teclapress)
        {
            godMode = !godMode;
            teclapress = true;
        }

        if (Input.GetKey("space") && !Spacepressed && canJump && !godMode)
        {
            Spacepressed = true;
            if (alreadyJump == 0) anim.SetBool("jump", true);
            else if (alreadyJump == 1) anim.SetBool("jumpA", true);
            anim.SetBool("ground", false);
        }

         if (anim.GetCurrentAnimatorStateInfo(0).normalizedTime > 1 && anim.GetCurrentAnimatorStateInfo(0).IsName("Falling Back Death"))
         {
            trans += 5*Time.deltaTime;
            Color currentColor = Color.black;;
            currentColor.a = trans;
            image.color = currentColor;
            if (trans >= 3.5f)
            {
                if (PlayerPrefs.GetInt("Score") < distancia) PlayerPrefs.SetInt("Score", distancia);
                PlayerPrefs.SetInt("Puntos", distancia);
                string sceneName = "FinalDead";
                SceneManager.LoadScene(sceneName);
            }
         }
    }

    public Vector3 getPosition()
    {
        return transform.position;
    }

    public void sumaDist()
    {
        ++distancia;
    }

    void CambiarTexto()
    {
        textoCanvas.text = distancia.ToString();
    }

    void FixedUpdate()
    {
        if (!dead)
        {
            
            if (godMode)
            {
                if ((isRotating && godMode && gira))
                {
                    if (rotateLeft) transform.Rotate(0, -90, 0);
                    else
                        transform.Rotate(0, 90, 0);
                    gira = false;
                }
                
                if (alreadyJump < 2 && !Jump && Spacepressed && canJump)
                {
                    rb.velocity = Vector3.zero;
                    rb.angularVelocity = Vector3.zero;
                    rb.AddForce(new Vector3(0,fuerzaSalto,0), ForceMode.Impulse);
                    alreadyJump++;
                    Jump = true;
                }
            }
            else{
                if (isRotating && !Jump && gira)
                {
                    if (rotateLeft) transform.Rotate(0, -90, 0);
                    else
                        transform.Rotate(0, 90, 0);
                    gira = false;
                }
                
                if (alreadyJump < 2 && !Jump && Spacepressed)
                {
                    rb.velocity = Vector3.zero;
                    rb.angularVelocity = Vector3.zero;
                    rb.AddForce(new Vector3(0,fuerzaSalto,0), ForceMode.Impulse);
                    alreadyJump++;
                    Jump = true;
                    
                }
            }
            CambiarTexto();
            transform.Translate(new Vector3(0,0,playerSpeed*Time.deltaTime));
        }
    }

    public void salta()
    {
        Spacepressed = true;
        Jump = false;
        if (alreadyJump == 0) anim.SetBool("jump", true);
        else if (alreadyJump == 1) anim.SetBool("jumpA", true);
        anim.SetBool("ground", false);
    }

    public void win(){
        if (PlayerPrefs.GetInt("Score") < distancia) PlayerPrefs.SetInt("Score", distancia);
        PlayerPrefs.SetInt("Puntos", distancia);
    }

    public void die() 
    {
        AudioSource audioSource = GetComponent<AudioSource>();
        if (audioSource == null)
        {
            audioSource = gameObject.AddComponent<AudioSource>();
        }
        audioSource.clip = soundClip;
        audioSource.volume = 1f;
        if (!dead) audioSource.Play();
        dead = true;
        anim.SetBool("die", true);
        if (PlayerPrefs.GetInt("Score") < distancia) PlayerPrefs.SetInt("Score", distancia);
        PlayerPrefs.SetInt("Puntos", distancia);
    }

}
