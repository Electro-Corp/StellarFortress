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
        JsonReader jsonReader(filePath);
        Json::Value val = jsonReader.read();
        for(auto& objs : val["objects"]){
            std::cout << objs["obj"].asString() << "\n";
            Object* obj = new Object();
            obj->type = objs["obj"].asString();
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