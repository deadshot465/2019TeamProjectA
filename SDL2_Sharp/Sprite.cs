using System;
using System.Collections.Generic;

namespace SDL2_Sharp
{
    internal class Sprite : IDisposable
    {
        private List<Image> staticSprites = new List<Image>();
        
        internal Sprite()
        {

        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            foreach (var image in staticSprites)
            {
                image.Dispose();
            }
        }

        internal void LoadStaticSprite(string fileName, IntPtr renderer)
        {
            staticSprites.Add(new Image(fileName, renderer, 0, 0, null, null, null));
        }

        internal void RenderStaticSprite(IntPtr renderer, int index,
            RenderConfig renderConfig, double? angle)
        {
            if (!angle.HasValue)
            {
                staticSprites[index].Render(renderer,
                renderConfig.XPos, renderConfig.YPos,
                renderConfig.ScaleX, renderConfig.ScaleY, null);
            }
            else
            {
                staticSprites[index].Render(renderer,
                renderConfig.XPos, renderConfig.YPos,
                renderConfig.ScaleX, renderConfig.ScaleY, angle.Value);
            }
        }

        internal void RenderStaticSprite(IntPtr renderer,
            CoreSystem.StaticSpriteList spriteListNo, RenderConfig renderConfig,
            double? angle)
        {
            RenderStaticSprite(renderer, (int)spriteListNo, renderConfig, angle);
        }
    }
}
