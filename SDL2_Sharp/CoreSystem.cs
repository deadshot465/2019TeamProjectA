using SDL2;
using System;
using System.Diagnostics;

namespace SDL2_Sharp
{
    internal class CoreSystem : IDisposable
    {
        private IntPtr renderer;
        private RenderConfig backgroundPosition1 =
            new RenderConfig(0, Helper.WINDOW_HEIGHT - 128, Helper.SCALE_SIZE, Helper.SCALE_SIZE);
        private RenderConfig backgroundPosition2 =
            new RenderConfig(Helper.WINDOW_WIDTH * 2, Helper.WINDOW_HEIGHT - 128,
                Helper.SCALE_SIZE, Helper.SCALE_SIZE);
        private int backgroundMoveSpeed = Helper.WINDOW_WIDTH / 10;
        private SDL.SDL_Rect viewport = new SDL.SDL_Rect();
        private Sprite sprites = new Sprite();
        private Enemy enemy;
        private Player player;
        
        private static Stopwatch timer = new Stopwatch();
        private static Stopwatch backgroundTimer = new Stopwatch();
        private static double angle = 6.0;
        private static double gameTime = 0.0;

        internal enum StaticSpriteList
        {
            Background,
            Clock,
            Indicator,
            Floor
        }

        internal CoreSystem(IntPtr handle, SDL.SDL_Rect viewport)
        {
            Helper.ThrowIfFailed(SDL_image
                .IMG_Init(SDL_image.IMG_InitFlags.IMG_INIT_PNG |
                SDL_image.IMG_InitFlags.IMG_INIT_JPG),
                "SDL failed to initialize SDL_image.\n");

            renderer = SDL.SDL_CreateRenderer(handle, -1,
                SDL.SDL_RendererFlags.SDL_RENDERER_ACCELERATED);

            sprites.LoadStaticSprite("texture/background_resized.png", renderer);
            sprites.LoadStaticSprite("texture/sample_clock.png", renderer);
            sprites.LoadStaticSprite("texture/sample_indicator.png", renderer);
            sprites.LoadStaticSprite("texture/floor.png", renderer);

            enemy = new Enemy("texture/boss1.png", renderer, 0, 0,
                "texture/bullet.png", 0, 0);

            player = new Player("texture/sample_player.png", renderer, 0, 0, 64,
                (int)(Helper.WINDOW_HEIGHT * 0.75f));

            this.viewport = viewport;

            timer.Start();
            backgroundTimer.Start();
        }

        internal void ClearColor(byte r, byte g, byte b, byte a = 0xFF)
        {
            if (renderer == IntPtr.Zero)
            {
                Helper.ThrowIfFailed("Renderer is not created.\n");
            }

            Helper.ThrowIfFailed(SDL.SDL_SetRenderDrawColor(renderer, r, g, b, a),
                "SDL failed to set the render draw color.\n");

            Helper.ThrowIfFailed(SDL.SDL_RenderClear(renderer),
                "SDL failed to clear the renderer.\n");
        }

        internal unsafe void Render()
        {
            var elapsed = timer.Elapsed.TotalSeconds;

            try
            {
                sprites.RenderStaticSprite(renderer, StaticSpriteList.Background,
                    new RenderConfig(0, 0, Helper.SCALE_SIZE, Helper.SCALE_SIZE), null);

                sprites.RenderStaticSprite(renderer, StaticSpriteList.Floor,
                    backgroundPosition1, null);
                sprites.RenderStaticSprite(renderer, StaticSpriteList.Floor,
                    backgroundPosition2, null);

                sprites.RenderStaticSprite(renderer, StaticSpriteList.Clock,
                    new RenderConfig(64, (int)(Helper.WINDOW_WIDTH * 0.05f), 1.0f, 1.0f),
                    null);

                if (elapsed > 1.0)
                {
                    angle += 6.0;
                    timer.Restart();
                    gameTime += elapsed;
                }

                sprites.RenderStaticSprite(renderer, StaticSpriteList.Indicator,
                    new RenderConfig(64, (int)(Helper.WINDOW_WIDTH * 0.05f), 1.0f, 1.0f),
                    angle);

                enemy.Update(renderer,
                    new RenderConfig((int)(viewport.w * 0.6f),
                    (int)(viewport.h * 0.25f), Helper.SCALE_SIZE, Helper.SCALE_SIZE));

                UpdatePlayer();
                UpdateBackground();

                player.Render(renderer);

                SDL.SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL.SDL_RenderDrawRect(renderer, ref player.CollisionBox);
                SDL.SDL_RenderPresent(renderer);

            }
            catch (Exception)
            {
                throw;
            }
        }

        private unsafe void UpdatePlayer()
        {
            var keyStates = (byte*)SDL.SDL_GetKeyboardState(out int numKeys);
            var result = enemy.CheckCollisions(ref player.CollisionBox);

            if (keyStates[(int)SDL.SDL_Scancode.SDL_SCANCODE_SPACE] > 0)
            {
                if (result == SDL.SDL_bool.SDL_TRUE)
                {
                    backgroundMoveSpeed *= 1;
                }
                else
                {
                    backgroundMoveSpeed = 0;
                }
            }
            else
            {
                backgroundMoveSpeed = (int)(Helper.WINDOW_WIDTH / 10) * 1;
            }
        }

        private void UpdateBackground()
        {
            var elapsed = backgroundTimer.Elapsed.TotalSeconds;

            if (elapsed > 1.0)
            {
                backgroundPosition1.XPos -= backgroundMoveSpeed;
                backgroundPosition2.XPos -= backgroundMoveSpeed;
                backgroundTimer.Restart();
            }

            if (backgroundPosition1.XPos <= -(Helper.WINDOW_WIDTH * 2))
                backgroundPosition1.XPos = Helper.WINDOW_WIDTH;
            if (backgroundPosition2.XPos <= -(Helper.WINDOW_WIDTH * 2))
                backgroundPosition2.XPos = Helper.WINDOW_WIDTH;
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            sprites.Dispose();
            enemy.Dispose();
            player.Dispose();
            SDL_image.IMG_Quit();
            SDL.SDL_DestroyRenderer(renderer);
        }
    }
}
