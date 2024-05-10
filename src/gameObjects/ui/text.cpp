#include <gameObjects/ui/text.h>

UI::Text::Text(std::string caption){
    drawable = false;
#if USE_SFML
    if(!font.loadFromFile("../assets/fonts/playball.ttf")){

    }
    text.setFont(font);
    text.setString(caption);
    text.setFillColor(sf::Color::White);
#endif

}

void UI::Text::setText(std::string caption){
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
    // run scripts
    updateScript();
}
#if USE_SFML
void UI::Text::draw(sf::RenderWindow* window){
    window->draw(text);
}
#endif

#if USE_SDL
void UI::Text::draw(SDL_Renderer* window){

}
#endif