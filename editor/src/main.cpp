#include "uiman.h"
int main(int argc, char** argv)
{
  UIMan man(argc,argv);
  man.initUI();
  return man.run();
}