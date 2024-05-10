/*
*/
#include <graphics/sprite.h>

Rendering::Sprite::Sprite(){
    
}

Rendering::Sprite::Sprite(std::string fileName){
#if USE_SFML
    // Load texture
    if(!texture.loadFromFile(fileName)){
        // Error, for now just print it
        printf("Failed to load texture %s\n", fileName.c_str());
        exit(-1);
    }
    // Smooth out the texture
    texture.setSmooth(true);

    sprite.setTexture(texture);

    sprite.setOrigin(
        (sf::Vector2f)texture.getSize() / 2.f
    );
#endif
#if USE_SDL
    surface = IMG_Load(fileName.c_str());
    if(!surface){
        std::cout << fileName.c_str() << " failed to load as a sprite.\n";
    }
#endif
}


#if USE_SFML
sf::Sprite* Rendering::Sprite::getSprite(){
    return &(this->sprite);
}
#endif

SDL_Surface* Rendering::Sprite::getSurface(){
    return surface;
}
