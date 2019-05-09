using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TransitionComplete : MonoBehaviour
{
    public GameObject welcomePanel;
    public GameObject gamePanel;

    public void CompleteTransition()
    {
        welcomePanel.SetActive(false);
        gamePanel.SetActive(true);
        TileSelector.isInteractable = true;
    }
}
