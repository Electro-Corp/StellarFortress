#ifndef OBJECT_H
#define OBJECT_H

#include <QListWidgetItem>

class Object : public QListWidgetItem{
private:
public:
    std::string type;
};

#endif