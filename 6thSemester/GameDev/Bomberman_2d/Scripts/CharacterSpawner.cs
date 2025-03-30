using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Tilemaps;
using System.Collections.Generic;

public class GameSessionManager : MonoBehaviour
{
    public static GameSessionManager Instance { get; private set; }

    public Tilemap destructibles;
    private List<GameObject> players = new List<GameObject>(); // Store spawned player instances

    // Define spawn positions for up to 4 characters
    private Vector2[] spawnPositions = new Vector2[]
    {
        new Vector2(-6, 5),  // First player
        new Vector2(6, -5),   // Second player
        new Vector2(-6, -5), // Third player (if selected)
        new Vector2(6, 5)   // Fourth player (if selected)
    };

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void Start()
    {
        SpawnPlayers();
    }

    private void SpawnPlayers()
    {
        players.Clear(); // Reset the players list

        // Get selected characters from CharacterManager
        List<GameObject> selectedCharacters = CharacterManager.GetSelectedCharacters();

        if (selectedCharacters.Count < 2)
        {
            Debug.LogError("Not enough characters selected to start the game.");
            return;
        }

        // Spawn each selected character at the assigned position
        for (int i = 0; i < selectedCharacters.Count; i++)
        {
            if (i < spawnPositions.Length) // Ensure we don't exceed available positions
            {
                GameObject newCharacter = Instantiate(selectedCharacters[i], spawnPositions[i], Quaternion.identity);
                players.Add(newCharacter); // Add spawned player to the list

                // Assign the destructible tilemap to the character's BombController
                BombController bombController = newCharacter.GetComponent<BombController>();
                if (bombController != null)
                {
                    bombController.destructibleTiles = destructibles;
                }
                else
                {
                    Debug.LogWarning($"BombController not found on {newCharacter.name}");
                }

                Debug.Log($"Spawned {newCharacter.name} at {spawnPositions[i]}");
            }
        }
    }

    public void CheckWinState()
    {
        int aliveCount = 0;
        GameObject lastAlivePlayer = null;

        // Count alive players and store the last one alive
        foreach (GameObject player in players)
        {
            if (player.activeSelf)
            {
                aliveCount++;
                lastAlivePlayer = player;
            }
        }

        // If only one player remains, they win
        if (aliveCount == 1 && lastAlivePlayer != null)
        {
            // Increase score for the winning player
            CharacterManager.Instance.UpdateScore(lastAlivePlayer, 1);
            Debug.Log($"Player {lastAlivePlayer.name} wins! Score updated.");

            // Go back to the selection scene after a delay
            Invoke(nameof(ReturnToSelectionScene), 3f);
        }
        else if (aliveCount == 0) // If no players are left, restart the round
        {
            Invoke(nameof(ReturnToSelectionScene), 3f);
        }
    }

    private void ReturnToSelectionScene()
    {
        SceneManager.LoadScene("StartScene"); // Replace with your actual scene name
    }
}
