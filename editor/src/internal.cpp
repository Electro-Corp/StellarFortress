#include "internal.h"

InternalEngine::InternalEngine(QObject *parent) : QObject(parent)
{
}

void InternalEngine::newScene(){
    printf("[Internal] Creating new scene...\n");
}

void InternalEngine::openScene(){
    printf("[Internal] Opening scene...\n");
    QFileDialog* file = new QFileDialog(0, "Open Scene", "/home/segfault/StellarFortress/assets/scenes", tr("Scene files (*.json)"));
    file->show();
    if (file->exec()){
        std::string filePath = file->selectedFiles()[0].toStdString();
        std::cout << "Opening " << filePath << "\n";
        uiMan->changeTitle(std::string{"Mosiac Editor v0.1 | " + filePath});
        JsonReader jsonReader(filePath);
        Json::Value val = jsonReader.read();
        uiMan->clearEditorForNewFile();
        for(auto& objs : val["objects"]){
            std::cout << objs["obj"].asString() << "\n";
            Object* obj = new Object();
            obj->objectClass = objs["obj"].asString();

            // Add args
            for(auto& arg : objs["args"]){
                obj->args.push_back(arg.asString());
            }

            obj->script = objs["script"].asString();

            // Do transform
            if(objs.isMember("transform")){
            // if(objs["transfrom"]["position"] != NULL){
                    float xPos = objs["transform"]["position"][0].asFloat();
                    float yPos = objs["transform"]["position"][1].asFloat();
                    obj->transform.position = Vector2(xPos, yPos);
                //}
            // if(objs["transform"]["scale"] != NULL){
                    float xScale = objs["transform"]["scale"][0].asFloat();
                    float yScale = objs["transform"]["scale"][1].asFloat();
                    obj->transform.scale = Vector2(xScale, yScale);
            // }
            }

            obj->setStuff();

            if(uiMan){
                uiMan->addObject(obj);
            }else{
                printf("uiMan null...\n");
            }
        }
    }
}

void InternalEngine::saveScene(){
    printf("[Internal] Saving scene...\n");
}

void InternalEngine::exitEditor(){
    printf("[Internal] Exiting...\n");
    exit(0);
}