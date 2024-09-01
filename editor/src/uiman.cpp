#include "uiman.h"
#include <QDebug>

void newFile(){
  printf("Placeholder\n");
}

UIMan::UIMan(QApplication* a, InternalEngine* i) : app(a), internalEngine(i) {
}

void UIMan::initUI() {
  mainWindow.resize(640, 480);
  mainWindow.setWindowTitle("Mosaic Scene Editor v0.1 | No file loaded");

  /*
    Main toolbar
  */
  QToolBar* toolbar = new QToolBar("Main Toolbar", &mainWindow);
  mainWindow.addToolBar(Qt::TopToolBarArea, toolbar);

  QAction* newAction = new QAction("New", toolbar);
  QAction* openAction = new QAction("Open", toolbar);
  QAction* saveAction = new QAction("Save", toolbar);
  QAction* exitAction = new QAction("Exit", toolbar);

  connect(newAction, SIGNAL(triggered()), internalEngine, SLOT(newScene()));
  connect(openAction, SIGNAL(triggered()), internalEngine, SLOT(openScene()));
  connect(saveAction, SIGNAL(triggered()), internalEngine, SLOT(saveScene()));
  connect(exitAction, SIGNAL(triggered()), internalEngine, SLOT(exitEditor()));

  toolbar->addAction(newAction);
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(exitAction);

  /*
    Main display area
  */

  // Scene view
  QGraphicsScene* scene = new QGraphicsScene();
  scene->addText("No file loaded.");

  QGraphicsView* view = new QGraphicsView(scene);

  QWidget *widget = new QWidget();
  QHBoxLayout *mainDisp = new QHBoxLayout(widget);
  widget->setLayout(mainDisp);

  // Add scene view
  mainDisp->addWidget(view);

  // Properties 
  

  // Create "object list" text
  QLabel *objListTxt = new QLabel("Object list:");
  // Create object list
  QListView *objList = new QListView();
  // Create properties text
  QLabel *propText = new QLabel("Selected object properties:");
  // Create properties toolbox
  QToolBox *toolBox = new QToolBox();
  // Add things to toolbox
  QWidget *generalPage = new QWidget();
  QWidget *transformPage = new QWidget();
  
  toolBox->addItem(generalPage, "General");
  toolBox->addItem(transformPage, "Transform");

  QWidget *propWid = new QWidget(); 
  QVBoxLayout *props = new QVBoxLayout(propWid);
  propWid->setLayout(props);

  props->addWidget(objListTxt); 
  props->addWidget(objList);
  props->addWidget(propText);
  props->addWidget(toolBox);
  
  
  //props->addWidget(propWid);
  mainDisp->addWidget(propWid);


  mainWindow.setCentralWidget(widget);


  mainWindow.show();
}

int UIMan::run() {
  return app->exec();
}
