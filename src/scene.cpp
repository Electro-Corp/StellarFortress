/*
*/
#include <scene.h>

Engine::Scene::Scene(std::string name){
    this->name = name;
}

void Engine::Scene::addObject(Engine::GameObject* object){
    this->gameObjects.emplace_back(object);
}

std::vector<Engine::GameObject*> Engine::Scene::getObjs(){
    return gameObjects;
}