using TMPro;
using UnityEngine;

public class ScoreDisplay : MonoBehaviour
{
    public string characterName;
    private TMP_Text scoreText;

    private void Start()
    {
        scoreText = GetComponent<TMP_Text>();
        UpdateScore();
    }

    private void Update()
    {
        UpdateScore();
    }

    private void UpdateScore()
    {
        // Get the corresponding prefab for the character
        GameObject characterPrefab = CharacterManager.Instance.GetCharacterPrefab(characterName);
        if (characterPrefab != null)
        {
            int score = CharacterManager.Instance.GetScore(characterPrefab);
            scoreText.text = "Score: " + score;
        }
        else
        {
            scoreText.text = "Score: 0";
            Debug.LogWarning($"Character {characterName} not found in CharacterManager.");
        }
    }
}
