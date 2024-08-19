/*
    Script manager
*/
#pragma once
#include <vector>
#include <iostream>
#include <filesystem>
#include <memory>
#include <fstream>
namespace fs = std::filesystem;

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

// Include things that need to be exposed to Lua
//#include <gameObjects/county.h>
#include <scene.h>
#include <graphics/renderer.h>

namespace Engine{
    class GameObject;
}
namespace Rendering{
    class Renderer;
}
namespace Game{
    class SF;
}
namespace Scripting{
    class Script{
        private:
            luabridge::LuaRef init = nullptr;
            luabridge::LuaRef updateFunc = nullptr;
            luabridge::LuaRef keyPressed = nullptr;

            int keyCallBackReg = 0;

            Engine::GameObject* thisObj;
        public:
            Script(lua_State* L);

            void setGameObj(Engine::GameObject*);

            luabridge::LuaRef getUpdateFunc();

            void update();

            void onKeyPressed(char key);
    };

    class ScriptManager{
        friend Script; 
        private:
            lua_State* m_luaState;
            std::vector<luabridge::LuaRef> initFuncs;
            std::vector<luabridge::LuaRef> updateFuncs;

            std::unique_ptr<Rendering::Renderer> m_renderManGlob;
            std::unique_ptr<Game::SF> m_gameGlob;

        public:
            ScriptManager();
            ScriptManager(std::string p_scriptPath, Rendering::Renderer* renderer, Game::SF* sf);

            void loadScriptForObject(Engine::GameObject* object, std::string path);

            void initScripts();

            // Expose GameObject features to Lua
            void exposeGame();

            // Expose Scene features to Lua
            void exposeScene();

            lua_State* getLuaState();
    };
};