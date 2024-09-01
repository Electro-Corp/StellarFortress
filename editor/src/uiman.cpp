#include "uiman.h"
#include <QDebug>

void newFile(){
  printf("Placeholder\n");
}

UIMan::UIMan(QApplication* a, InternalEngine* i) : app(a), internalEngine(i) {
}

void UIMan::initUI() {
  mainWindow.resize(1024, 768);
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
    Scene View
  */


  mainWindow.show();
}

int UIMan::run() {
  return app->exec();
}
