/*
*/
#pragma once
#include <SDL2/SDL_ttf.h>

#include <rgb.h>
#include <gameobject.h>

namespace UI{

    class Text : public Engine::GameObject {
    private:
        sf::Font font;
        sf::Text text;

        TTF_Font* SD_font = NULL;
        SDL_Texture* texture;

    public:
        RGB rgb;
        std::string caption;
    
        Text(std::string caption);
        Text(std::string caption, int rgb);

        void setText(std::string caption);
        void setSize(int size);

        void update() override;

#if USE_SFML
        void draw(sf::RenderWindow* window) override;
#endif
#if USE_SDL
        void draw(SDL_Renderer* window) override;
#endif

    };

}