using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject[] players;

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
