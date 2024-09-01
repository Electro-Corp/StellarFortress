#ifndef UIMAN_H
#define UIMAN_H

#include "internal.h"
#include "object.h"

#include <QPushButton>
#include <QPalette>
#include <QColor>
#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QAction>  
#include <QTranslator>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QToolBox>
#include <QLabel>
#include <QListView>

#include <vector>

class InternalEngine;

class UIMan : public QObject{
  Q_OBJECT
private:
  QApplication* app;
  QMainWindow mainWindow; 
  InternalEngine* internalEngine;

  // Main toolbar
  QToolBar* toolbar;
  QAction* newAction;
  QAction* openAction;
  QAction* saveAction;
  QAction* exitAction;

  // Disp area
  QGraphicsScene* scene;
  QGraphicsView* view;
  QWidget* widget;
  QHBoxLayout* mainDisp;
  // Side bar
  QLabel *objListTxt;
  // Create object li
  QListWidget *objList;
  // Create properties
  QLabel *propText;
  // Create properties
  QToolBox *toolBox;
  // Add things to toolbox
  QWidget *generalPage;
  QWidget *transformPage;

  QWidget *propWid;
  QVBoxLayout *props;

  std::vector<Object*> objVec;
public:
  explicit UIMan(QApplication* a, InternalEngine* i);

  void initUI();
  int run();

  void addObject(Object* obj);

  void updateListView();
};

#endif