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
#include <transform.h>

#include <gameobject.h>

namespace Engine{
    class Scene;
    class GameObject;
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
            SDL_Renderer* renderer;
#endif
            // Game Instance
            Game::SF* game;

            unsigned int a = 0;
            unsigned int b = 0;
            double delta = 0;

            Engine::Scene* lScene;

            std::vector<luabridge::LuaRef*> keyCallBacks;

            Engine::GameObject* curContext;
        public:
            #if USE_SFML
            float mouseX, mouseY, mouseDelta, zoom;
            #endif
            #if USE_SDL
            int mouseX, mouseY, mouseDelta, zoom;
            #endif
            bool mouseDown, rendering = false;
            
            std::vector<char> keybuffer;
            

            Renderer(std::string title, int width, int height, Game::SF* game);

            Renderer();

            // Update the render view based on the current scene
            void update(Engine::Scene* scene);

            void moveView(float x, float y);
            
            void setView(float x, float y);

            void zoomView(float delta);

            void rotateView(float delta);

            void changeTitle(std::string);

            Transform::Vector2 getWindowSize();

            Transform::Vector2 getViewPos();


            float getDeltaTime();

            float getDelta();

            SDL_Renderer* getRenderer();

            // Register callback
            void addCallBackOnKeyPressed(luabridge::LuaRef* funcToCall);

            ~Renderer();
    };

    // Global renderer (bad programming practice prob but whatever)
    static Renderer rendererStat;
}

