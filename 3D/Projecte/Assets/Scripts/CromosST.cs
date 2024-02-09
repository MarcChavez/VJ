using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;


public class CromosST : MonoBehaviour
{
    public GameObject[] Beasts;
    public GameObject[] Bosses;
    public GameObject[] Dragons;
    public GameObject[] Giants;
    public GameObject[] Goblins;
    public GameObject[] Hags;
    public GameObject[] Quidditch;
    public GameObject[] Vampires;
    public GameObject[] Witches;
    public GameObject[] Wizards;
    string tagTaken;

    int numeroAleatorio;
    public AudioClip soundClip;
    GameObject skin;
    float time = 0;
    bool taken = false;
    System.Random random = new System.Random();

    // Start is called before the first frame update
    void Start()
    {
        int coleccionAleatoria = random.Next(1, 11);
        if (coleccionAleatoria == 1 || coleccionAleatoria == 9 || coleccionAleatoria == 10)
            spawnQuince(coleccionAleatoria);
        else
            spawnCinco(coleccionAleatoria);
    }

    void Update(){
        if (taken){
            if (time <= 0.75f){
                time += Time.deltaTime;
                skin.transform.Rotate(0, 1500f*Time.deltaTime, 0);
                skin.transform.Translate(new Vector3(0,10f*Time.deltaTime,0));
            }
            else{
                Destroy(skin);
                int tmp = numeroAleatorio;
                string c = tmp.ToString();
                string oName = PlayerPrefs.GetString(tagTaken+c); 
                Debug.Log(oName);
                PlayerPrefs.SetInt(oName, 1);
                taken = false;
            }
        }
    }

    // Update is called once per frame
    public void updateCromo(string tag)
    {
        taken = true;
        tagTaken = tag;
        AudioSource audioSource = GetComponent<AudioSource>();
        if (audioSource == null)
        {
            audioSource = gameObject.AddComponent<AudioSource>();
        }
        audioSource.clip = soundClip;
        audioSource.volume = 1f;
        audioSource.Play();
    }

    public void spawnCinco(int i)
    {
        numeroAleatorio = random.Next(1, 6);
        if (i == 2)
            skin = Instantiate(Bosses[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 3)
            skin = Instantiate(Dragons[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 4)
            skin = Instantiate(Giants[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 5)
            skin = Instantiate(Goblins[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 6)
            skin = Instantiate(Hags[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 7)
            skin = Instantiate(Quidditch[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 8)
            skin = Instantiate(Vampires[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
    }

    public void spawnQuince(int i)
    {
        numeroAleatorio = random.Next(1, 16);
        if (i == 9)
            skin = Instantiate(Witches[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        
        else if (i == 1)
            skin = Instantiate(Beasts[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
        else if (i == 10)
            skin = Instantiate(Wizards[numeroAleatorio-1], new Vector3(25.83f, 1.04f, 461.14f), Quaternion.identity);
    }
}
