using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PassButton : MonoBehaviour
{
    public GameObject passPanel;

    public void passTurn()
    {
        passPanel.SetActive(true);
        TileSelector.isInteractable = false;
    }

    // You shall not pass
    public void youShallNotPass()
    {
        passPanel.SetActive(false);
        TileSelector.isInteractable = true;
    }

    public void youShallPass()
    {
        passPanel.SetActive(false);
        TileSelector.isInteractable = true;
        // TODO: reverse turns
        // TODO: reset every tile to initial position
        for (int x = 0; x < 15; x++)
        {
            for (int y = 0; y < 15; y++)
            {
                if (!GameManager.globalGameBoard.getBoard(x, y) && GameManager.globalGameBoard.getTileOnBoard(x, y).GetComponent<Draggable>().getDrag())
                {
                    //TODO: return to rack
                }
            }
        }
    }
}
