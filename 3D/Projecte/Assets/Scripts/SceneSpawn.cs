using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneSpawn : MonoBehaviour
{
    public FloorTemp ft;
    public AudioClip soundClip;
    int i = 0;
    int floorToDelele = 0;
    int floorToCreate = 4;
    // Start is called before the first frame update
    void Start()
    {
        ft = GameObject.FindGameObjectWithTag("Rooms").GetComponent<FloorTemp>();
        for (int j = 4; j < ft.FloorTemplate.Length; ++j)
        {
            //ft.FloorTemplate[j].SetActive(false);
        }
        creaCromos();
        AudioSource audioSource = GetComponent<AudioSource>();
        if (audioSource == null)
        {
            audioSource = gameObject.AddComponent<AudioSource>();
        }
        audioSource.clip = soundClip;
        audioSource.volume = 0.1f;
        audioSource.Play();   
    }

    // Update is called once per frame
    void creaCromos()
    {
        if (PlayerPrefs.GetString("WI1") != "Beatrix Bloxam")
        {
            brujas();
            beasts();
            magos();
            bosses();
            quidditch();
            goblins();
            hags();
            vampire();
            giants();
            dragons();
        }   
    }

    public void sumaGiro()
    {
        ++i;
        if (i % 3 == 0)
        {
            if (floorToCreate < ft.FloorTemplate.Length)
            {
            ft.FloorTemplate[floorToCreate].SetActive(true);
            ++floorToCreate;
            }
             
        }
        if (i % 5 == 0)
        {
            ft.FloorTemplate[floorToDelele].SetActive(false);
            ++floorToDelele;
        }
        
    }

    void brujas()
    {
        PlayerPrefs.SetString("WI1", "Beatrix Bloxam");
        PlayerPrefs.SetString("WI2", "Dymphna Furmage");
        PlayerPrefs.SetString("WI3", "Honoria Nutcombe");
        PlayerPrefs.SetString("WI4", "La Rara Wendelin");
        PlayerPrefs.SetString("WI5", "Jocunda Sykes");
        PlayerPrefs.SetString("WI6", "Carlotta Pinkstone");
        PlayerPrefs.SetString("WI7", "Dorcas Wellbeloved");
        PlayerPrefs.SetString("WI8", "Elfrida Clagg");
        PlayerPrefs.SetString("WI9", "Sacharissa Tugwood");
        PlayerPrefs.SetString("WI10", "Ignatia Wildsmith");
        PlayerPrefs.SetString("WI11", "Hesper Starkey");
        PlayerPrefs.SetString("WI12", "	Cliodna");
        PlayerPrefs.SetString("WI13", "Mirabella Plunkett");
        PlayerPrefs.SetString("WI14", "Morgan le Fay");
        PlayerPrefs.SetString("WI15", "Gunhilda De Gorsemoor");
    }

    void magos()
    {
        PlayerPrefs.SetString("WZ1", "El Miedoso Fulbert");
        PlayerPrefs.SetString("WZ2", "Ethelred el Siempre Listo");
        PlayerPrefs.SetString("WZ3", "Crispin Cronk");
        PlayerPrefs.SetString("WZ4", "Edgar Stroulger");
        PlayerPrefs.SetString("WZ5", "Oswald Beamish");
        PlayerPrefs.SetString("WZ6", "Norvel Twonk");
        PlayerPrefs.SetString("WZ7", "Grogan Stump");
        PlayerPrefs.SetString("WZ8", "Glanmore Peakes");
        PlayerPrefs.SetString("WZ9", "Wilfred Elphick");
        PlayerPrefs.SetString("WZ10", "Profesor Armando Dippet");
        PlayerPrefs.SetString("WZ11", "Mungo Bonham");
        PlayerPrefs.SetString("WZ12", "Dzou Yen");
        PlayerPrefs.SetString("WZ13", "Falco Aesalon");
        PlayerPrefs.SetString("WZ14", "Thaddeus Thurkell");
        PlayerPrefs.SetString("WZ15", "Harry Potter");
    }

    void quidditch()
    {
        PlayerPrefs.SetString("QU1", "Jocelind Wadcock");
        PlayerPrefs.SetString("QU2", "Gwenog Jones");
        PlayerPrefs.SetString("QU3", "Cyprian Youdle");
        PlayerPrefs.SetString("QU4", "Roderick Plumpton");
        PlayerPrefs.SetString("QU5", "Bowman Wright");
    }

    void vampire()
    {
        PlayerPrefs.SetString("VP1", "Sir Herbert Varney");
        PlayerPrefs.SetString("VP2", "Amarillo Lestoat");
        PlayerPrefs.SetString("VP3", "Lady Carmilla Sanguina");
        PlayerPrefs.SetString("VP4", "Blodwyn Bludd");
        PlayerPrefs.SetString("VP5", "aa");
    }

    void goblins()
    {
        PlayerPrefs.SetString("GB1", "Eargit el Feo");
        PlayerPrefs.SetString("GB2", "Alguff el Horroroso");
        PlayerPrefs.SetString("GB3", "Ug el faltón");
        PlayerPrefs.SetString("GB4", "Urg el Sucio");
        PlayerPrefs.SetString("GB5", "Conde Vlad Drácula");
    }

    void hags()
    {
        PlayerPrefs.SetString("HG1", "Babayaga");
        PlayerPrefs.SetString("HG2", "Malodora Grymm");
        PlayerPrefs.SetString("HG3", "Leticia Somnolens");
        PlayerPrefs.SetString("HG4", "Vieja Madre Hubbard");
        PlayerPrefs.SetString("HG5", "Cordelia Misericordia");
    }
    void giants()
    {
        PlayerPrefs.SetString("GI1", "Bran el sediento de sangre");
        PlayerPrefs.SetString("GI2", "Cíclope");
        PlayerPrefs.SetString("GI3", "Goliath");
        PlayerPrefs.SetString("GI4", "Morholt");
        PlayerPrefs.SetString("GI5", "Hengist de Upper Barnton");
    }

    void dragons()
    {
        PlayerPrefs.SetString("DR1", "Gales verde común");
        PlayerPrefs.SetString("DR2", "Hébrido negro");
        PlayerPrefs.SetString("DR3", "Colacuerno húngaro");
        PlayerPrefs.SetString("DR4", "Ridgeback noruego");
        PlayerPrefs.SetString("DR5", " Longhorn rumano");
    }

    void bosses()
    {
        PlayerPrefs.SetString("BO1", "Godric Gryffindor");
        PlayerPrefs.SetString("BO2", "Rowena Ravenclaw");
        PlayerPrefs.SetString("BO3", "Helga Hufflepuff");
        PlayerPrefs.SetString("BO4", "Salazar Slytherin");
        PlayerPrefs.SetString("BO5", "Albus Dumbledore");
    }

    void beasts()
    {
        PlayerPrefs.SetString("BE1", "Imp");
        PlayerPrefs.SetString("BE2", "Doxy");
        PlayerPrefs.SetString("BE3", "Bowtruckle");
        PlayerPrefs.SetString("BE4", "Billywig");
        PlayerPrefs.SetString("BE5", "Gnomo");
        PlayerPrefs.SetString("BE6", "Calamar gigante");
        PlayerPrefs.SetString("BE7", "Mantícora");
        PlayerPrefs.SetString("BE8", "Unicornio");
        PlayerPrefs.SetString("BE9", "Troll de montaña");
        PlayerPrefs.SetString("BE10", "Streeler");
        PlayerPrefs.SetString("BE11", "Sapo púrpura gigante");
        PlayerPrefs.SetString("BE12", "Tritón de doble cola");
        PlayerPrefs.SetString("BE13", "	Gytrash");
        PlayerPrefs.SetString("BE14", "Kelpie");
        PlayerPrefs.SetString("BE15", "Fénix");
    }
}
