#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
