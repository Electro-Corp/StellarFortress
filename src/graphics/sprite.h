/*
    Sprite
*/
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <graphics/renderer.h>

namespace Rendering{
    class Sprite{
        private:
        #if USE_SFML
            sf::Texture texture;
            sf::Sprite sprite;
        #endif
        #if USE_SDL            
            SDL_Surface* surface;
            SDL_Texture* texture;
        #endif

            int renderLayer;
        public:
            Sprite();
            Sprite(std::string fileName);

        #if USE_SFML
            // Return the SFML sprite
            sf::Sprite* getSprite();
        #endif

        #if USE_SDL
            // Return the SDL surface
            SDL_Surface* getSurface();

            // Return the SDL texture
            SDL_Texture* getTexture();
        #endif
    };
}