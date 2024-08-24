/*
    GameObject, a thing in the world
*/
#pragma once
#include <transform.h>
/*#include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
*/
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
            Scripting::Script* script = nullptr;
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

            virtual void initScript();
            virtual void updateScript();
            
            void updateTransform();
            void setTex(std::string);

#if USE_SFML
            virtual void draw(sf::RenderWindow* window);
#endif

#if USE_SDL
            virtual void draw(SDL_Renderer* renderer);
#endif

            // They derive!
            virtual void update(); 
    };
}


