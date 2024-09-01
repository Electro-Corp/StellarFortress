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
  toolbar = new QToolBar("Main Toolbar", &mainWindow);
  mainWindow.addToolBar(Qt::TopToolBarArea, toolbar);

  newAction = new QAction("New", toolbar);
  openAction = new QAction("Open", toolbar);
  saveAction = new QAction("Save", toolbar);
  exitAction = new QAction("Exit", toolbar);

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
  scene = new QGraphicsScene();
  scene->addText("No file loaded.");

  view = new QGraphicsView(scene);

  widget = new QWidget();
  mainDisp = new QHBoxLayout(widget);
  widget->setLayout(mainDisp);

  // Add scene view
  mainDisp->addWidget(view);

  // Properties 
  

  // Create "object list" text
  objListTxt = new QLabel("Object list:");
  // Create object list
  objList = new QListWidget();
  // Create properties text
  propText = new QLabel("Selected object properties:");
  // Create properties toolbox
  toolBox = new QToolBox();
  // Add things to toolbox
  generalPage = new QWidget();
  transformPage = new QWidget();
  
  toolBox->addItem(generalPage, "General");
  toolBox->addItem(transformPage, "Transform");

  propWid = new QWidget(); 
  props = new QVBoxLayout(propWid);
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


void UIMan::addObject(Object* obj){
  objVec.push_back(obj);
  updateListView();
}


void UIMan::updateListView(){
  for(auto& item : objVec){
    item->setText(tr(item->type.c_str()));
    objList->addItem(item);
  }
}