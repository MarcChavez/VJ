using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shop : MonoBehaviour
{
    
    private CharacterController controller;

    public float playerSpeed = 10.0f;

    public Animator anim;

    public Rigidbody rb;
    
    // Start is called before the first frame update
    void Start()
    {
        playerSpeed = 22f; //12.5
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
