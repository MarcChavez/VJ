using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;

public class goToCromo : MonoBehaviour
{
    public TMPro.TextMeshProUGUI buttonTextWizard;
    public TMPro.TextMeshProUGUI buttonTextWitches;
    public TMPro.TextMeshProUGUI buttonTextQuidditch;
    public TMPro.TextMeshProUGUI buttonTextVamp;
    public TMPro.TextMeshProUGUI buttonTextGoblin;
    public TMPro.TextMeshProUGUI buttonTextBoss;
    public TMPro.TextMeshProUGUI buttonTextBeast;
    public TMPro.TextMeshProUGUI buttonTextDragon;
    public TMPro.TextMeshProUGUI buttonTextGiant;
    public TMPro.TextMeshProUGUI buttonTextHag;
    
    private void Start() {
        buttonTextWizard.text = calculaCant15("WZ");
        buttonTextWitches.text = calculaCant15("WI");
        buttonTextQuidditch.text = calculaCant5("QU");
        buttonTextVamp.text = calculaCant5("VP");
        buttonTextGoblin.text = calculaCant5("GB");
        buttonTextBoss.text = calculaCant5("BO");
        buttonTextBeast.text = calculaCant15("BE");
        buttonTextDragon.text = calculaCant5("DR");
        buttonTextGiant.text = calculaCant5("GI");
        buttonTextHag.text = calculaCant5("HG");
    }

    public void Back()
    {
        SceneManager.LoadScene("Menu");  
    }

    private string calculaCant15(string tag) {
        int totalWZ = 0;
        for (int i = 1; i <= 15; ++i)
        {
            string cWZ = i.ToString();
            string oNameWZ = PlayerPrefs.GetString(tag+cWZ);
            if (PlayerPrefs.GetInt(oNameWZ) == 1)
                totalWZ++;
        }
        string end15 = totalWZ.ToString() + "/15";
        return end15;
    }

    private string calculaCant5(string tag) {
        int totalWZ = 0;
        for (int i = 1; i <= 5; ++i)
        {
            string cWZ = i.ToString();
            string oNameWZ = PlayerPrefs.GetString(tag+cWZ);
            if (PlayerPrefs.GetInt(oNameWZ) == 1)
                totalWZ++;
        }
        string end15 = totalWZ.ToString() + "/5";
        return end15;
    }
    
    
    public void Beast()
    {
        PlayerPrefs.SetInt("Type", 0);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Bosses()
    {
        PlayerPrefs.SetInt("Type", 1);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Dragons()
    {
        PlayerPrefs.SetInt("Type", 2);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Giants()
    {
        PlayerPrefs.SetInt("Type", 3);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Hags()
    {
        PlayerPrefs.SetInt("Type",5);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Quidditch()
    {
        PlayerPrefs.SetInt("Type", 6);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Vampires()
    {
        PlayerPrefs.SetInt("Type", 7);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Witches()
    {
        PlayerPrefs.SetInt("Type", 8);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Wizards()
    {
        PlayerPrefs.SetInt("Type", 9);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }

    public void Goblins()
    {
        PlayerPrefs.SetInt("Type", 4);
        string sceneName = "Cromo";
        SceneManager.LoadScene(sceneName);
    }
}
