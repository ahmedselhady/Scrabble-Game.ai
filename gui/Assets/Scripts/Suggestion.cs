using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Suggestion : MonoBehaviour
{
    public Text suggestionTextbox;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        suggestionTextbox.text = ServerIn.getTeacherOpinion();
    }
}
