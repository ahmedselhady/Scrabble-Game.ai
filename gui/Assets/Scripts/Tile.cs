using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour
{
    private bool onBoard;
    private bool onRack;
    public char letter;

    public Tile() { }

    public void setOnBoard(bool value)
    {
        onBoard = value;
    }

    public bool getOnBoard()
    {
        return onBoard;
    }

    public void setOnRack(bool value)
    {
        onRack = value;
    }

    public bool getOnRack()
    {
        return onRack;
    }
}
