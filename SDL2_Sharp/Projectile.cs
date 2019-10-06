using SDL2;

namespace SDL2_Sharp
{
    internal class Projectile
    {
        internal RenderConfig ProjectileRenderConfig;
        internal SDL.SDL_Rect CollisionBox;
        private float speed = 0.0f;

        internal Projectile(int width, int height, int projectileXPos,
            int projectileYPos, float speed)
        {
            CollisionBox.x = projectileXPos + width / 4;
            CollisionBox.y = projectileYPos;
            CollisionBox.h = height;
            CollisionBox.w = width / 2;

            ProjectileRenderConfig.XPos = projectileXPos;
            ProjectileRenderConfig.YPos = projectileYPos;
            ProjectileRenderConfig.ScaleX = Helper.SCALE_SIZE;
            ProjectileRenderConfig.ScaleY = Helper.SCALE_SIZE;

            this.speed = speed;
        }

        internal void Update()
        {
            ProjectileRenderConfig.XPos += (int)speed;
            CollisionBox.x += (int)speed;
        }

        internal SDL.SDL_bool CheckCollision(ref SDL.SDL_Rect other)
        {
            return SDL.SDL_HasIntersection(ref CollisionBox, ref other);
        }
    }
}
