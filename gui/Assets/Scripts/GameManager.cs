using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using NetMQ;
using NetMQ.Sockets;
using System.IO;
using UnityEngine.UI;

/**
 * This class is the heart of the GUI application.
 * It is responsible for creating a thread to run the communication logic implemented using NetMQ.
 * it is responsible for setting the suitable game panels active and inactive during the game.
 * It is responsible for generating the game tiles and showing them in the GUI window.
 * 
 * This code was written on 3/5/2019
 * author:@minalouis9
 */

public class GameManager : MonoBehaviour
{
    public GameObject welcomePanel; // Welocome window panel
    public GameObject gamePanel; // Game window panel
    public GameObject owlPanel; // The owl teacher panel
    public GameObject passPanel; // The pass panel
    public GameObject bestMovePanel; // The best move board panel

    public GameObject board;

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

    public static bool playerOnesTurn; // Boolean value to determine which player's turn

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
        //Debug.Log(ServerIn.Get_Ready_to_Recv());
        rackGenerator();
        
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
        FindObjectOfType<CountdownTimer>().gameObject.SetActive(true);
        if (ServerIn.Get_Ready_to_Recv())
        {
            for (int i = 0; i < 7; i++)
            {
                if (globalGameRack.getRack(i))
                {
                    //globalGameRack.getTileOnRack(i).gameObject.transform.SetParent(board.transform, true);
                    Destroy(globalGameRack.getTileOnRack(i));
                    Debug.Log("Destroyed");
                }
            }

            Debug.Log("Ready to receive" + Rack);
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 27; j++)
                {
                    if (Rack[i] == tiles[j].GetComponent<Tile>().letter.ToString().ToLower()[0])
                    {
                        Debug.Log(tiles[j]);
                        privateTile = Instantiate(tiles[j]);
                        privateTile.transform.SetParent(slots[i].transform, true);
                        globalGameRack.setRack(i, privateTile, true);
                        break;
                    }
                }
            }

            boardGenerator();

            FindObjectOfType<player1Score>().updatePlayer1Score();
            FindObjectOfType<player2Score>().updatePlayer2Score();
            
            ServerIn.Set_Ready_to_Recv(false);
        }
    }

    public void boardGenerator()
    {
        //Debug.Log("IN BOARD GENERATION");
        Debug.Log("IN BOARD GENERATION");
        int startCol = int.Parse(ServerIn.Get_Start_Col_From_Program());
        int startRow = int.Parse(ServerIn.Get_Start_Row_From_Program());
        Debug.Log("startCol " + startCol + "startRow" + startRow);
        string word = ServerIn.Get_Word_From_Program();
        bool orientation = ServerIn.Get_Horizontal_From_Program();

        for (int i = 0; i < word.Length; )
        {
            for (int j = 0; j < 27; j++)
            {
                if (globalGameBoard.getBoard(startCol,startRow) && word[i] == tiles[j].GetComponent<Tile>().letter.ToString().ToLower()[0])
                {
                    Debug.Log(tiles[j]);
                    privateTile = Instantiate(tiles[j]);
                    globalGameBoard.setBoard(startCol, startRow, privateTile, false);
                    Debug.Log(globalGameBoard.getTileOnBoard(startCol, startRow));
                    float tempCol = (float)startCol;
                    float tempRow = (float)startRow;

                    //Debug.Log("tile is " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7));
                    privateTile.transform.SetParent(board.transform, true);
                    Debug.Log("COL " + ((tempCol * 31.7f) - 221.9f));
                    Debug.Log("ROW " + (-(tempRow * 31.7f) + 221.9f));
                    //privateTile.GetComponent<RectTransform>().position = new Vector3((tempCol * 31.7f) - 221.9f, -(tempRow * 31.7f) + 221.9f, 0f);
                    privateTile.GetComponent<RectTransform>().anchoredPosition = new Vector2(((tempCol * 31.7f) - 221.9f), (-(tempRow * 31.7f) + 221.9f));
                    //Debug.Log("tile has a letter of " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7).GetComponent<Tile>().letter.ToString().ToLower());
                    privateTile.GetComponent<Draggable>().setDrag(false);
                    privateTile.GetComponent<Tile>().setOnBoard(true);
                    privateTile.GetComponent<Tile>().setOnRack(false);
                    i++;

                    break;
                }
            }

            if (orientation)
                startCol++;
            else
                startRow++;
        }  
    }

    public void bestMoveBoardGenerator()
    {
        if (ServerIn.Get_Ready_to_Recv_Best() && MainMenu.teacher)
        {
            bestMovePanel.SetActive(true);
            TileSelector.isInteractable = false;

            Debug.Log("IN BOARD GENERATION");
            int startCol = int.Parse(ServerIn.Get_Start_Col_From_Program_Best());
            int startRow = int.Parse(ServerIn.Get_Start_Row_From_Program_Best());
            Debug.Log("startCol " + startCol + "startRow" + startRow);
            string word = ServerIn.Get__Best_Word();
            bool orientation = ServerIn.Get_Horizontal_From_Program_Best();

            for (int i = 0; i < word.Length;)
            {
                for (int j = 0; j < 27; j++)
                {
                    if (bestMoveBoard.getBoard(startCol, startRow) && word[i] == tiles[j].GetComponent<Tile>().letter.ToString().ToLower()[0])
                    {
                        Debug.Log(tiles[j]);
                        privateTile = Instantiate(tiles[j]);
                        bestMoveBoard.setBoard(startCol, startRow, privateTile, false);
                        //Debug.Log(globalGameBoard.getTileOnBoard(startCol, startRow));
                        float tempCol = (float)startCol;
                        float tempRow = (float)startRow;

                        //Debug.Log("tile is " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7));
                        privateTile.transform.SetParent(bestMovePanel.transform, true);
                        Debug.Log("COL " + ((tempCol * 31.7f) - 221.9f));
                        Debug.Log("ROW " + (-(tempRow * 31.7f) + 221.9f));
                        //privateTile.GetComponent<RectTransform>().position = new Vector3((tempCol * 31.7f) - 221.9f, -(tempRow * 31.7f) + 221.9f, 0f);
                        privateTile.GetComponent<RectTransform>().anchoredPosition = new Vector2(((tempCol * 31.7f) - 221.9f), (-(tempRow * 31.7f) + 221.9f));
                        //Debug.Log("tile has a letter of " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7).GetComponent<Tile>().letter.ToString().ToLower());
                        privateTile.GetComponent<Draggable>().setDrag(false);
                        privateTile.GetComponent<Tile>().setOnBoard(true);
                        privateTile.GetComponent<Tile>().setOnRack(false);
                        i++;

                        break;
                    }
                }

                if (orientation)
                    startCol++;
                else
                    startRow++;
            }

        }
    }
}
