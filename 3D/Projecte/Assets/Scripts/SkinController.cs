using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SkinController : MonoBehaviour
{
    
    private CharacterController controller;
    public Animator anim;

    public Rigidbody rb;
    

    
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();

    }
}
