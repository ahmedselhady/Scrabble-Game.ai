using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Slot: MonoBehaviour
{
    public GameObject tileHighlightPrefab;
    private GameObject tileHighlight;

    private Camera cam;

    public static Vector3 dropGoPos;

    // Start is called before the first frame update
    void Start()
    {
        cam = Camera.main;
        Vector3 point = new Vector3(0, 0, 0);
        tileHighlight = Instantiate(tileHighlightPrefab, point, Quaternion.identity, gameObject.transform);
        tileHighlight.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        RectTransform trans = GetComponent<RectTransform>();
        Vector3 mousePosition = Camera.main.ScreenToViewportPoint(Input.mousePosition);
        mousePosition = trans.InverseTransformPoint(Input.mousePosition);
        Vector2 cellSize = (trans.rect.size - 4.5f * Vector2.one) / 15;
        mousePosition = new Vector2(Mathf.Round(mousePosition.x / cellSize.x), Mathf.Round(mousePosition.y / cellSize.y)) * cellSize;

        if (mousePosition.x > 315 && mousePosition.x < 347 && mousePosition.y > -153 && mousePosition.y < -151)
        {
            Debug.Log(mousePosition);
            tileHighlight.SetActive(true);
            mousePosition.z = 0.5f;
            tileHighlight.GetComponent<RectTransform>().anchoredPosition = mousePosition;
            dropGoPos = tileHighlight.transform.position;
        }
        else
            tileHighlight.SetActive(false);
            
       
    }

}
