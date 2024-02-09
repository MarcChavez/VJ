using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using UnityEngine.SceneManagement;

public class CromosTemplate : MonoBehaviour
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
    public GameObject empty;
    GameObject cromo;
    public Text posicion;
    public Text nameText;
    int i = 0;
    int type = 0;


    public void Start()
    {
        posicion.text = (i+1).ToString();
        type = PlayerPrefs.GetInt("Type");
        if (type == 0)
        {
            string name = "BE";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Beasts[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/15";
        }
        else if (type == 1)
        {
           string name = "BO";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Bosses[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5"; 
        }
        else if (type == 2)
        {
            string name = "DR";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Dragons[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5"; 
        }
        else if (type == 3)
        {
            string name = "GI";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Giants[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5";  
        }
        else if (type == 4)
        {
            string name = "GB";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Goblins[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5"; 
        }
        else if (type == 5)
        {
            string name = "HG";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Hags[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5";  
        }
        else if (type == 6)
        {
            string name = "QU";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Quidditch[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5"; 
        }
        else if (type == 7)
        {
            string name = "VP";
            name += (char)i;
            char c = '0';
                        c += (char)(i+1);
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Vampires[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/5"; 
        }
        else if (type == 8)
        {
            string name = "WI";
            char c = '0';
            c += (char)(i+1);
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Witches[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/15"; 
        }
        else if (type == 9)
        {
            string name = "WZ";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Wizards[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            posicion.text += "/15"; 
        }
    }


    public void next()
    {
        if (type == 0)
        {
            Destroy(cromo);
            ++i;
            if (i == 15) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "BE";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Beasts[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            
        }
        else if (type == 1)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "BO";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Bosses[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 2)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "DR";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Dragons[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 3)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "GI";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Giants[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 4)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "GB";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Goblins[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 5)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "HG";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Hags[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 6)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "QU";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Quidditch[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 7)
        {
            Destroy(cromo);
            ++i;
            if (i == 5) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "VP";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Vampires[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 8)
        {
            Destroy(cromo);
            ++i;
            if (i == 15) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "WI";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Witches[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 9)
        {
            Destroy(cromo);
            ++i;
            if (i == 15) i = 0;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "WZ";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Wizards[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
    }

    public void previous()
    {
        if (type == 0)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 14;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "BE";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Beasts[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
            
        }
        else if (type == 1)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "BO";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Bosses[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 2)
        {
            Destroy(cromo);
            --i;
            if (i ==-1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "DR";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Dragons[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 3)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "GI";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Giants[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 4)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "GB";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Goblins[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 5)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "HG";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Hags[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 6)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "QU";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Quidditch[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 7)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 4;
            posicion.text = (1+i).ToString();
            posicion.text += "/5"; 
            string name = "VP";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Vampires[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 8)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 14;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "WI";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c); 
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Witches[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
        else if (type == 9)
        {
            Destroy(cromo);
            --i;
            if (i == -1) i = 14;
            posicion.text = (1+i).ToString();
            posicion.text += "/15"; 
            string name = "WZ";
            int tmp = i+1;
            string c = tmp.ToString();
            string oName = PlayerPrefs.GetString(name+c);
            if (PlayerPrefs.GetInt(oName) == 1)
            {
                cromo = Instantiate(Wizards[i], new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = oName;
            }
            else{
                cromo = Instantiate(empty, new Vector3((float)46.9f,11.94f,24.21f), Quaternion.identity);
                cromo.transform.Rotate(0, 180, 0);
                nameText.text = "????";
            }
        }
    }

    public void goBack()
    {
        string sceneName = "Cromos";
        SceneManager.LoadScene(sceneName);
    }

}
