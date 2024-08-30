#include <QApplication>
#include <QPushButton>
#include <QPalette>
#include <QColor>

int main(int argc, char** argv)
{
  QApplication a(argc, argv);

  QPushButton hello("Hello world!", 0);

  hello.resize(100, 30);

  QColor color = QColor(0, 255, 0);

  QPalette p = hello.palette();

  p.setColor(QPalette::ColorRole::Button, color);

  hello.setPalette(p);

  hello.show();

  return a.exec();
}