using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OkButton : MonoBehaviour
{
    public GameObject bestMoveBoard;

    public void Ok()
    {
        bestMoveBoard.SetActive(false);
        TileSelector.isInteractable = true;
    }
}
