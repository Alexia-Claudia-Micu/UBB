using System.Collections.Generic;
using UnityEngine;

public class CharacterManager : MonoBehaviour
{
    public static CharacterManager Instance { get; private set; } // Singleton Instance

    public List<GameObject> characterPrefabs; // Assign all character prefabs in the Inspector
    private Dictionary<string, int> characterScores = new Dictionary<string, int>(); // Now uses names

    public static List<GameObject> selectedCharacters = new List<GameObject>(); // Stores selected characters

    private static Dictionary<string, string> nameMapping = new Dictionary<string, string>
    {
        { "White", "PlayerWhite" },
        { "Black", "PlayerBlack" },
        { "Red", "PlayerRed" },
        { "Blue", "PlayerBlue" }
    };

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject); // Keep this GameObject alive across scenes
            InitializeScores();
        }
        else
        {
            Destroy(gameObject); // Ensures only one instance exists
        }
    }

    private void InitializeScores()
    {
        characterScores.Clear();
        foreach (GameObject prefab in characterPrefabs)
        {
            string prefabName = prefab.name;
            if (!characterScores.ContainsKey(prefabName))
            {
                characterScores[prefabName] = 0; // Initialize score to 0
            }
        }
    }

    // Method to get a character prefab by its simple name (e.g., "White" -> "PlayerWhite")
    public GameObject GetCharacterPrefab(string simpleName)
    {
        if (nameMapping.TryGetValue(simpleName, out string actualPrefabName))
        {
            foreach (GameObject prefab in characterPrefabs)
            {
                if (prefab.name == actualPrefabName)
                {
                    return prefab;
                }
            }
        }

        Debug.LogWarning($"Character {simpleName} not found in CharacterManager.");
        return null;
    }

    // Method to select/deselect a character
    public void ToggleCharacterSelection(GameObject character)
    {
        if (selectedCharacters.Contains(character))
        {
            selectedCharacters.Remove(character);
            Debug.Log($"Deselected: {character.name}");
        }
        else
        {
            if (selectedCharacters.Count < 4) // Max 4 characters
            {
                selectedCharacters.Add(character);
                Debug.Log($"Selected: {character.name}");
            }
            else
            {
                Debug.LogWarning("Cannot select more than 4 characters.");
            }
        }
    }

    // Method to retrieve a character's score by name
    public int GetScore(GameObject character)
    {
        string characterName = character.name.Replace("(Clone)", ""); // Remove (Clone) if present
        if (characterScores.ContainsKey(characterName))
        {
            return characterScores[characterName];
        }
        else
        {
            Debug.LogWarning($"Character {characterName} not found in score list.");
            return 0;
        }
    }

    // Method to update a character's score by name
    public void UpdateScore(GameObject character, int scoreToAdd)
    {
        string characterName = character.name.Replace("(Clone)", ""); // Remove (Clone) if present
        if (characterScores.ContainsKey(characterName))
        {
            characterScores[characterName] += scoreToAdd;
            Debug.Log($"{characterName} score updated: {characterScores[characterName]}");
        }
        else
        {
            Debug.LogWarning($"Character {characterName} not found in score list.");
        }
    }

    // Method to get selected characters
    public static List<GameObject> GetSelectedCharacters()
    {
        return new List<GameObject>(selectedCharacters);
    }

    // Ensure at least 2 characters are selected
    public static bool CanProceed()
    {
        return selectedCharacters.Count >= 2;
    }
}
