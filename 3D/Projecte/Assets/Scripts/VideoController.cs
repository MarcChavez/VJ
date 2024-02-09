using UnityEngine;
using UnityEngine.Video;

public class VideoController : MonoBehaviour
{
    public string videoPath = "Videos/[Wallpaper Engine] Harry Potter - Hogwarts Legacy Deluxe Edition - Dark arts version.mp4"; //
    private VideoPlayer videoPlayer;

    private void Start()
    {
        videoPlayer = gameObject.AddComponent<VideoPlayer>();

        // Establece la ruta del video
        videoPlayer.url = Application.streamingAssetsPath + "/" + videoPath;

        // Reproduce el video en bucle
        videoPlayer.isLooping = true;

        // Establece el volumen del video
        videoPlayer.SetDirectAudioVolume(0, 0.25f);

        // Reproduce el video
        videoPlayer.Play();
    }
}
