using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SubmitButton : MonoBehaviour
{
    public GameObject board;
    public GameObject bestMoveBoard;

    public string wordOnBoard;
    public int colStart = -1;
    public int rowStart = -1;

    public void submit()
    {
        if (!checkInDictionaryCol() || !checkInDictionaryRow())
        {
            ServerIn.Set_Message_From_Teacher("This is an invalid move");
            return;
        }

        Debug.Log("Submit works");
        for (int x = 0; x < 15; x++) // Column
            for (int y = 0; y < 15; y++) // Row
                if (!GameManager.globalGameBoard.getBoard(x, y))
                {
                    Debug.Log("X = " + x + ",Y = " + y + GameManager.globalGameBoard.getTileOnBoard(x, y).GetComponent<Draggable>().getDrag());
                    if (!GameManager.globalGameBoard.getTileOnBoard(x, y).GetComponent<Draggable>().getDrag())
                    {
                        GameManager.bestMoveBoard.setBoard(x, y, GameManager.globalGameBoard.getTileOnBoard(x, y), false);

                    }
                    else
                    {
                        if(colStart == -1 && rowStart == -1)
                        {
                            colStart = x;
                            rowStart = y;
                        }
                        else
                        {
                            if (x > colStart)
                                ServerIn.Set_Horizontal_From_Gui(true); // Orientation is horizontal
                            else if (y > rowStart)
                                ServerIn.Set_Horizontal_From_Gui(false); // Orientation is vertical
                        }
                        wordOnBoard += GameManager.globalGameBoard.getTileOnBoard(x, y).GetComponent<Tile>().letter.ToString();
                        GameManager.globalGameBoard.getTileOnBoard(x, y).GetComponent<Draggable>().setDrag(false);
                    }
                }

        ServerIn.Set_Start_Col_From_Gui(colStart.ToString());
        ServerIn.Set_Start_Row_From_Gui(rowStart.ToString());
        ServerIn.Set_Word_From_GUi(wordOnBoard.ToLower());
        rowStart = -1;
        colStart = -1;
        GameManager.playerOnesTurn = !GameManager.playerOnesTurn;
        
        //GameManager.globalGameRack = new Rack();
        //for (int i = 0; i < 7; i++)
        //{
        //    if (GameManager.globalGameRack.getRack(i))
        //    {
        //        GameManager.globalGameRack.getTileOnRack(i).gameObject.transform.SetParent(board.transform, true);
        //        Destroy(GameManager.globalGameRack.getTileOnRack(i).gameObject);
        //        Debug.Log("Destroyed");
        //    }
        //}
        Debug.Log(wordOnBoard.ToLower());
        ServerIn.Set_Ready_to_Send(true);
        Debug.Log("set to true"+ServerIn.Get_Ready_to_Send());

        if (MainMenu.teacher)
        {
            FindObjectOfType<GameManager>().bestMoveBoardGenerator();
        }
    }

    private bool checkInDictionaryRow()
    {
        string word = "";
        for (int row = 0; row < 15; ++row)
        {
            word = "";
            for (int col = 0; col < 15; ++col)
            {
                word = "";
                while (col < 15 && !GameManager.globalGameBoard.getBoard(row, col))
                {
                    word += GameManager.globalGameBoard.getTileOnBoard(row, col).GetComponent<Tile>().letter.ToString().ToLower();
                    ++col;
                }
                // once i am out, ana la2eet makan fady, zawedoooooo
                // check on this word:
                if (word.Length > 1 && !GameManager.sowpods.ContainsKey(word)) return false; // board is fucked
            }
        }
        // am not fucked:
        return true;
    }

    private bool checkInDictionaryCol()
    {
        string word = "";
        for (int row = 0; row < 15; ++row)
        {
            word = "";
            for (int col = 0; col < 15; ++col)
            {
                word = "";
                while (col < 15 && !GameManager.globalGameBoard.getBoard(col, row))
                {
                    word += GameManager.globalGameBoard.getTileOnBoard(col, row).GetComponent<Tile>().letter.ToString().ToLower();
                    ++col;
                }
                // once i am out, ana la2eet makan fady, zawedoooooo
                // check on this word:

                if (word.Length > 1 && !GameManager.sowpods.ContainsKey(word)) return false; // board is fucked
            }
        }
        // am not fucked:
        return true;
    }
}
