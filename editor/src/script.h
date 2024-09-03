#ifndef SCRIPT_H
#define SCRIPT_H

#include <QListWidgetItem>

#include <iostream>
#include <sstream>
#include <fstream> 

class Script : public QListWidgetItem{
private:
public:
    std::string fileText;

    Script(std::string file){
        std::ifstream reader(file);

        std::stringstream buffer;
        buffer << reader.rdbuf();

        fileText = buffer.str();

        reader.close(); 
    }

};

#endif