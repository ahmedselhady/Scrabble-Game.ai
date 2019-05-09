using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class BlankTile : MonoBehaviour
{
    public GameObject slot;
    public GameObject button;
    public GameObject blankTilePanel;

    public GameObject[] tiles;
    private GameObject tile;

    private GameObject[] slotArray;
    private GameObject[] buttonsArray;

    // Start is called before the first frame update
    void Start()
    {
        TileSelector.isInteractable = false;

        for(int i=0;i<26;i++)
        {
            slotArray = new GameObject[26];
            buttonsArray = new GameObject[26];
            slotArray[i] = Instantiate(slot);
            slotArray[i].transform.SetParent(blankTilePanel.transform, true);
            buttonsArray[i] = Instantiate(button);
            buttonsArray[i].transform.SetParent(slotArray[i].transform, true);
            char tempChar = Convert.ToChar('A' + i);
            buttonsArray[i].GetComponentInChildren<Text>().text = tempChar.ToString();
            buttonsArray[i].AddComponent<Tile>().letter = tempChar;
            //buttonsArray[i].AddComponent<ChooseBlankTile>().text = tempChar;
            buttonsArray[i].GetComponent<Button>().onClick.AddListener(delegate { generateTile(tempChar); });
        }
    }

    public void generateTile(char letter)
    {
        Debug.Log("Tile selected is " + letter);
        
        for (int i = 0; i < 27; i++)
            if (GameManager.staticTiles[i].GetComponent<Tile>().letter == letter)
            {
                Debug.Log("inside if condition with tile " + GameManager.staticTiles[i].GetComponent<Tile>().letter);
                tile = Instantiate(GameManager.staticTiles[i]);
                GameManager.globalGameBoard.setBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)Mathf.Abs((TileSelector.coordinateToIndex.y / 31.7f) - 7), tile, false);
                Debug.Log("tile is " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)Mathf.Abs((TileSelector.coordinateToIndex.y / 31.7f) - 7)));
                tile.transform.SetParent(TileSelector.dropTarget.transform, true);
                tile.GetComponent<RectTransform>().position = TileSelector.dropGoPos;
                Debug.Log("tile has a letter of " + GameManager.globalGameBoard.getTileOnBoard((int)(TileSelector.coordinateToIndex.x / 31.7f) + 7, (int)Mathf.Abs((TileSelector.coordinateToIndex.y / 31.7f) - 7)).GetComponent<Tile>().letter.ToString().ToLower());
                //tile.GetComponent<Draggable>().setDrag(false);
                tile.GetComponent<Tile>().setOnBoard(true);
                tile.GetComponent<Tile>().setOnRack(false);
                tile.GetComponent<Image>().color = Color.green;
            }

        TileSelector.isInteractable = true;
        GameManager.staticBlankTilePanel.SetActive(false);
    }

}

