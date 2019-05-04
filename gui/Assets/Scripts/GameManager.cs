using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using NetMQ;
using NetMQ.Sockets;
using System.IO;

/**
 * This class is the heart of the GUI application.
 * It is responsible for creating a thread to run the communication logic implemented using NetMQ.
 * it is responsible for setting the suitable game panels active and inactive during the game.
 * It is responsible for generating the game tiles and showing them in the GUI window.
 * 
 * This code was written on 3/5/2019
 * @author:Mina Louis
 */

public class GameManager : MonoBehaviour
{
    public GameObject welcomePanel; // Welocome window panel
    public GameObject gamePanel; // Game window panel
    public GameObject owlPanel; // The owl teacher panel
    public GameObject passPanel; // The pass panel
    public GameObject bestMovePanel; // The best move board panel

    public GameObject blankTilePanel;
    public static GameObject staticBlankTilePanel;

    private Thread thread; // Thread used to run the communication part independently from the whole GUI application
    public static Dictionary<string, bool> sowpods;

    public GameObject[] slots; // Rack slots
    public GameObject[] tiles; // Prefab Tiles
    public static GameObject[] staticTiles;
    private GameObject privateTile; // Private GameObject variable used to set the tile in the slots and set the slots as parents for the assigned tile
    
    public GameObject[] hiddenRack; // Rack used to regenerate the rack when the player wants to pass his turn
    public GameObject[,] hiddenBoard; // Board used to regenerate the board when the player wants to pass his turn

    public GameObject player1Timer;
    public GameObject player2Timer;

    public static Board globalGameBoard; // The game board
    public static Rack globalGameRack; // The game rack
    public static Board bestMoveBoard; // The best move board

    public bool playerOnesTurn; // Boolean value to determine which player's turn

    // Start is called before the first frame update
    void Start()
    {
        staticBlankTilePanel = blankTilePanel;
        staticTiles = tiles;

        sowpods = new Dictionary<string, bool>(267753);
        string path = "./Assets/sowpods.txt";
        if(File.Exists(path))
        {
            Debug.Log("I am alive");
            string[] lines = File.ReadAllLines(path);
            foreach(string line in lines)
                sowpods.Add(line, true);
        }
        
        if (MainMenu.teacher)
        {
            welcomePanel.SetActive(true);
            gamePanel.SetActive(false);
            owlPanel.SetActive(true);
        }
        else
        {
            welcomePanel.SetActive(false);
            gamePanel.SetActive(true);
            TileSelector.isInteractable = true;
            owlPanel.SetActive(false);
        }
        passPanel.SetActive(false);
        bestMovePanel.SetActive(false);
        
        globalGameBoard = new Board();
        globalGameRack = new Rack();
        bestMoveBoard = new Board();

        thread = new Thread(ServerIn.Receive_From_Program);
        if (!thread.IsAlive)
            thread.Start();
        else
            Debug.Log("Thread not starting");
    }

    // Update is called once per frame
    void Update()
    {
        rackGenerator();
        ServerIn.Set_Ready_to_Recv(false);
    }

    private void OnDestroy()
    {
        thread.Abort();
    }

    private void OnApplicationQuit()
    {
        thread.Abort();
        NetMQConfig.Cleanup();
    }

    public void rackGenerator()
    {
        string Rack = ServerIn.Get_Rack();
        if (ServerIn.Get_Ready_to_Recv())
        {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 27; j++)
                {
                    if (Rack[i] == tiles[j].GetComponent<Tile>().letter)
                    {
                        globalGameRack.setRack(i, tiles[j], true);
                        break;
                    }
                }
            }

            for (int i = 0; i < 7; i++)
            {
                privateTile = Instantiate(globalGameRack.getTileOnRack(i));
                privateTile.transform.SetParent(slots[i].transform, true);
            }
        }
    }

    //public void bestMoveBoardGenerator()
    //{
    //    if (ServerIn.Get_Ready_to_Recv() && MainMenu.teacher)
    //    {
    //        bestMovePanel.SetActive(true);
    //        TileSelector.isInteractable = false;
    //    }
    //}
}
