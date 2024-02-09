using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkinTemplate : MonoBehaviour
{
    public Material mat1G;
    public Material mat2G;
    public Material mat1S;
    public Material mat2S;
    public Material mat1R;
    public Material mat2R;
    public Material mat1H;
    public Material mat2H;
    public Renderer renderers1;
    public Renderer renderers2;
    GameObject player;
    // Start is called before the first frame update
    void Start()
    {
        int skin = PlayerPrefs.GetInt("Skin");
        if (skin == 1)
        {
            renderers1.material = mat1G;
            renderers2.material = mat2G;
        }
        else if (skin == 2){
            renderers1.material = mat1S;
            renderers2.material = mat2S;
        }
        else if (skin == 3){
            renderers1.material = mat1H;
            renderers2.material = mat2H;
        }
        else if (skin == 4){
            renderers1.material = mat1R;
            renderers2.material = mat2R;
        }
        else{
            renderers1.material = mat1G;
            renderers2.material = mat2G;
        }

        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
