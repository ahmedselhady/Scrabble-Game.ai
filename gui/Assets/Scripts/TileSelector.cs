using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public enum DropTarget {
    None,
    Board,
    Rack,
    Exchange
}

public class TileSelector : MonoBehaviour
{

    public GameObject tileHighlightPrefab;
    private GameObject tileHighlight;

    public RectTransform[] rackSlots;

    public static bool isInteractable; // boolean value to set the board interactable or not

    private Camera cam;

    public static Vector3 dropGoPos;
    public static RectTransform dropTarget = null;
    public static DropTarget dropTargetType = DropTarget.None;
    public static Vector3 coordinateToIndex;

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
        //Debug.Log(isInteractable);
        if (isInteractable)
        {
            RectTransform trans = GetComponent<RectTransform>();
            Vector3 mousePosition = Camera.main.ScreenToViewportPoint(Input.mousePosition);
            mousePosition = trans.InverseTransformPoint(Input.mousePosition);
            //Debug.Log(mousePosition);
            Vector2 cellSize = (trans.rect.size - 4.5f * Vector2.one) / 15;
            mousePosition = new Vector2(Mathf.Round(mousePosition.x / cellSize.x), Mathf.Round(mousePosition.y / cellSize.y)) * cellSize;
            coordinateToIndex = mousePosition;
            dropTargetType = DropTarget.None;
            dropTarget = null;

            if (mousePosition.x > -trans.rect.size.x / 2 && mousePosition.x < trans.rect.size.x / 2 && mousePosition.y > -trans.rect.size.y / 2 && mousePosition.y < trans.rect.size.y / 2)
            {
                //Debug.Log(mousePosition);
                tileHighlight.SetActive(true);
                mousePosition.z = 0.5f;
                tileHighlight.GetComponent<RectTransform>().anchoredPosition = mousePosition;
                dropGoPos = tileHighlight.transform.position;
                dropTargetType = DropTarget.Board;
                dropTarget = trans;
            }
            else
            {
                tileHighlight.SetActive(false);
                foreach (var slotTrans in rackSlots)
                {
                    mousePosition = slotTrans.InverseTransformPoint(Input.mousePosition);
                    if (mousePosition.x > -slotTrans.rect.size.x / 2 && mousePosition.x < slotTrans.rect.size.x / 2 && mousePosition.y > -slotTrans.rect.size.y / 2 && mousePosition.y < slotTrans.rect.size.y / 2)
                    {
                        dropGoPos = slotTrans.transform.position;
                        dropTargetType = DropTarget.Rack;
                        dropTarget = slotTrans;
                        break;
                    }
                }
            }
        }
    }
}
