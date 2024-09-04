#include <QApplication>
#include <QStyleFactory>

#include "internal.h"
#include "uiman.h"


int main(int argc, char** argv) {

  QStringList args;
  for (int i = 0; i < argc; ++i) {
      args << QString(argv[i]);
  }
  args << "-style" << "window";

  char** newArgv = new char*[args.size() + 1];
  for (int i = 0; i < args.size(); ++i) {
      newArgv[i] = strdup(args[i].toUtf8().constData());
  }
  newArgv[args.size()] = nullptr;

  int argcount = args.size();
  QApplication app(argcount, newArgv);

  
  InternalEngine* internalEngine = new InternalEngine();

  UIMan man(&app, internalEngine);
  internalEngine->uiMan = &man;
  man.initUI();

  return man.run();
}