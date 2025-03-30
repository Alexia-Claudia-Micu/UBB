using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PlayButton : MonoBehaviour
{
    public static PlayButton Instance { get; private set; }
    private Button playButton;

    private void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
        }
        playButton = GetComponent<Button>();
        UpdatePlayButton();
    }

    public void UpdatePlayButton()
    {
        playButton.interactable = CharacterManager.CanProceed();
    }

    public void StartGame()
    {
        if (CharacterManager.CanProceed())
        {
            SceneManager.LoadScene("Bomberman"); // Replace with your actual scene name
        }
    }
}
