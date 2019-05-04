using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PanelTransitionBegin : MonoBehaviour
{
    private Animator anime;
    public void BeginTransition()
    {
        anime.Play("BeginGame");
    }

    private void Start()
    {
        anime = GetComponent<Animator>();
    }
}
