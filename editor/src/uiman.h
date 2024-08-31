#include <QApplication>
#include <QPushButton>
#include <QPalette>
#include <QColor>

class UIMan{
private:
  QApplication a;
public:
  UIMan(int w, char** h);

  void initUI();
  int run();
};