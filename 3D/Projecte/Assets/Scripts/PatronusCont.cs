using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PatronusCont : MonoBehaviour
{
    public bool move = false;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (move) transform.Translate(new Vector3(0,18f*Time.deltaTime,0));
    }
}
