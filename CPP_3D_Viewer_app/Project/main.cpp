//#include <QApplication>
#include "mainwindow.h"
//#include "../VIEW/mainwindow.h"

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#else
#include <QtGui/QApplication>
#endif

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}