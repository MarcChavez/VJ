using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SkinScript : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject[] Skins;
    public GameObject[] Floors;
    public Scrollbar scrollbar;
    GameObject skin;
    GameObject floor;
    GameObject wall;
    int i = 0;
    void Start()
    {
        skin = Instantiate(Skins[i], new Vector3((float)3.970911,0,0), Quaternion.identity);
        skin.transform.Rotate(0, (float)-17.216, 0);

        floor = Instantiate(Floors[i], new Vector3(0,(float)6.43,-4), Quaternion.identity);
        floor.transform.Rotate(90, 0, 0);
        floor.transform.localScale = new Vector3((float)50.59, (float)0.1, (float)13.3);

        wall = Instantiate(Floors[i], new Vector3(0,(float)-0.14,0), Quaternion.identity);
        wall.transform.localScale = new Vector3(49, (float)0.1, (float)13.3);

    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void gryffindor()
    {  
        Destroy(skin);
        Destroy(floor);
        Destroy(wall);

        PlayerPrefs.SetInt("Skin", 1);

        skin = Instantiate(Skins[0], new Vector3((float)3.970911,0,0), Quaternion.identity);
        skin.transform.Rotate(0, (float)-17.216, 0);

        floor = Instantiate(Floors[i], new Vector3(0,(float)6.43,-4), Quaternion.identity);
        floor.transform.Rotate(90, 0, 0);
        floor.transform.localScale = new Vector3((float)50.59, (float)0.1, (float)13.3);

        wall = Instantiate(Floors[i], new Vector3(0,(float)-0.14,0), Quaternion.identity);
        wall.transform.localScale = new Vector3(49, (float)0.1, (float)13.3);
    }

    public void slytherin()
    {
        Destroy(skin);
        Destroy(floor);
        Destroy(wall);

        PlayerPrefs.SetInt("Skin", 2);

        skin = Instantiate(Skins[1], new Vector3((float)3.970911,0,0), Quaternion.identity);
        skin.transform.Rotate(0, (float)-17.216, 0);

        floor = Instantiate(Floors[1], new Vector3(0,(float)6.43,-4), Quaternion.identity);
        floor.transform.Rotate(90, 0, 0);
        floor.transform.localScale = new Vector3((float)50.59, (float)0.1, (float)13.3);

        wall = Instantiate(Floors[1], new Vector3(0,(float)-0.14,0), Quaternion.identity);
        wall.transform.localScale = new Vector3(49, (float)0.1, (float)13.3);
    }

    public void hufflepuff()
    {
        Destroy(skin);
        Destroy(floor);
        Destroy(wall);

        PlayerPrefs.SetInt("Skin", 3);

        skin = Instantiate(Skins[3], new Vector3((float)3.970911,0,0), Quaternion.identity);
        skin.transform.Rotate(0, (float)-17.216, 0);

        floor = Instantiate(Floors[3], new Vector3(0,(float)6.43,-4), Quaternion.identity);
        floor.transform.Rotate(90, 0, 0);
        floor.transform.localScale = new Vector3((float)50.59, (float)0.1, (float)13.3);

        wall = Instantiate(Floors[3], new Vector3(0,(float)-0.14,0), Quaternion.identity);
        wall.transform.localScale = new Vector3(49, (float)0.1, (float)13.3);
    }

    public void ravenclaw()
    {
        Destroy(skin);
        Destroy(floor);
        Destroy(wall);

        PlayerPrefs.SetInt("Skin", 4);

        skin = Instantiate(Skins[2], new Vector3((float)3.970911,0,0), Quaternion.identity);
        skin.transform.Rotate(0, (float)-17.216, 0);

        floor = Instantiate(Floors[2], new Vector3(0,(float)6.43,-4), Quaternion.identity);
        floor.transform.Rotate(90, 0, 0);
        floor.transform.localScale = new Vector3((float)50.59, (float)0.1, (float)13.3);

        wall = Instantiate(Floors[2], new Vector3(0,(float)-0.14,0), Quaternion.identity);
        wall.transform.localScale = new Vector3(49, (float)0.1, (float)13.3);
    }

    public void rotar()
    {
        float valorActual = scrollbar.value;
        skin.transform.Rotate(0, valorActual, 0);
    }
}
