/*
    Manages the game
*/
#pragma once

#include <stdlib.h>
#include <iostream>

#include <scripting/scriptmanager.h>

#ifdef __linux__
#include <signal.h>
#endif

namespace Scripting{
    class ScriptManager;
}
namespace Engine{
    class GameObject;
    class Scene;
}
namespace Rendering{
    class Renderer;
}
namespace Game{
    // Nunticle
    class SF{
        private:
            Scripting::ScriptManager* scriptMan;
            Rendering::Renderer* renderer;

            int tickNum;
        public:
            /********
                SCENE LIST
            ********/
            std::unique_ptr<Engine::Scene> mainMenu;

            std::vector<std::unique_ptr<Engine::Scene>> scenes;

            // End Scene List
            
            SF();
    
            void loadScript(Engine::GameObject* object, std::string path);
    
            void tick(Engine::Scene);

            void tick();

            void tick(int num);
    
            void changeWindowTitle(std::string);
    
            void initScripts();
    
            float getTime();
    
            float getDelta();
    
            lua_State* getLuaState();
    

            void mainMenuLoop();

            void setTickNum(int num);
        
            static void endGame();
    
            static void segFault();
    };
}