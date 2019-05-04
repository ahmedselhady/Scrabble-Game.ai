using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneTransitionBegin : MonoBehaviour
{
    private Animator anime;
    public void BeginTransition()
    {
        anime.Play("SceneAnimation");
    }

    private void Start()
    {
        anime = GetComponent<Animator>();
    }
}
