using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Draggable : MonoBehaviour, IBeginDragHandler, IDragHandler, IEndDragHandler
{
    private Vector3 startPositionWorldCoordinate;
    private Vector3 startPositionBoardCoordinate;
    public static GameObject itemBeingDragged;

    private bool isDraggable = true;

    public bool getDrag()
    {
        return isDraggable;
    }

    public void setDrag(bool value)
    {
        isDraggable = value;
    }


    public void OnBeginDrag(PointerEventData eventData)
    {
        if (!isDraggable)
            eventData.pointerDrag = null;
        Debug.Log("Drag Begin");
        startPositionBoardCoordinate = TileSelector.coordinateToIndex;
        startPositionWorldCoordinate = this.transform.position;
        transform.SetSiblingIndex(transform.parent.childCount - 1);
        //Debug.Log(startPosition);
    }

    public void OnDrag(PointerEventData eventData)
    {
        if (!isDraggable)
            eventData.pointerDrag = null;
        //Debug.Log("Drag");
        GetComponent<RectTransform>().position = eventData.position;
    }

    public void OnEndDrag(PointerEventData eventData)
    {
        if (!isDraggable)
            eventData.pointerDrag = null;
        Debug.Log("Drag End");
        RectTransform trans = GetComponent<RectTransform>();

        if (TileSelector.dropTargetType == DropTarget.Board) // Droping on board
        {
            if (this.GetComponent<Tile>().letter == '#')
            {
                TileSelector.isInteractable = false;
                GameManager.staticBlankTilePanel.SetActive(true);
                Destroy(this.gameObject);
                this.GetComponent<Image>().color = Color.green;
            }

            Debug.Log("Start position " + startPositionBoardCoordinate);
            // Starting drag from the board and droping on the board
            if (startPositionBoardCoordinate.x > -240 && startPositionBoardCoordinate.x < 240 && startPositionBoardCoordinate.y > -240 && startPositionBoardCoordinate.y < 240)
            {
                // if the drop position is empty(true) then drop otherwise drop at start position
                if (GameManager.globalGameBoard.getBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7))
                {
                    Debug.Log("Drag from board on board");
                    GetComponent<RectTransform>().position = TileSelector.dropGoPos;
                    transform.SetParent(TileSelector.dropTarget.transform, true);
                    GameManager.globalGameBoard.setBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7, this.gameObject, false);
                    GameManager.globalGameBoard.setBoard((int)(startPositionBoardCoordinate.x / 31.7f) + 7, (int)(startPositionBoardCoordinate.y / 31.7f) + 7, this.gameObject, true);
                }
                else
                    GetComponent<RectTransform>().position = startPositionWorldCoordinate;
            }
            else // Starting drag from the rack of tiles and dropping on the board
            {
                // if the drop position is empty(true) then drop otherwise drop in the rack of tiles 
                if (GameManager.globalGameBoard.getBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7))
                {
                    Debug.Log("Drag from rack to board");
                    GetComponent<RectTransform>().position = TileSelector.dropGoPos;
                    Debug.Log(TileSelector.dropGoPos);
                    transform.SetParent(TileSelector.dropTarget.transform, true);
                    GameManager.globalGameBoard.setBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)(TileSelector.coordinateToIndex.y / 31.7f) + 7, this.gameObject, false);
                    this.gameObject.GetComponent<Tile>().setOnBoard(true);
                    this.gameObject.GetComponent<Tile>().setOnRack(false);
                }
                else
                    GetComponent<RectTransform>().position = startPositionWorldCoordinate;
            }
        }
        else if (TileSelector.dropTargetType == DropTarget.Rack) // Droping on rack of tiles
        {
            if (startPositionBoardCoordinate.x > -240 && startPositionBoardCoordinate.x < 240 && startPositionBoardCoordinate.y > -240 && startPositionBoardCoordinate.y < 240)
            {
                GameManager.globalGameBoard.setBoard((int)(startPositionBoardCoordinate.x / 31.7f) + 7, (int)(startPositionBoardCoordinate.y / 31.7f) + 7, this.gameObject, true);
                this.gameObject.GetComponent<Tile>().setOnBoard(false);
                this.gameObject.GetComponent<Tile>().setOnRack(true);
            }
            GetComponent<RectTransform>().position = TileSelector.dropGoPos;
            transform.SetParent(TileSelector.dropTarget.transform, true);
        }
        else if (TileSelector.dropTargetType == DropTarget.Exchange) // Droping on exchange rack
        {
            if (startPositionBoardCoordinate.x > -240 && startPositionBoardCoordinate.x < 240 && startPositionBoardCoordinate.y > -240 && startPositionBoardCoordinate.y < 240)
            {
                GameManager.globalGameBoard.setBoard((int)(startPositionBoardCoordinate.x / 31.7f) + 7, (int)(startPositionBoardCoordinate.y / 31.7f) + 7, this.gameObject, true);
                this.gameObject.GetComponent<Tile>().setOnBoard(false);
                this.gameObject.GetComponent<Tile>().setOnRack(true);
            }
            GetComponent<RectTransform>().position = TileSelector.dropGoPos;
            transform.SetParent(TileSelector.dropTarget.transform, true);
        }
        else // Droping on empty space
            GetComponent<RectTransform>().position = startPositionWorldCoordinate;
    }
}
