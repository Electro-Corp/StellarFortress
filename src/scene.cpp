/*
*/
#include <scene.h>

#include <gameObjects/ui/text.h>
#include <gameObjects/ui/inputpanel.h>
#include <map/map.h>

/*
    Feels like this dosen't belong here, but I don't know where else to put it
    or more rather, i dont care enough right now to move it to the utils folder
*/
std::unique_ptr<Engine::GameObject> createInstance(const std::string& className, const std::vector<std::string>& args) {
    static std::unordered_map<std::string, std::function<std::unique_ptr<Engine::GameObject>(const std::vector<std::string>&)>> factoryMap;

    if (factoryMap.empty()) {
        factoryMap["Engine::GameObject"] = [](const std::vector<std::string>& args) {
            return std::make_unique<Engine::GameObject>(args[0]);
        };
        factoryMap["UI::Text"] = [](const std::vector<std::string>& args) {
            return std::make_unique<UI::Text>(args[0], std::stoi(args[1]));
        };
        factoryMap["UI::Panel"] = [](const std::vector<std::string>& args) {
            return std::make_unique<UI::Panel>(args[0], std::stoi(args[1]));
        };
        factoryMap["Map::Map"] = [](const std::vector<std::string>& args){
            return std::make_unique<Map::Map>(std::stoi(args[0]), std::stoi(args[1]));
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

Engine::Scene::Scene(std::string name, std::string sceneJson){
    this->name = name;
    this->json = sceneJson;
}

void Engine::Scene::load(Game::SF* game){
    // Load scene from a json file
    JsonReader reader(json);
    Json::Value val = reader.read();
    for(auto& objs : val["objects"]){
        //std::cout << objs["texture"].asString() << std::endl;
        // Generate
        std::vector<std::string> argList;
    
        for(auto& args : objs["args"]){
            argList.push_back(args.asString());
        }
    
        std::string script = objs["script"].asString();
        std::unique_ptr<Engine::GameObject> obj = createInstance(objs["obj"].asString(), argList);
    
        if(objs.isMember("transform")){
           // if(objs["transfrom"]["position"] != NULL){
                float xPos = objs["transform"]["position"][0].asFloat();
                float yPos = objs["transform"]["position"][1].asFloat();
                obj->transform.position = Transform::Vector2(xPos, yPos);
            //}
           // if(objs["transform"]["scale"] != NULL){
                float xScale = objs["transform"]["scale"][0].asFloat();
                float yScale = objs["transform"]["scale"][1].asFloat();
                obj->transform.scale = Transform::Vector2(xScale, yScale);
           // }
        }
    
        if(script != "NONE"){
            std::cout << "Script " << script << " for " << objs["obj"].asString() << " " << objs["args"][0] << std::endl; 
            game->loadScript(obj.get(), script);
    
            obj->initScript();
        }
    
    
    
        addObject(obj.release());
    }
    loaded = true;
}

void Engine::Scene::deload(){
    printf("%s deloading...\n", this->name.c_str());
    /*for(auto& gm : gameObjects){
        delete gm;
    }
    gameObjects.clear();
    gameObjects.shrink_to_fit();
    loaded = false;*/
    printf("%s deloaded.\n", this->name.c_str());
}

void Engine::Scene::addObject(Engine::GameObject* object){
    this->gameObjects.emplace_back(object);
}

std::vector<Engine::GameObject*> Engine::Scene::getObjs(){
    return gameObjects;
}