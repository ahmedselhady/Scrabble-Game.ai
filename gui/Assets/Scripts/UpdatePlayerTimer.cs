using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UpdatePlayerTimer : MonoBehaviour
{
    public Text mPlayerTimerText;
    // Time in seconds
    public float mTime = 600;
    void Start()
    {
        // This should start when its the player's turn
        StartCoundownTimer();
    }

    void StartCoundownTimer()
    {
        if (mPlayerTimerText != null)
        {
            // Time in seconds
            mTime = 600;
            mPlayerTimerText.text = "10:00";
            // Keep updating time
            // Will start at 0 seconds and repeat every 0.01667 seconds
            InvokeRepeating("UpdateTimer", 0.0f, 0.01667f);
        }
    }

    void UpdateTimer()
    {
        if (mPlayerTimerText != null)
        {
            string minutes;
            string seconds;
            // TODO: If time runs up, increment it negatively
            // TODO: Only decrement the time of the currently playing player
            if(mTime <= 0){
                
            }
            else {
                mTime -= Time.deltaTime;
                minutes = Mathf.Floor(mTime / 60).ToString("00");
                seconds = (mTime % 60).ToString("00");
                mPlayerTimerText.text = minutes + ":" + seconds;
            }
        }
    }

}
