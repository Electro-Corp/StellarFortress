/*
*/
#include <scripting/scriptmanager.h>

#include <gameObjects/ui/text.h>
#include <gameObjects/ui/inputpanel.h>

Scripting::Script::Script(lua_State* L, std::string path){
    std::cout << "Loading funcs in \"" << path << "\"\n";

    //this->luaState = (lua_State*)malloc(sizeof(lua_State*));
    //memcpy(this->luaState, L, sizeof(lua_State*));

    assert(L != NULL);
    assert(luaState == NULL);
    
    this->luaState = L;

    assert(luaState != NULL);

    assert(luabridge::getGlobal(L, "init").isNil() != true);
    assert(luabridge::getGlobal(L, "update").isNil() != true);
    updateFunc = (luabridge::getGlobal(luaState, "update")); 
    init = (luabridge::getGlobal(luaState, "init"));

    if(luabridge::getGlobal(luaState, "onKeyPressed").isNil()){
        printf("[ScriptManager] \"%s\" does not have a global function 'onKeyPressed'. Assuming you didn't want a key callback.\n", path.c_str());
    }else{
        printf("[ScriptManger] Found onKeyPressed for %s\n", path.c_str());
        keyPressed = luabridge::getGlobal(luaState, "onKeyPressed");
        keyCallBackReg = 1;
    }
}    

void Scripting::Script::setGameObj(Engine::GameObject* obj){
    this->thisObj = obj;
    
}

luabridge::LuaRef Scripting::Script::getUpdateFunc(){
    return updateFunc;
}

// template <typename T>
// void Scripting::Script::update(T* cast){
//     updateFunc((T*)thisObj);
// }

void Scripting::Script::onKeyPressed(char key){
    if(keyCallBackReg == 1){
        keyPressed(thisObj, key);
    }else{
    }
}

Scripting::ScriptManager::ScriptManager(){
    
}

Scripting::ScriptManager::ScriptManager(std::string p_scriptPath, Rendering::Renderer* renderer, Game::SF* game) {   
    // Create Lua state             
    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);

    m_renderManGlob = std::unique_ptr<Rendering::Renderer>(renderer);
    m_gameGlob = std::unique_ptr<Game::SF>(game);

    
}

void Scripting::ScriptManager::initScripts(){
    for(auto& script : initFuncs){
        script();
    }
}

void Scripting::ScriptManager::loadScriptForObject(Engine::GameObject* object, std::string path){
    //for (const auto & entry : fs::directory_iterator(path)){
    // Load scripts
    std::ifstream file((char*) path.c_str());
    // Create new Lua state
    lua_State* tmp = nullptr;
    tmp = luaL_newstate();
    luaL_openlibs(tmp);
    exposeGame(tmp);


    int scriptLoadStatus = luaL_dofile(tmp, path.c_str());


    
    if (scriptLoadStatus != 0) {
        std::cout << "[ScriptManager] Lua script load error in file \"" << path << "\" for object " << object << std::endl;
        std::cout << lua_tostring(tmp, -1) << std::endl;
        lua_pop(tmp, 1);
    }

    
    object->script = new Script(tmp, path);
    object->script->setGameObj(object);
    
    luaStates.push_back(tmp);


        //updateFuncs.push_back(luabridge::getGlobal(luaState, "update"));
        //initFuncs.push_back(luabridge::getGlobal(luaState, "init"));
        
    //}
}

void Scripting::ScriptManager::exposeGame(lua_State* state){
    printf("[ScriptManager] Expose Vector2/Transform/GameObject to 0x%u\n", state);
    // Expose Transform
    luabridge::getGlobalNamespace(state)
        .beginClass<Transform::Vector2>("Vector2")
        .addConstructor<void(*) (float, float)>()
        .addProperty("x", &Transform::Vector2::x)
        .addProperty("y", &Transform::Vector2::y)
        .endClass();

    luabridge::getGlobalNamespace(state)
        .beginClass<Transform::Transform>("Transform")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (float, float, float)>()
        .addConstructor<void(*) (Transform::Vector2, float)>()
        .addProperty("position", &Transform::Transform::position)
        .addProperty("angle", &Transform::Transform::angle)
        .addProperty("scale", &Transform::Transform::scale)
        .endClass();

    luabridge::getGlobalNamespace(state)
        .beginClass<Engine::GameObject>("GameObject")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (Transform::Transform)>()
        .addFunction("getSprite", &Engine::GameObject::getSprite)
        .addFunction("setTex", &Engine::GameObject::setTex)
        .addProperty("transform", &Engine::GameObject::transform)
        .endClass()
        .deriveClass<UI::Text, Engine::GameObject>("Text")
        // .addConstructor<void(*) ()>()
        .addConstructor<void(*) (std::string)>()
        // .addProperty("transform", &UI::Text::transform)
        .addProperty("text", &UI::Text::caption)
        .endClass()
        .deriveClass<UI::Panel, Engine::GameObject>("Panel")
        // .addConstructor<void(*) ()>()
        .addConstructor<void(*) (std::string, int)>()
        // .addProperty("transform", &UI::Text::transform)
        .addProperty("question", &UI::Panel::question)
        .addProperty("input", &UI::Panel::input)
        .addProperty("rgb", &UI::Panel::rgb)
        .endClass();
        


   
    luabridge::getGlobalNamespace(state)
        .beginClass<Rendering::Renderer>("Renderer")
        .addConstructor<void(*) (std::string, int, int, Game::SF*)>()
        .addProperty("mouseX", &Rendering::Renderer::mouseX)
        .addProperty("mouseY", &Rendering::Renderer::mouseY)
        .addProperty("mouseDown", &Rendering::Renderer::mouseDown)
        .addProperty("mouseDelta", &Rendering::Renderer::mouseDelta)
        .addProperty("zoom", &Rendering::Renderer::zoom)
        .addFunction("moveView", &Rendering::Renderer::moveView)
        .addFunction("setView", &Rendering::Renderer::setView)
        .addFunction("getWindowSize", &Rendering::Renderer::getWindowSize)
        .addFunction("getViewPos", &Rendering::Renderer::getViewPos)
        .addFunction("zoomView", &Rendering::Renderer::zoomView)
        .addFunction("rotateView", &Rendering::Renderer::rotateView)
        .endClass();

    
    luabridge::getGlobalNamespace(state)
        .beginClass<Game::SF>("Game")
        .addConstructor<void(*) ()>()
        .addFunction("setTickNum", &Game::SF::setTickNum)
        .addFunction("getDelta", &Game::SF::getDelta)
        .endClass();

    luabridge::setGlobal(state, m_renderManGlob.get(), "Graphics");
    luabridge::setGlobal(state, m_gameGlob.get(), "Game");
}

lua_State* Scripting::ScriptManager::getLuaState(){
    return m_luaState;
}