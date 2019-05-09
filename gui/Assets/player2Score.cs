using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class player2Score : MonoBehaviour
{
    int newScore = 0;
    int accumilativeScore = 0;
    public Text score2;
    // Start is called before the first frame update
    void Start()
    {
        ServerIn.Set_Opp_score("0");
    }

    public void updatePlayer2Score()
    {
        newScore = int.Parse(ServerIn.Get_Opp_score());
        Debug.Log(newScore);
        accumilativeScore += newScore;
        Debug.Log(accumilativeScore);
        score2.text = accumilativeScore.ToString();
        GameManager.playerOnesTurn = !GameManager.playerOnesTurn;
    }
}
