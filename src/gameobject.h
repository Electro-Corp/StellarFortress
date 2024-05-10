/*
    GameObject, a thing in the world
*/
#pragma once
#include <transform.h>
#include <graphics/sprite.h>
namespace Rendering{
    class Sprite;
}
namespace Scripting{
    class Script;
}
// Gameobject
namespace Engine {
    /**
     * A gameObject 
    */
    class GameObject{
        private:
        protected:
            Rendering::Sprite* sprite;
            SDL_Rect texture_rect;
        public:
            Scripting::Script* script;
            Transform::Transform transform;

            bool drawable;

            GameObject();
            GameObject(Transform::Transform transform);
            GameObject(std::string texLoc);

            // Get position
            Transform::Vector2 getPos();
            // Get rotation
            float getRotation();

            // Return the sprite
            Rendering::Sprite* getSprite();

            virtual void updateScript();
            void updateTransform();

#if USE_SFML
            virtual void draw(sf::RenderWindow* window);
#endif

#if USE_SDL
            virtual void draw(SDL_Renderer* surface);
#endif

            // They derive!
            virtual void update(); 
    };
}