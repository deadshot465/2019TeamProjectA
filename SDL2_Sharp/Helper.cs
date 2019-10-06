using SDL2;
using System;

namespace SDL2_Sharp
{
    public static class Helper
    {
        public static readonly int WINDOW_WIDTH = 960;
        public static readonly int WINDOW_HEIGHT = 540;
        public static readonly float SCALE_SIZE = 1.0f;

        public static void ThrowIfFailed(int result, string message)
        {
            if (result < 0)
            {
                string msg = $"{message}\nError Message: {SDL.SDL_GetError()}\n";
                throw new Exception(msg);
            }
        }

        public static void ThrowIfFailed(string message)
        {
            throw new Exception(message);
        }
    }

    public struct RenderConfig
    {
        public int XPos;
        public int YPos;
        public float ScaleX;
        public float ScaleY;

        public RenderConfig(int xPos, int yPos, float scaleX, float scaleY)
        {
            XPos = xPos;
            YPos = yPos;
            ScaleX = scaleX;
            ScaleY = scaleY;
        }
    }
}
