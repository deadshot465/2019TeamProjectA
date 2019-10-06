using SDL2;
using System;

namespace SDL2_Sharp
{
    internal class Image : IDisposable
    {
        private IntPtr texture;
        internal int RenderXPos { get; set; }
        internal int RenderYPos { get; set; }
        internal int Width { get; private set; }
        internal int Height { get; private set; }

        private static readonly byte TRANSPARENT_R = 250;
        private static readonly byte TRANSPARENT_G = 125;
        private static readonly byte TRANSPARENT_B = 250;

        internal unsafe Image(string fileName, IntPtr renderer, int renderXPos,
            int renderYPos, bool? isAnimation, int? frameWidth, int? frameHeight)
        {
            var surface = SDL_image.IMG_Load(fileName);

            Helper.ThrowIfFailed(SDL.SDL_SetColorKey(surface,
                Convert.ToInt32(true),
                SDL.SDL_MapRGBA(((SDL.SDL_Surface*)surface)->format, TRANSPARENT_R,
                TRANSPARENT_G, TRANSPARENT_B, 0xFF)),
                "SDL failed to set the color key.\n");

            texture = SDL.SDL_CreateTextureFromSurface(renderer, surface);
            RenderXPos = renderXPos;
            RenderYPos = renderYPos;

            if (!isAnimation.HasValue)
            {
                Width = ((SDL.SDL_Surface*)surface)->w;
                Height = ((SDL.SDL_Surface*)surface)->h;
            }
            else
            {
                if (!frameWidth.HasValue || !frameHeight.HasValue)
                {
                    Helper
                        .ThrowIfFailed("Frame width and frame height cannot be zero while the sprite is an animation.\n");
                }
                Width = frameWidth.Value;
                Height = frameHeight.Value;
            }

            SDL.SDL_FreeSurface(surface);
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            SDL.SDL_DestroyTexture(texture);
        }

        public void Render(IntPtr renderer, int dstXPos, int dstYPos,
            float scaleX, float scaleY, double? angle)
        {
            var srcRect = new SDL.SDL_Rect
            {
                x = RenderXPos,
                y = RenderYPos,
                w = Width,
                h = Height
            };

            var dstRect = new SDL.SDL_Rect
            {
                x = dstXPos,
                y = dstYPos,
                w = (int)(Width * scaleX),
                h = (int)(Height * scaleY)
            };

            var point = new SDL.SDL_Point
            {
                x = dstRect.w / 2,
                y = dstRect.h / 2
            };

            if (angle.HasValue)
            {
                SDL.SDL_RenderCopyEx(renderer, texture,
                    ref srcRect, ref dstRect, angle.Value, ref point,
                    SDL.SDL_RendererFlip.SDL_FLIP_NONE);
            }
            else
            {
                SDL.SDL_RenderCopy(renderer, texture, ref srcRect, ref dstRect);
            }
        }
    }
}
