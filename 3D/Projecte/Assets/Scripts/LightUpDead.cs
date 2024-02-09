using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class LightUpDead : MonoBehaviour
{
    public Image image;
    public TextMeshProUGUI maxPuntos;
    public TextMeshProUGUI puntos;
    public GameObject buttonC;
    public GameObject buttonE;
    public GameObject buttonC1;
    public GameObject buttonE1;
    float trans = 5.0f;
    // Start is called before the first frame update
    void Start()
    {
        buttonC.SetActive(false);
        buttonE.SetActive(false);
        buttonC1.SetActive(false);
        buttonE1.SetActive(false);
        puntos.text = "Puntos: " + (PlayerPrefs.GetInt("Puntos")).ToString();
        maxPuntos.text = "Record: " + (PlayerPrefs.GetInt("Score")).ToString();
    }

    // Update is called once per frame
    void Update()
    {
            trans -= 2.5f*Time.deltaTime;
            Color currentColor = image.color;
            currentColor.a = trans;
            image.color = currentColor;
            if (trans <= 0.55){
                buttonC.SetActive(true);
                buttonE.SetActive(true);
                buttonC1.SetActive(true);
                buttonE1.SetActive(true);
            }
    }
}
