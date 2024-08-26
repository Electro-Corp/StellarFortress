/*
*/
#include <graphics/sprite.h>

Rendering::Sprite::Sprite(){
    
}

Rendering::Sprite::Sprite(std::string fileName){
    this->fName = fileName;
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
    SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
#endif
}

void Rendering::Sprite::setAlpha(int alpha){
    #if USE_SDL
        // printf("[Rendering::Sprite::setAlpha] Setting alpha to %d\n", alpha);
        if(SDL_SetSurfaceAlphaMod(surface, alpha) < 0){
            printf("[Rendering::Sprite::setAlpha] SDL_SetSurfaceAlphaMod failed with error %s\n", SDL_GetError());
        }
        this->SD_texture = nullptr;
       
    #endif
    #if USE_SFML
        
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
