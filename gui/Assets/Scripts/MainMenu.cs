using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MainMenu : MonoBehaviour
{
    private bool teacherMode = false;
    private bool aiMode = false;
    private bool quitGame = false;

    public static bool teacher;
    public static bool ai;
    public static bool quit;

    public void TeacherModeGame()
    {
        teacherMode = true;
        teacher = teacherMode;
        FindObjectOfType<SceneTransitionBegin>().BeginTransition();
    }

    public void AIModeGame()
    {
        aiMode = true;
        ai = aiMode;
        FindObjectOfType<SceneTransitionBegin>().BeginTransition();
    }

    public void ExitGame()
    {
        quitGame = true;
        quit = quitGame;
        FindObjectOfType<SceneTransitionBegin>().BeginTransition();
    }

    public bool IsTeacherMode()
    {
        return teacherMode;
    }

    public bool IsAIMode()
    {
        return aiMode;
    }

    public bool IsQuit()
    {
        return quitGame;
    }

}
