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
        public:
            /********
                SCENE LIST
            ********/
            std::unique_ptr<Engine::Scene> mainMenu;

            // End Scene List
            
            SF();
    
            void loadScript(Engine::GameObject* object, std::string path);
    
            void tick(Engine::Scene);

            void tick();
    
            void changeWindowTitle(std::string);
    
            void initScripts();
    
            float getTime();
    
            float getDelta();
    
            lua_State* getLuaState();
    

            void mainMenuLoop();
        
        
            static void endGame();
    
            static void segFault();
    };
}