#include <QApplication>

#include "internal.h"
#include "uiman.h"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  
  InternalEngine* internalEngine = new InternalEngine();

  UIMan man(&app, internalEngine);
  internalEngine->uiMan = &man;
  man.initUI();

  return man.run();
}