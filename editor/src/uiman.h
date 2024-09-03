#ifndef UIMAN_H
#define UIMAN_H

#include "internal.h"
#include "object.h"
#include "GraphicsView.h"

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
#include <QTabWidget>
#include <QTextEdit>
#include <QGraphicsTextItem>
#include <QTransform>
#include <QColor>

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

  QTabWidget *tabs;


  // Disp area
  QGraphicsScene* scene;
  ZoomGraphicsView* view;
  QWidget* widget;
  QHBoxLayout* mainDisp;

  // Scene toolbar
  QToolBar* sceneToolbar;
  QAction* newObject;

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

  // Scripting area
  QWidget* scripting;
  QHBoxLayout* sceneDisp;


  QWidget* scriptWid;
  QVBoxLayout *scriptSide;
  QToolBar* scriptToolbar;
  QAction* saveScript;

  QTextEdit* scriptEdit;
  QListWidget* scriptList;


  std::vector<Object*> objVec;

  Object* selObj;
  Script* selScript;
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
  void changeScript(QListWidgetItem*, QListWidgetItem*);
  void toggleObjectVisibility();
  void aboutPanel();

  void addObject();

  void saveCurScript();

};

#endif