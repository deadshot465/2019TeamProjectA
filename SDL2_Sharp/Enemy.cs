using SDL2;
using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace SDL2_Sharp
{
    internal class Enemy : IDisposable
    {
        private Stopwatch attackTimer = new Stopwatch();
        private Stopwatch projectileTimer = new Stopwatch();
        private Stopwatch animationTimer = new Stopwatch();
        private bool animationStarted = false;
        private float attackDuration = 0.0f;

        private Image sprite;
        private Image projectile;

        List<Projectile> projectiles = new List<Projectile>();
        List<RenderConfig> projectileConfigs = new List<RenderConfig>();

        internal Enemy(string fileName, IntPtr renderer, int renderXPos,
            int renderYPos, string projectileFileName, int projectileXPos,
            int projectileYPos)
        {
            attackTimer.Start();
            projectileTimer.Start();
            var random = new Random();
            attackDuration = (float)(random.NextDouble() * 4 + 1);

            sprite = new Image(fileName, renderer, renderXPos, renderYPos, true,
                128, 128);
            projectile = new Image(projectileFileName, renderer, projectileXPos,
                projectileYPos, true, 32, 32);
            projectile.RenderXPos = 32;
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
            sprite.Dispose();
            projectile.Dispose();

            projectiles.Clear();
            projectileConfigs.Clear();
        }

        internal SDL.SDL_bool CheckCollisions(ref SDL.SDL_Rect playerCollisionBox)
        {
            if (projectiles.Count <= 0) return SDL.SDL_bool.SDL_FALSE;

            foreach (var _projectile in projectiles)
            {
                var result = _projectile.CheckCollision(ref playerCollisionBox);

                if (result == SDL.SDL_bool.SDL_TRUE)
                {
                    projectiles.Remove(_projectile);
                    return result;
                }
            }

            return SDL.SDL_bool.SDL_FALSE;
        }

        internal void Update(IntPtr renderer, RenderConfig renderConfig)
        {
            var elapsed = attackTimer.Elapsed.TotalSeconds;

            if (elapsed > attackDuration && !animationStarted)
            {
                animationStarted = true;
                animationTimer.Restart();
                sprite.RenderXPos = sprite.Width;

                projectiles.Add(new Projectile(projectile.Width, projectile.Height,
                    renderConfig.XPos, renderConfig.YPos + (Helper.WINDOW_HEIGHT / 2), -25));
                attackTimer.Restart();

                var random = new Random();
                attackDuration = (float)(random.NextDouble() * 4 + 1);
            }

            var animationElapsed = animationTimer.Elapsed.TotalSeconds;

            if (animationStarted && animationElapsed > 2.0)
            {
                animationStarted = false;
                sprite.RenderXPos = 0;
            }

            UpdateProjectiles();

            foreach (var _projectile in projectiles)
            {
                projectile.Render(renderer, _projectile.ProjectileRenderConfig.XPos,
                    _projectile.ProjectileRenderConfig.YPos,
                    _projectile.ProjectileRenderConfig.ScaleX,
                    _projectile.ProjectileRenderConfig.ScaleY, null);

                SDL.SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL.SDL_RenderDrawRect(renderer, ref _projectile.CollisionBox);
            }

            sprite.Render(renderer, renderConfig.XPos, renderConfig.YPos,
                renderConfig.ScaleX, renderConfig.ScaleY, null);
        }

        private void UpdateProjectiles()
        {
            var elapsed = projectileTimer.Elapsed.TotalSeconds;

            if (elapsed > 0.25)
            {
                foreach (var _projectile in projectiles)
                {
                    if (_projectile.ProjectileRenderConfig.XPos < -100)
                    {
                        projectiles.Remove(_projectile);
                        continue;
                    }

                    _projectile.Update();
                }
                projectileTimer.Restart();
            }
        }
    }
}
