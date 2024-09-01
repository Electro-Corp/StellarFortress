#ifndef UIMAN_H
#define UIMAN_H

#include "internal.h"

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

class UIMan : public QObject{
  Q_OBJECT
private:
  QApplication* app;
  QMainWindow mainWindow; 
  InternalEngine* internalEngine;
public:
  explicit UIMan(QApplication* a, InternalEngine* i);

  void initUI();
  int run();
};

#endif
