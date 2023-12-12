#include <QApplication>

#include "container_calc_app.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/images/calc.png"));

  s21::ContainerCalcApp calculator;
  calculator.Init();

  return app.exec();
}
