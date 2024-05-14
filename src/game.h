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
        SF();

        void loadScript(Engine::GameObject* object, std::string path);

        void tick(Engine::Scene);

        void changeWindowTitle(std::string);

        void initScripts();

        float getTime();

        lua_State* getLuaState();

        
    
        static void endGame();

        static void segFault();
    };
}