/*
*/
#include <game.h>

static int segfaults = 0;

Game::SF::SF(){
    this->renderer = new Rendering::Renderer(std::string("Stellar Fortress"), 800, 600, this);
    scriptMan = new Scripting::ScriptManager("../assets/scripts", renderer, this);

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

void Game::SF::tick(Engine::Scene* scene){
    this->renderer->update(scene);
}

float Game::SF::getTime(){
    return this->renderer->getDeltaTime();
}

float Game::SF::getDelta(){
    return this->renderer->getDelta();
}

void Game::SF::changeWindowTitle(std::string title){
    this->renderer->changeTitle(title);
}

lua_State* Game::SF::getLuaState(){
    return scriptMan->getLuaState();
}

void Game::SF::mainMenuLoop(){
    //tick(mainMenu);
}

void Game::SF::tick(){
    // TODO: SWITCH STATMENT
    //this->renderer->update(*mainMenu);
    if(scenes[tickNum]->loaded)
        this->renderer->update((scenes[tickNum]).get());
}

void Game::SF::setTickNum(int num){
    if(tickNum != -1){
        printf("Deload scene %d\n", tickNum);
        //while(this->renderer->rendering){}
        scenes[tickNum]->deload();
    }
    this->tickNum = num;
    printf("Load scene %d\n", num);
    scenes[tickNum]->load(this);
}


void Game::SF::endGame(){
    // Confirm
    // Exit
    // Print bye bye
    std::cout << "Cleaning up..\n";
    // clean up
    std::cout << "Exiting Stellar Fortress. Loser.\n";
    exit(1);
}

void Game::SF::segFault(){
    segfaults++;
    if(segfaults < 5){
        std::cout << "Segmentation fault (" << segfaults << ")! Attempting to continue game...\n";
    }else{
        std::cout << "Too many segfaults! Clearly this situation is unrecoverable. Exiting game.\n";
        endGame();
    }
}