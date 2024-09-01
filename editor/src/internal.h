#ifndef INTERNAL_H
#define INTERNAL_H

#include <QObject>

#include <cstdio>
#include <cstdlib>

class InternalEngine : public QObject
{
    Q_OBJECT

public:
    explicit InternalEngine(QObject *parent = nullptr);

public Q_SLOTS:
    void newScene();
    void openScene();
    void saveScene();
    void exitEditor();
};

#endif
