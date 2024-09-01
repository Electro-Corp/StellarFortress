#include "internal.h"

InternalEngine::InternalEngine(QObject *parent) : QObject(parent)
{
}

void InternalEngine::newScene(){
    printf("[Internal] Creating new scene...\n");
}

void InternalEngine::openScene(){
    printf("[Internal] Opening scene...\n");
}

void InternalEngine::saveScene(){
    printf("[Internal] Saving scene...\n");
}

void InternalEngine::exitEditor(){
    printf("[Internal] Exiting...\n");
    exit(0);
}