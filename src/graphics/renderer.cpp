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

void Rendering::Renderer::update(Engine::Scene scene){
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
        for (Engine::GameObject* gameObj : scene.getObjs()){
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
        case SDL_KEYDOWN:
            keybuffer.push_back(e.key.keysym.sym);
            if(keybuffer.size() > 50){
                keybuffer.clear();
            }
            break;
    }


    // SDL_UpdateWindowSurface(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);   
    SDL_RenderClear(renderer);
    for (Engine::GameObject* gameObj : scene.getObjs()){
        gameObj->update();
        gameObj->draw(renderer);
    }
    SDL_RenderPresent(renderer);
#endif
}

float Rendering::Renderer::getDeltaTime(){
    float time = 0.0f;
#if USE_SFML 
    time = clock.getElapsedTime().asSeconds();
#endif
#if USE_SDL

#endif
    return time;
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

Rendering::Renderer::~Renderer(){
    std::cout << "Mosaic Engine Renderer exiting\n";
}


SDL_Renderer* Rendering::Renderer::getRenderer(){
    return renderer;
}