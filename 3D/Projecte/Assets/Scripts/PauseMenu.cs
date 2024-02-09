using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.SceneManagement;

public class PauseMenu : MonoBehaviour
{
    
    public GameObject buttonC;
    public GameObject buttonE;
    public GameObject buttonR;
    // Start is called before the first frame update
    void Start()
    {
        buttonC.SetActive(false);
        buttonE.SetActive(false);
        buttonR.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void RestartGame()
    {
        SceneManager.LoadScene("Main");
        Time.timeScale = 1.0f;
    }

    public void PauseGame()
    {
        if (Time.timeScale == 1.0f)
        {
            Time.timeScale = 0.0f;
            buttonC.SetActive(true);
            buttonE.SetActive(true);
            buttonR.SetActive(true);
        }
        else
        {
            Time.timeScale = 1.0f;
            buttonC.SetActive(false);
            buttonE.SetActive(false);
            buttonR.SetActive(false);
        }
    }

    public void QuitGame()
    {
            SceneManager.LoadScene("Menu");
    }

    public void ResumeGame()
    {
        Time.timeScale = 1.0f;
        buttonC.SetActive(false);
        buttonE.SetActive(false);
        buttonR.SetActive(false);
    }
}
