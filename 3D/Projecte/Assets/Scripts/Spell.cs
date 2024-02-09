using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spell : MonoBehaviour
{
    // Start is called before the first frame update
    private CharacterController controller;
    public Animator anim;
    void Start()
    {
        anim = GetComponent<Animator>();
        anim.SetBool("spell", true);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
