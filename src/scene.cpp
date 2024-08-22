/*
*/
#include <scene.h>

#include <gameObjects/ui/text.h>

std::unique_ptr<Engine::GameObject> createInstance(const std::string& className, const std::vector<std::string>& args) {
    static std::unordered_map<std::string, std::function<std::unique_ptr<Engine::GameObject>(const std::vector<std::string>&)>> factoryMap;

    if (factoryMap.empty()) {
        factoryMap["Engine::GameObject"] = [](const std::vector<std::string>& args) {
            return std::make_unique<Engine::GameObject>(args[0]);
        };
        factoryMap["UI::Text"] = [](const std::vector<std::string>& args) {
            return std::make_unique<UI::Text>(args[0], std::stoi(args[1]));
        };
    }

    auto it = factoryMap.find(className);
    if (it != factoryMap.end()) {
        return it->second(args);
    }

    return nullptr;
}


Engine::Scene::Scene(std::string name){
    this->name = name;
}

Engine::Scene::Scene(std::string name, std::string sceneJson, Game::SF* game){
    this->name = name;
    // Load scene from a json file
    JsonReader reader(sceneJson);
    Json::Value val = reader.read();
    for(auto& objs : val["objects"]){
        std::cout << objs["texture"].asString() << std::endl;
        // Generate
        std::vector<std::string> argList;

        for(auto& args : objs["args"]){
            argList.push_back(args.asString());
        }
        
        std::string script = objs["script"].asString();
        float xPos = objs["transform"]["position"][0].asFloat();
        float yPos = objs["transform"]["position"][1].asFloat();
        float xScale = objs["transform"]["scale"][0].asFloat();
        float yScale = objs["transform"]["scale"][0].asFloat();

        
        std::unique_ptr<Engine::GameObject> obj = createInstance(objs["obj"].asString(), argList);
        //Engine::GameObject* tmp = /*createInstance(objs["obj"].asString(), argList);*/ dynamic_cast<Engine::GameObject*>(obj.release());
    
        obj->transform.position = Transform::Vector2(xPos, yPos);
        obj->transform.scale = Transform::Vector2(xScale, yScale);
        
        if(script != "NONE"){
            game->loadScript(obj.get(), script);
        }

        addObject(obj.release());
        
    }
}

void Engine::Scene::addObject(Engine::GameObject* object){
    this->gameObjects.emplace_back(object);
}

std::vector<Engine::GameObject*> Engine::Scene::getObjs(){
    return gameObjects;
}