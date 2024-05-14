#include <gameObjects/ui/text.h>

UI::Text::Text(std::string caption){
    drawable = false;
    this->caption = caption;
#if USE_SFML
    if(!font.loadFromFile("../assets/fonts/protest.ttf")){

    }
    text.setFont(font);
    text.setString(caption);
    text.setFillColor(sf::Color::White);
#endif
#if USE_SDL
    TTF_Init();
    // Load fonts
    SD_font = TTF_OpenFont("../assets/fonts/protest.ttf", 80);
    if(!SD_font){
        printf("Error loading default font! %s\n", TTF_GetError());
        exit(-1);
    }
#endif
}

void UI::Text::setText(std::string caption){
    this->caption = caption;
#if USE_SFML
    text.setString(caption);
#endif
}

void UI::Text::setSize(int size){
#if USE_SFML
    text.setCharacterSize(size);
#endif
}

void UI::Text::update(){
#if USE_SFML
    // Update text transformation
    this->text.setPosition(
        sf::Vector2f(
            this->transform.position.x,
            this->transform.position.y
        )
    );
    this->text.setScale(
        sf::Vector2f(
            this->transform.scale.x,
            this->transform.scale.y
        )
    );
    this->text.setRotation(
        this->transform.angle
    );
#endif
#if USE_SDL
    texture_rect.x = this->transform.position.x; 
    texture_rect.y = this->transform.position.y;
    texture_rect.w = this->transform.scale.x;
    texture_rect.h = this->transform.scale.y;
#endif
    // run scripts
    updateScript();
}
#if USE_SFML
void UI::Text::draw(sf::RenderWindow* window){
    window->draw(text);
}
#endif

#if USE_SDL
void UI::Text::draw(SDL_Renderer* render){
    SDL_Surface* surface = TTF_RenderText_Solid(SD_font, this->caption.c_str(), {rgb.r, rgb.g, rgb.b, rgb.a});
    texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(render, texture, NULL, &texture_rect);
}
#endif