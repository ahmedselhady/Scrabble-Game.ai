using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PanelTransition : MonoBehaviour
{
    public Text inGamePlayer;
    public Text inWelcomePlayer;

    private void CheckInput()
    {
        if(Input.GetKeyDown(KeyCode.Return))
        {
            Debug.Log("Enter is pressed");
            inGamePlayer.text = inWelcomePlayer.text;
            FindObjectOfType<PanelTransitionBegin>().BeginTransition();
        }
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        CheckInput();
    }
}
