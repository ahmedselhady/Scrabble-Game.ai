using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class player2Time : MonoBehaviour
{
    public Text mPlayerTimerText;
    // Time in seconds
    public float mTime = 600;
    void Start()
    {
        mTime = 600;
        mPlayerTimerText.text = "10:00";
    }

    private void Update()
    {
        //if (!GameManager.playerOnesTurn)
        mPlayerTimerText.text = ServerIn.Get_Opp_Time();
                //InvokeRepeating("UpdateTimer", 0.0f, 0.01667f);
    }

    void UpdateTimer()
    {
        if (mPlayerTimerText != null)
        {
            string minutes;
            string seconds;
            // TODO: If time runs up, increment it negatively
            // TODO: Only decrement the time of the currently playing player
            if (mTime <= 0)
            {
                mPlayerTimerText.text = "00:00";
            }
            else
            {
                mTime -= Time.deltaTime;
                minutes = Mathf.Floor(mTime / 60).ToString("00");
                seconds = (mTime % 60).ToString("00");
                mPlayerTimerText.text = minutes + ":" + seconds;
            }
        }
    }

}
