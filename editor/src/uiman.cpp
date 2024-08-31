#include "uiman.h"

UIMan::UIMan(int w, char** h){
  this->a = Application(w, h);
}

void UIMan::initUI(){
  QPushButton hello("Hello world!", 0);

  hello.resize(100, 30);

  QColor color = QColor(0, 255, 0);

  QPalette p = hello.palette();

  p.setColor(QPalette::ColorRole::Button, color);

  hello.setPalette(p);

  hello.show();
}

int UIMan::run(){
  return a.exec();
}