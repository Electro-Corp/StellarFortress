/*
*/
#include <scripting/scriptmanager.h>

Scripting::Script::Script(lua_State* L) : 
    updateFunc(luabridge::getGlobal(L, "update")), 
    init(luabridge::getGlobal(L, "init")){

}   

void Scripting::Script::setGameObj(Engine::GameObject* obj){
    this->thisObj = obj;
}

luabridge::LuaRef Scripting::Script::getUpdateFunc(){
    return updateFunc;
}

void Scripting::Script::update(){
    updateFunc(thisObj);
}

Scripting::ScriptManager::ScriptManager(){
    
}

Scripting::ScriptManager::ScriptManager(std::string p_scriptPath, Rendering::Renderer* renderer) {   
    // Create Lua state             
    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);

    m_renderManGlob = std::unique_ptr<Rendering::Renderer>(renderer);
    
    exposeGame();
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
        int scriptLoadStatus = luaL_dofile(m_luaState, path.c_str());

        object->script = new Script(m_luaState);
        object->script->setGameObj(object);

        updateFuncs.push_back(luabridge::getGlobal(m_luaState, "update"));
        initFuncs.push_back(luabridge::getGlobal(m_luaState, "init"));
    //}
}

void Scripting::ScriptManager::exposeGame(){
    printf("[ScriptManager] Expose Vector2/Transform/GameObject to Lua\n");
    // Expose Transform
    luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Transform::Vector2>("Vector2")
        .addConstructor<void(*) (float, float)>()
        .addProperty("x", &Transform::Vector2::x)
        .addProperty("y", &Transform::Vector2::y)
        .endClass();

    luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Transform::Transform>("Transform")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (float, float, float)>()
        .addConstructor<void(*) (Transform::Vector2, float)>()
        .addProperty("position", &Transform::Transform::position)
        .addProperty("angle", &Transform::Transform::angle)
        .addProperty("scale", &Transform::Transform::scale)
        .endClass();

    luabridge::getGlobalNamespace(m_luaState)
        .beginClass<Engine::GameObject>("GameObject")
        .addConstructor<void(*) ()>()
        .addConstructor<void(*) (Transform::Transform)>()
        .addFunction("getSprite", &Engine::GameObject::getSprite)
        .addProperty("transform", &Engine::GameObject::transform)
        .endClass();

    luabridge::getGlobalNamespace(m_luaState)
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

    luabridge::setGlobal(m_luaState, m_renderManGlob.get(), "Graphics");
}

lua_State* Scripting::ScriptManager::getLuaState(){
    return m_luaState;
}