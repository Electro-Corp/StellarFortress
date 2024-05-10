/*
    A scene

    in the future use Boost::Serilization 
*/
#pragma once
#include <vector>
#include <gameobject.h>
namespace Engine{
    class GameObject;

    class Scene{
        private:    
            std::string name;

            std::vector<Engine::GameObject*> gameObjects;
        public:
            Scene(std::string name);

            // Add object into current scene
            void addObject(Engine::GameObject* object);

            // Get all objects in scene
            std::vector<Engine::GameObject*> getObjs();
    };
}