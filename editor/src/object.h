#ifndef OBJECT_H
#define OBJECT_H

#include "transform.h"

#include <QListWidgetItem>

#include <vector>

class Object : public QListWidgetItem{
private:
public:
    std::string objectClass;
    std::vector<std::string> args;

    // GameOBJ specfic stuff

    // Base gameObj
    Transform transform;
    std::string spritePath;
    std::string script;

    // Text
    std::string caption;
    int rgb = 255;
    // Map
    // nothing to see here...

    void setStuff(){
        if(objectClass == "Engine::GameObject"){
            this->spritePath = std::string{"../" + args[0]};
        }else if(objectClass == "UI::Text"){
            this->caption = args[0];
            this->rgb = std::stoi(args[1]);
        }
    }
};

#endif