/*
*/
#include <gameobject.h>

Engine::GameObject::GameObject(){
    
}
Engine::GameObject::GameObject(Transform::Transform transform){
    this->transform = transform;
}
Engine::GameObject::GameObject(std::string texLoc){
    this->sprite = new Rendering::Sprite(texLoc);
    this->drawable = true;
}

Transform::Vector2 Engine::GameObject::getPos(){
    return transform.position;
}

Rendering::Sprite* Engine::GameObject::getSprite(){
    return sprite;
}

void Engine::GameObject::updateTransform(){
    if(drawable){
        #if USE_SFML
        // Set position based on Transform
        this->sprite->getSprite()->setPosition(
            sf::Vector2f(
                this->transform.position.x,
                this->transform.position.y
            )
        );
        // Set angle based on Transform 
        this->sprite->getSprite()->setRotation(
            this->getRotation()
        );
        // Set scale
        this->sprite->getSprite()->setScale(
            sf::Vector2f(
                this->transform.scale.x,
                this->transform.scale.y
            )
        );
        #endif
        #if USE_SDL
        texture_rect.x = this->transform.position.x; 
        texture_rect.y = this->transform.position.y;
        texture_rect.w = this->transform.scale.x;
        texture_rect.h = this->transform.scale.y;
        #endif
    }
}
#if USE_SFML
void Engine::GameObject::draw(sf::RenderWindow* window){
    if(drawable){
        window->draw(*(this->getSprite()->getSprite()));
    }
}
#endif

#if USE_SDL
void Engine::GameObject::draw(SDL_Renderer* renderer){
    if(drawable){
        // Massive optimization
        if(this->getSprite()->SD_texture == nullptr){
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, this->getSprite()->getSurface());
            if(!tex){
                printf("Failed to create texture from surface!\n");
                std::cout << SDL_GetError() << "\n";
                exit(-1);
            }
            this->getSprite()->SD_texture = tex;
        }
        // Micro optimization (not even sure if this is even necessary)
        if(this->transform.angle == 0) {
            // If the angle is 0, we can just draw the texture directly
            SDL_RenderCopy(renderer, this->getSprite()->SD_texture, NULL, &texture_rect); 
        }else{
            // Otherwise, we need to rotate the texture
            SDL_RenderCopyEx(renderer, this->getSprite()->SD_texture, NULL, &texture_rect, this->transform.angle, NULL, SDL_FLIP_NONE);
        }
    }
}
#endif

void Engine::GameObject::updateScript(){
    if(this->script){
        this->script->update(this);
    }
}

float Engine::GameObject::getRotation(){
    return transform.angle;
}

void Engine::GameObject::update(){
    updateTransform();
    updateScript();
}
