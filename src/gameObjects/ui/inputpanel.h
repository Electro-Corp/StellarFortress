/*
*/
#pragma once
#include <SDL2/SDL_ttf.h>

#include <rgb.h>
#include <gameobject.h>
#include <gameObjects/ui/text.h>

namespace UI{

    class Panel : public Engine::GameObject {
    private:
       

    public:
        UI::Text* question;
        UI::Text* input;
        RGB rgb;

        Panel(std::string question, int rgb);

        void initScript() override;
        void update() override;

#if USE_SFML
        void draw(sf::RenderWindow* window) override;
#endif
#if USE_SDL
        void draw(SDL_Renderer* window) override;
#endif

    };

}