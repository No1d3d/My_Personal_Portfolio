#include <QApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test.h"


//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

using namespace std;

int main(int argc, char *argv[])
{

    //freopen("testing.log", "w+", stdout);
    QApplication a(argc, argv);
    Test *testObject = new Test;
    QTest::qExec(testObject, argc, argv);
    delete testObject;
    return 0;
}
