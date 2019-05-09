using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class player1Score : MonoBehaviour
{
    int newScore = 0;
    int accumilativeScore = 0;
    public Text score1;
    // Start is called before the first frame update
    void Start()
    {
        ServerIn.Set_My_Score("0");
    }

    public void updatePlayer1Score()
    {
        newScore = int.Parse(ServerIn.Get_My_Score());
        Debug.Log(newScore);
        accumilativeScore += newScore;
        Debug.Log(accumilativeScore);
        score1.text = accumilativeScore.ToString();
    }
    
}
