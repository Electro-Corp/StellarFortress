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
  aboutAction = new QAction("About", toolbar);
  exitAction = new QAction("Exit", toolbar);

  connect(newAction, SIGNAL(triggered()), internalEngine, SLOT(newScene()));
  connect(openAction, SIGNAL(triggered()), internalEngine, SLOT(openScene()));
  connect(saveAction, SIGNAL(triggered()), internalEngine, SLOT(saveScene()));
  connect(exitAction, SIGNAL(triggered()), internalEngine, SLOT(exitEditor()));
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutPanel()));

  toolbar->addAction(newAction);
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addAction(aboutAction);
  toolbar->addAction(exitAction);

  /*
    Main display area
  */

  tabs = new QTabWidget;

  // Scene view
  scene = new QGraphicsScene();
  scene->addText("No file loaded.");

  view = new ZoomGraphicsView(scene);

  widget = new QWidget();
  mainDisp = new QHBoxLayout(widget);
  widget->setLayout(mainDisp);

  // Add scene view
  mainDisp->addWidget(view);

  tabs->addTab(widget, tr("Scene View"));


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
  setVisible = new QPushButton("Toggle visibility");
  connect(setVisible, SIGNAL(clicked()), this, SLOT(toggleObjectVisibility()));

  objType = new QLabel("Object Type");
  scriptLabel = new QLabel("Script path");

  generalPageLayout->addWidget(setVisible);
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

  scripting = new QWidget();
  sceneDisp = new QHBoxLayout(scripting);

  scriptEdit = new QTextEdit();
  scriptList = new QListWidget();
  connect(scriptList, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(changeScript(QListWidgetItem*, QListWidgetItem*)));


  sceneDisp->addWidget(scriptEdit);
  sceneDisp->addWidget(scriptList);

  tabs->addTab(scripting, tr("Scripts"));

  


  mainWindow.setCentralWidget(tabs);


  mainWindow.show();
}

int UIMan::run() {
  return app->exec();
}

void UIMan::changeTitle(std::string title){
  mainWindow.setWindowTitle(title.c_str());
}


void UIMan::addObject(Object* obj){
  objVec.push_back(obj);
  updateListView();

  // Load into view
  updateGraphics();
}

void UIMan::toggleObjectVisibility(){
  if(selObj){
    printf("Toggling visibility %s\n", selObj->script.c_str());
    selObj->visibility = !(selObj->visibility);
    updateGraphics();
  }
}

void UIMan::updateGraphics(){
  scene->clear();
  for(auto& obj : objVec){
    if(obj->spritePath.size() > 0 && obj->visibility){
      QImage image(obj->spritePath.c_str());
      if(image.isNull()){
        printf("%s is null!\n", obj->spritePath.c_str());
      }else{
        printf("%s is here\n", obj->spritePath.c_str());
      }
      float normX = ((obj->transform.scale.x) / 800) * 800; 
      float normY = ((obj->transform.scale.y) / 600) * 800; 
      QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image.scaled(QSize(normX, normY))));
      item->setPos(obj->transform.position.x - 800, obj->transform.position.y - 600);
      scene->addItem(item);
    }
  }
}

void UIMan::updateListView(){
  for(auto& item : objVec){
    item->setText(tr(item->objectClass.c_str()));
    objList->addItem(item);

    item->scriptItem->setText(tr(item->script.c_str()));
    scriptList->addItem(item->scriptItem);
  }
}

void UIMan::clearEditorForNewFile(){
  scene->clear();
  objList->clear();
  objVec.clear();
}

void UIMan::changeItem(QListWidgetItem* c, QListWidgetItem* prev){
  Object* selObj = (Object*)c;
  this->selObj = selObj;

  objType->setText(tr(selObj->objectClass.c_str()));
  scriptLabel->setText(tr(selObj->script.c_str()));

  std::string posText(std::string{"Position: (" + std::to_string(selObj->transform.position.x) + ", "+std::to_string(selObj->transform.position.y) + ")"});
  objPosition->setText(tr(posText.c_str()));

  std::string scaleText(std::string{"Scale: (" + std::to_string(selObj->transform.scale.x) + ", "+std::to_string(selObj->transform.scale.y) + ")"});
  objScale->setText(tr(scaleText.c_str()));

  std::cout << "sel change, " << selObj->objectClass << "\n";
}

void UIMan::changeScript(QListWidgetItem* c, QListWidgetItem* prev){
  Script* selScript = (Script*)c;
  this->selScript = selScript;


  scriptEdit->setText(tr(selScript->fileText.c_str()));

}

void UIMan::aboutPanel(){
  QMessageBox* about = new QMessageBox();
  about->setWindowTitle("About Mosaic Scene Editor");
  about->about(about, "About Mosiac Scene Editor", "An open source editor for Mosiac Scene JSON files.\nFor use with games that use the Mosiac Engine.\n");
}