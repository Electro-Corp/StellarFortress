/*
*/
#include <game.h>

Game::SF::SF(){
    this->renderer = new Rendering::Renderer(std::string("Stellar Fortress"), 800, 600, this);
    scriptMan = new Scripting::ScriptManager("../assets/scripts", renderer);

    #ifdef __linux__
    signal(SIGINT, endGame);
    signal(SIGSEGV, segFault);
    signal(SIGABRT, endGame);
    signal(SIGKILL, endGame);
    #endif
    
    std::cout << "STELLAR FORTRESS\n";
}

/**
 * Load script for a gameObject
*/
void Game::SF::loadScript(Engine::GameObject* obj, std::string path){
    this->scriptMan->loadScriptForObject(obj, path);
}

void Game::SF::initScripts(){
    this->scriptMan->initScripts();
}

void Game::SF::tick(Engine::Scene scene){
    this->renderer->update(scene);
}

float Game::SF::getTime(){
    return this->renderer->getDeltaTime();
}

void Game::SF::changeWindowTitle(std::string title){
    this->renderer->changeTitle(title);
}

lua_State* Game::SF::getLuaState(){
    return scriptMan->getLuaState();
}

void Game::SF::endGame(){
    // Confirm
    // Exit
    // Print bye bye
    std::cout << "Exiting Stellar Fortress. Loser.\n";
    exit(1);
}

void Game::SF::segFault(){
    std::cout << "Segmentation fault! Game Exited.\n";
    exit(1);
}