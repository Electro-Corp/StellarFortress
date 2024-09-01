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
  connect(objList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(changeItem(QListWidgetItem*, QListWidgetItem*)));
  // Create properties text
  propText = new QLabel("Selected object properties:");
  // Create properties toolbox
  toolBox = new QToolBox();
  // Add things to toolbox
  generalPage = new QWidget();
  generalPageLayout = new QVBoxLayout(generalPage);
  objType = new QLabel("Object Type");
  scriptLabel = new QLabel("Script path");

  generalPageLayout->addWidget(objType);
  generalPageLayout->addWidget(scriptLabel); 

  transformPage = new QWidget();
  transformInfo = new QVBoxLayout(transformPage);

  posWid = new QWidget();
  position = new QHBoxLayout(transformPage);
  posWid->setLayout(position);
  objPosition = new QLabel("Position");
  position->addWidget(objPosition);

  transformInfo->addWidget(posWid);

  scaleWid = new QWidget();
  scale = new QHBoxLayout(transformPage);
  scaleWid->setLayout(scale);
  objScale = new QLabel("Scale");
  scale->addWidget(objScale);

  transformInfo->addWidget(scaleWid);
  
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

  // Load into view
  if(obj->spritePath.size() > 0){
    QImage image(obj->spritePath.c_str());
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item->setPos(0 , 0);
    item->setScale(0.4);
    scene->addItem(item);
  }
}


void UIMan::updateListView(){
  for(auto& item : objVec){
    item->setText(tr(item->objectClass.c_str()));
    objList->addItem(item);
  }
}

void UIMan::clearEditorForNewFile(){
  scene->clear();
  objList->clear();
  objVec.clear();
}

void UIMan::changeItem(QListWidgetItem* c, QListWidgetItem* prev){
  Object* selObj = (Object*)c;

  objType->setText(tr(selObj->objectClass.c_str()));
  scriptLabel->setText(tr(selObj->script.c_str()));

  std::string posText(std::string{"Position: (" + std::to_string(selObj->transform.position.x) + ", "+std::to_string(selObj->transform.position.y) + ")"});
  objPosition->setText(tr(posText.c_str()));

  std::string scaleText(std::string{"Scale: (" + std::to_string(selObj->transform.scale.x) + ", "+std::to_string(selObj->transform.scale.y) + ")"});
  objScale->setText(tr(scaleText.c_str()));

  std::cout << "sel change, " << selObj->objectClass << "\n";
}