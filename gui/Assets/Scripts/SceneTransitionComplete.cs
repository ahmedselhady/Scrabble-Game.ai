using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneTransitionComplete : MonoBehaviour
{
    public void CompleteTransition()
    {
        if (FindObjectOfType<MainMenu>().IsTeacherMode())
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        else if (FindObjectOfType<MainMenu>().IsAIMode())
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
        else
            Application.Quit();
    }
}
