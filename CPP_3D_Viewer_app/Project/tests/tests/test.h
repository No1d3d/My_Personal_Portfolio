#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "../../ubercontroller.h"
#include "../../model.h"

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);
    ~Test();
private slots:
    void parser();
    void parser_1();
    void shift();
    void rotate();
    void scale();
};

#endif // TEST_H
