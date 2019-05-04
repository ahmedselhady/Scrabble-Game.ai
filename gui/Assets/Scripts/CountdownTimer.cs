using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class CountdownTimer : MonoBehaviour
{
    public Text mTimerText;
    // Time in seconds
    public float mTime = 1200;

    //public GameObject mGameOver; // Assign in inspector
    public Scene mGameOver;
    void Start()
    {
        StartCoundownTimer();
    }

    void StartCoundownTimer()
    {
        if (mTimerText != null)
        {
            // Time in seconds
            mTime = 1200;
            mTimerText.text = "20:00";
            // Keep updating time
            // Will start at 0 seconds and repeat every 0.01667 seconds
            InvokeRepeating("UpdateTimer", 0.0f, 0.01667f);
        }
    }

    void UpdateTimer()
    {
        if (mTimerText != null)
        {
            mTime -= Time.deltaTime;
            if (mTime <= 0)
            {
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
                return;
            }
            string minutes = Mathf.Floor(mTime / 60).ToString("00");
            string seconds = (mTime % 60).ToString("00");
            mTimerText.text = minutes + ":" + seconds;
        }
    }

}
