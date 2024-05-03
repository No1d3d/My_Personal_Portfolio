#include <QTest>
#include "test.h"


Test::Test(QObject *parent) :
    QObject(parent) {
}

Test::~Test() {

}

void Test::parser() {
    Model* model = new Model();
    model->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/pyramid.obj");

    double vals[][3] = {
        {0,1,0}, {-1,0,-1}, {1,0,-1}, {1,0,1}, {-1,0,1}

    };
    int j = 0;
    for (size_t i = 0; i <= (size_t(model->our_object->vertex_count) - 1); i++) {
        QCOMPARE((vals[i][0]), model->our_object->vertex_array[j]);
        QCOMPARE((vals[i][1]), model->our_object->vertex_array[j+1]);
        QCOMPARE((vals[i][2]), model->our_object->vertex_array[j+2]);
        j+=3;
    }
    delete model;
}

void Test::parser_1() {
    Model* model = new Model();
    model->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");

    double vals[][3] = {
        {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,-1,-1}, {1,1,-1}, {0,1,1}, {-1,1,1}, {-1,1,-1}

    };
    int j = 0;
    for (size_t i = 0; i <= (size_t(model->our_object->vertex_count) - 1); i++) {
        QCOMPARE((vals[i][0]), model->our_object->vertex_array[j]);
        QCOMPARE((vals[i][1]), model->our_object->vertex_array[j+1]);
        QCOMPARE((vals[i][2]), model->our_object->vertex_array[j+2]);
        j+=3;
    }
    delete model;
}

void Test::shift() {
    Model* model = new Model();
    Model* model1 = new Model();
    model->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");
    model1->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");
    double x_s = 2.0;
    double y_s = 4.0;
    double z_s = 5.0;
    model->delta_->dx = x_s;
    model->delta_->dy = y_s;
    model->delta_->dz = z_s;
    model->shiftFunction(model->our_object, *(model->delta_), 1);
    model->shiftFunction(model->our_object, *(model->delta_), 2);
    model->shiftFunction(model->our_object, *(model->delta_), 3);
    model1->shiftFunction(model->our_object, *(model->delta_), 1);
    model1->shiftFunction(model->our_object, *(model->delta_), 2);
    model1->shiftFunction(model->our_object, *(model->delta_), 3);
    for (size_t i = 0; i <= (size_t(model->our_object->vertex_count) - 1); i++) {
        QCOMPARE(model->our_object->vertex_array[i], model->our_object->vertex_array[i]);
    }
    delete model;
    delete model1;
}

void Test::rotate() {
    Model* model = new Model();
    Model* model1 = new Model();
    double x_r = 2.0;
    double y_r = 3.0;
    double z_r = 4.0;
    model->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");
    model1->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");
    model->rotationFunction(model->our_object, x_r, 1);
    model->rotationFunction(model->our_object, y_r, 2);
    model->rotationFunction(model->our_object, z_r, 3);
    model1->rotationFunction(model->our_object, x_r, 1);
    model1->rotationFunction(model->our_object, y_r, 2);
    model1->rotationFunction(model->our_object, z_r, 3);
    for (size_t i = 0; i <= (size_t(model->our_object->vertex_count) - 1); i++) {
        QCOMPARE(model->our_object->vertex_array[i], model->our_object->vertex_array[i]);
    }
    delete model;
    delete model1;
}

void Test::scale() {
    Model* model = new Model();
    model->parser("/Users/ennuidra/Desktop/CPP4_3DViewer_v2.0-1/src/obj/box.obj");
    double sc = 2.0;
    model->scaleFunction(model->our_object, sc);
    double vals[][3] = {
        {1,-1,-1}, {1,-1,1}, {-1,-1,1}, {-1,-1,-1}, {1,1,-1}, {0,1,1}, {-1,1,1}, {-1,1,-1}

    };
    int j = 0;
    for (size_t i = 0; i <= (size_t(model->our_object->vertex_count) - 1); i++) {
        QCOMPARE((vals[i][0] *= sc), model->our_object->vertex_array[j]);
        QCOMPARE((vals[i][1] *= sc), model->our_object->vertex_array[j+1]);
        QCOMPARE((vals[i][2] *= sc), model->our_object->vertex_array[j+2]);
        j+=3;
    }
    delete model;
}
