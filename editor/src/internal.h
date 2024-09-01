#ifndef INTERNAL_H
#define INTERNAL_H

#include "uiman.h"
#include "jsonReader.h"
#include "object.h"
#include "transform.h"

#include <QObject>
#include <QFileDialog>

#include <cstdio>
#include <cstdlib>
#include <iostream>

class UIMan;

class InternalEngine : public QObject
{
    Q_OBJECT

public:
    explicit InternalEngine(QObject *parent = nullptr);

    UIMan* uiMan;

public Q_SLOTS:
    void newScene();
    void openScene();
    void saveScene();
    void exitEditor();
};

#endif
