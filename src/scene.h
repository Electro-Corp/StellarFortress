/*
    A scene

*/
#pragma once
#include <vector>


#include <utils/jsonReader.h>
#include <game.h>
#include <gameobject.h>


namespace Game{
    class SF;
}

namespace Engine{

    class Scene{
        private:    
            std::string name, json;

            std::vector<Engine::GameObject*> gameObjects;
        public:
            Scene(std::string name);

            Scene(std::string name, std::string sceneJson);

            // Actually load in the scene
            void load(Game::SF* game);
    
    
            // Add object into current scene
            void addObject(Engine::GameObject* object);

            // Get all objects in scene
            std::vector<Engine::GameObject*> getObjs();
    };
}

// namespace UI{
//     class Text : public Engine::GameObject {
    
//     };
// }