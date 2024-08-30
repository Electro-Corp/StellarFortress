/*
*/
#include <graphics/renderer.h>

Rendering::Renderer::Renderer(std::string title, int width, int height, Game::SF* game){
#if USE_SFML
    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    this->currentView = window->getDefaultView();
#endif
#if USE_SDL
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    // Disable the cursor by default
    SDL_ShowCursor(SDL_DISABLE);
#endif
    this->game = game;
    zoom = 1.0f;
}

Rendering::Renderer::Renderer(){
    
}

void Rendering::Renderer::update(Engine::Scene* scene){
#if USE_SFML
    if(window->isOpen()){
        // Handle input
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::Resized) {
                currentView.setSize({
                        static_cast<float>(event.size.width),
                        static_cast<float>(event.size.height)
                });
            } else if (event.type == sf::Event::MouseWheelMoved){
                mouseDelta = event.mouseWheel.delta;
            }
        }

        this->mouseX = sf::Mouse::getPosition(*window).x;
        this->mouseY = sf::Mouse::getPosition(*window).y;
      
        this->mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        

        window->setView(currentView);

        // Clear Display    
        window->clear();
        // Draw
        for (Engine::GameObject* gameObj : scene->getObjs()){
            gameObj->update();
            gameObj->draw(window);
        }
        // Display
        window->display();
    }else{
        // End the game
        game->endGame();
    }
#endif
#if USE_SDL
    char key = NULL;
    // Poll input
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
        case SDL_WINDOWEVENT:
          switch (e.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                game->endGame();
                break;
        
            default:
                break;
          }
          break;
        case SDL_MOUSEMOTION:
          SDL_GetMouseState(&this->mouseX, &this->mouseY);
          break;
        case SDL_MOUSEBUTTONDOWN:
          switch (e.button.button){
            case SDL_BUTTON_LEFT:
              // Switch context
              for (Engine::GameObject* gameObj : scene->getObjs()){
                  if(gameObj->transform.position.x <= this->mouseX && 
                      gameObj->transform.position.x + gameObj->transform.scale.x >= this->mouseX &&
                        gameObj->transform.position.y <= this->mouseY && 
                          gameObj->transform.position.y + gameObj->transform.scale.y >= this->mouseY){
                            //printf("found a dude %f\n", gameObj->transform.position.x);
                            curContext = gameObj;
                  }
              }
              break;
            default:
              break;
          }
          break;
        case SDL_KEYDOWN:
            key = e.key.keysym.sym;
            for (Engine::GameObject* gameObj : scene->getObjs()){
                if(gameObj->script){
                    gameObj->update();
                    gameObj->script->onKeyPressed(key);
                }

            }
            /*if(curContext->script){
              printf("acutally found a script\n");
              curContext->update();
              curContext->script->onKeyPressed(key);
            }*/
            keybuffer.push_back(e.key.keysym.sym);
            if(keybuffer.size() > 50){
                keybuffer.clear();
            }
            break;
    }

    a = getDeltaTime();
    delta += a - b;
    if (delta > 1000/30.0)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   
        SDL_RenderClear(renderer);
        rendering = true;
        for (Engine::GameObject* gameObj : scene->getObjs()){
            //printf("%s is %d\n", scene->getName().c_str(), scene->loaded);
            if(scene->loaded == true){
                if(gameObj != nullptr){
                    if(!key)
                        gameObj->update();
                    gameObj->draw(renderer);
                }
            }else{
                break;
            }
        }
        rendering = false;
        SDL_RenderPresent(renderer);
        delta = 0;
    }else{
        
    }
    b = getDeltaTime();
    // SDL_UpdateWindowSurface(window);
    
#endif
}

float Rendering::Renderer::getDeltaTime(){
    float time = 0.0f;
#if USE_SFML 
    time = clock.getElapsedTime().asSeconds();
#endif
#if USE_SDL
    time = SDL_GetTicks();
#endif
    return time;
}

float Rendering::Renderer::getDelta(){
    return delta;
}

void Rendering::Renderer::moveView(float x, float y){
#if USE_SFML
    currentView.move(x, y);
#endif
}

void Rendering::Renderer::setView(float x, float y){
#if USE_SFML
    currentView.setCenter(x, y);
#endif
}

void Rendering::Renderer::zoomView(float delta){
#if USE_SFML
    currentView.zoom(delta);
    this->mouseDelta = 0.0f;
    zoom = delta;
#endif
}

void Rendering::Renderer::rotateView(float delta){
#if USE_SFML
    currentView.rotate(delta);
#endif
}
Transform::Vector2 Rendering::Renderer::getWindowSize(){
#if USE_SFML
    return Transform::Vector2(window->getSize().x, window->getSize().y);
#endif
#if USE_SDL
    int w = 0, h = 0;
    SDL_GetWindowSize(window, &w, &h);
    return Transform::Vector2(w, h);
#endif
}

Transform::Vector2 Rendering::Renderer::getViewPos(){
#if USE_SFML
    return Transform::Vector2(currentView.getCenter().x, currentView.getCenter().y);
#endif
}


void Rendering::Renderer::changeTitle(std::string title){
#if USE_SFML
    window->setTitle(title);
#endif
#if USE_SDL
    SDL_SetWindowTitle(window, title.c_str());
#endif
}

void Rendering::Renderer::addCallBackOnKeyPressed(luabridge::LuaRef* funcToCall){
    if(funcToCall != nullptr){
        keyCallBacks.push_back(funcToCall);
    };
}


Rendering::Renderer::~Renderer(){
    std::cout << "Mosaic Engine Renderer exiting\n";
}


SDL_Renderer* Rendering::Renderer::getRenderer(){
    return renderer;
}