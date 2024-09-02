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
#include <QImage>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

#include <vector>
#include <cmath>

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
  QAction* aboutAction;
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
  // generalPage stuff
  QVBoxLayout *generalPageLayout;
  QPushButton* setVisible;
  QLabel *objType;
  QLabel *scriptLabel;

  QWidget *transformPage;
  QVBoxLayout *transformInfo;

  QWidget* posWid;
  QHBoxLayout* position;
  QLabel *objPosition;

  QWidget* scaleWid;
  QHBoxLayout* scale;
  QLabel *objScale;


  QWidget *propWid;
  QVBoxLayout *props;

  std::vector<Object*> objVec;

  Object* selObj;
public:
  explicit UIMan(QApplication* a, InternalEngine* i);

  void initUI();
  int run();
  void changeTitle(std::string title);

  void addObject(Object* obj);

  

  void updateListView();
  void updateGraphics();
  void clearEditorForNewFile();

public Q_SLOTS:
  void changeItem(QListWidgetItem*, QListWidgetItem*);
  void toggleObjectVisibility();
  void aboutPanel();
};

#endif