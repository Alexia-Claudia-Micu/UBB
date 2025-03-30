using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class CharacterSelectButton : MonoBehaviour
{
    public string characterName; // Set this in the Inspector (White, Black, Red, Blue)
    public TMP_Text buttonText;
    private GameObject characterPrefab;

    private void Start()
    {
        characterPrefab = CharacterManager.Instance.GetCharacterPrefab(characterName);
        if (characterPrefab == null)
        {
            Debug.LogError($"Character prefab not found for: {characterName}");
        }
        UpdateButtonText();
    }

    public void ToggleSelection()
    {
        if (characterPrefab != null)
        {
            CharacterManager.Instance.ToggleCharacterSelection(characterPrefab);
            UpdateButtonText();
            PlayButton.Instance.UpdatePlayButton();
        }
    }

    private void UpdateButtonText()
    {
        if (CharacterManager.selectedCharacters.Contains(characterPrefab))
        {
            buttonText.text = "Selected";
        }
        else
        {
            buttonText.text = "Select";
        }
    }
}
