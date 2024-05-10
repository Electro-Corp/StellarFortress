/*
*/
#include <game.h>

Game::SF::SF(){
    //Rendering::rendererStat = Rendering::Renderer(std::string("Stellar Fortress"), 800, 600, this);
    this->renderer = new Rendering::Renderer(std::string("Stellar Fortress"), 800, 600, this);
    scriptMan = new Scripting::ScriptManager("../assets/scripts", renderer);

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