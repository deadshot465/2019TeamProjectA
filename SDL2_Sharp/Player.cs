using SDL2;
using System;

namespace SDL2_Sharp
{
    internal class Player : IDisposable
    {
        private RenderConfig renderConfig = new RenderConfig();
        private Image sprite;
        internal int Speed { get; set; }
        internal SDL.SDL_Rect CollisionBox;

        internal Player(string fileName, IntPtr renderer, int renderXPos,
            int renderYPos, int initialXPos, int initialYPos)
        {
            sprite = new Image(fileName, renderer, renderXPos, renderYPos, null,
                null, null);

            renderConfig.XPos = initialXPos;
            renderConfig.YPos = initialYPos;
            renderConfig.ScaleX = Helper.SCALE_SIZE;
            renderConfig.ScaleY = Helper.SCALE_SIZE;

            CollisionBox.x = initialXPos;
            CollisionBox.y = initialYPos;
            CollisionBox.w = (int)(sprite.Width * Helper.SCALE_SIZE);
            CollisionBox.h = (int)(sprite.Height * Helper.SCALE_SIZE);
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            sprite.Dispose();
        }

        internal void Render(IntPtr renderer)
        {
            sprite.Render(renderer, renderConfig.XPos, renderConfig.YPos,
                renderConfig.ScaleX, renderConfig.ScaleY, null);
        }
    }
}
