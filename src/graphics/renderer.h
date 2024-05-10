/*
    Rendering 
*/
#pragma once

#define USE_SFML 0
#define USE_SDL 1

#include <SFML/Graphics.hpp>
#include <SDL2/SDL.h>
#include <iostream>

#include <scene.h>
#include <game.h>



namespace Engine{
    class Scene;
}
namespace Game{
    class SF;
}
namespace Rendering{

    // Layer to render on
    enum RenderLayers{
        BACKGROUND = 0,
        MIDGROUND = 1,
        FOREGROUND = 2,
        UI = 3
    };

    class Renderer{
        private:
#if USE_SFML
            sf::RenderWindow* window;
            sf::View currentView;
            sf::Clock clock;
#endif

#if USE_SDL
            SDL_Window* window;
            SDL_Surface* surface;
            SDL_Renderer *renderer;
#endif
            // Game Instance
            Game::SF* game;
        public:
            float mouseX, mouseY, mouseDelta, zoom;
            bool mouseDown;
            

            Renderer(std::string title, int width, int height, Game::SF* game);

            Renderer();

            // Update the render view based on the current scene
            void update(Engine::Scene scene);

            void moveView(float x, float y);
            
            void setView(float x, float y);

            void zoomView(float delta);

            void rotateView(float delta);

            void changeTitle(std::string);

            Transform::Vector2 getWindowSize();

            Transform::Vector2 getViewPos();


            float getDeltaTime();

            SDL_Renderer* getRenderer();

            ~Renderer();
    };

    // Global renderer (bad programming practice prob but whatever)
    static Renderer renderer;
}

