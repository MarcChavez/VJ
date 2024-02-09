using System.Collections;  
using System.Collections.Generic;  
using UnityEngine;  
using UnityEngine.SceneManagement;  
public class SceneChanger: MonoBehaviour {  
    public void Scene1() {  
        SceneManager.LoadScene("Main");  
    }  
    public void Scene2() {  
        SceneManager.LoadScene("Tienda");  
    }  
    public void Scene3() {  
        SceneManager.LoadScene("Cromos");  
    }  
    public void Scene4() {  
        SceneManager.LoadScene("Menu");  
    }  
    public void Scene5() {  
        SceneManager.LoadScene("Ins");  
    }

    public void Cred() {  
        SceneManager.LoadScene("Credits");  
    }

}   