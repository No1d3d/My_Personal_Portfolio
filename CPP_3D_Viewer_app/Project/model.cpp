#include "model.h"

Model::Model() {
    delta_ = new delta;
    qDebug() << "Model created\n";
}

Model::~Model() {
    delete [] our_object->vertex_array;
    delete [] our_object->facets_array;
    delete our_object;
    delete delta_;
}

void Model::rotationFunction(object_s* object, double deg, int rotationAxis) {
  deg *= M_PI / 180;
  int adder1 = 0, adder2 = 0;
  if (rotationAxis == XAxis) {
    adder1 = YAxis;
    adder2 = ZAxis;
  } else if (rotationAxis == YAxis) {
    adder1 = XAxis;
    adder2 = ZAxis;
  } else if (rotationAxis == ZAxis) {
    adder1 = XAxis;
    adder2 = YAxis;
  }
  for (int i = 0; i < 3 * object->vertex_count; i += 3) {
    double tmp1 = object->vertex_array[i + adder1];
    double tmp2 = object->vertex_array[i + adder2];
    object->vertex_array[i + adder1] = tmp1 * cos(deg) - tmp2 * sin(deg);
    object->vertex_array[i + adder2] = tmp1 * sin(deg) + tmp2 * cos(deg);
  }
}

void Model::shiftFunction(object_s* object, delta delta, int shiftFlag) {
  for (int i = 0; i < object->vertex_count * 3; i += 3) {
    if (shiftFlag == XAxis) object->vertex_array[i] += delta.dx;
    if (shiftFlag == YAxis) object->vertex_array[i + 1] += delta.dy;
    if (shiftFlag == ZAxis) object->vertex_array[i + 2] += delta.dz;
  }
}

void Model::scaleFunction(object_s* object, double scale) {
  for (int i = 0; i < object->vertex_count * 3; i++) {
    object->vertex_array[i] *= scale;
  }
}

void Model::normalizationFunction(object_s* object) {
  double xmin = object->vertex_array[0];
  double xmax = object->vertex_array[0];
  double ymin = object->vertex_array[1];
  double ymax = object->vertex_array[1];
  for (int i = 3; i < object->vertex_count * 3; i += 3) {
    if (object->vertex_array[i] < xmin) xmin = object->vertex_array[i];
    if (object->vertex_array[i] > xmax) xmax = object->vertex_array[i];
    if (object->vertex_array[i + 1] < ymin) ymin = object->vertex_array[i + 1];
    if (object->vertex_array[i + 1] > ymax) ymax = object->vertex_array[i + 1];
  }
  double x_ratio = xmax / 100;
  double y_ratio = ymax / 100;
  double scaler = x_ratio > y_ratio ? 1 / x_ratio : 1 / y_ratio;
  for (int i = 0; i < object->vertex_count * 3; i++) {
    object->vertex_array[i] *= scaler;
  }
}

void Model::vrx_fsts_counter(QString filename, object_s* object) {
  QFile file(filename);
  QString str;
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream stream(&file);
    while (!stream.atEnd()) {
      str = stream.readLine();
      if (str.length() < 1) {
        continue;
      }
      if (str[0] == 'v' && str[1] == ' ') {
        object->vertex_count++;
      }
      if (str[0] == 'f' && str[1] == ' ') {
        for (int i = 2; i < str.length(); i++) {
          if (str[i].isDigit() && str[i - 1] == ' ') {
            object->facets_count++;
          }
        }
      }
    }
  } else {
    QMessageBox::information(0, "error", file.errorString());
    //        throw std::exception();
  }
  file.close();
}

//  В объектных файлах, в строках с f в начале, когда встречаются символы "//"
//  или "/", оставляем только первую часть до этого символа
// пример:
// f 1 2 3    -   оставляем все
// f 1/4 2/5 3/6   -   делаем сплит по "/" и оставляем только 1 2 3
// f 1//4 2//5 3//6   -   делаем сплит по "//" и оставляем только 1 2 3
void Model::parser(QString filename) {
  our_object = new object_s();
  vrx_fsts_counter(filename,
                   our_object);  // counting the number of edges and vertexes
  QVector<double> vertex_vector;
  QVector<int> facets_vector;
  our_object->facets_array = new int[our_object->facets_count * 3];
  our_object->vertex_array = new double[our_object->vertex_count * 3];
  QFile file(filename);
  QString str;
  int vert_counter = 0;
  int facets_counter = 0;
  int lines_counter = 0;
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream stream(&file);
    while (!stream.atEnd()) {
      str = stream.readLine();
      if (!str.isEmpty()) {
        if (str[0] == 'v' && str[1] == ' ') {
          lines_counter++;
          vert_counter++;
          QStringList parts = str.split(' ');
          for (int i = 1; i <= 3; i++) {
            double buffer = parts.value(i).toDouble();
            vertex_vector.push_back(buffer);
          }
        } else if (str[0] == 'f' && str[1] == ' ') {
                  lines_counter++;
                  facets_counter++;
                  QStringList parts =
                      str.split(' ', Qt::SkipEmptyParts);  // f 1/2 2/3 3/4
                  if (!str.contains('/', Qt::CaseInsensitive)) {
                    for (int i = 1; i < parts.size(); i++) {
                      int buffer =
                          parts.value(i).toInt() - 1;  // change toInt -> toInt - 1
                      facets_vector.append(buffer);
                    }
                  } else {
                    for (int i = 1; i <= 3; i++) {
                      QStringList tmp = parts.value(i).split("/", Qt::SkipEmptyParts);
                      int buffer = tmp.value(0).toInt() - 1;
                      facets_vector.append(buffer);
                    }
                  }
                }
              }
            }
  } else {
    QMessageBox::information(0, "error", file.errorString());
    //        throw std::exception();
  }
  file.close();
  qDebug() << lines_counter << " " << vert_counter << " " << facets_counter;
  for (int i = 0; i < our_object->vertex_count * 3; i++) {
    our_object->vertex_array[i] = vertex_vector.value(i);
  }
  for (int i = 0; i < our_object->facets_count; i++) {
    our_object->facets_array[i] = facets_vector.value(i);
  }

  file.close();
}

void Model::GetCondition(Condition con) {
    qDebug() << "lt" << con.line_size;
}
//  void Model::show_obj() {
//      if (our_object == nullptr ) {
//          qDebug()<<"our object dont exists";
//          return;
//      }
//      if (!our_object->facets_count) {
//          qDebug()<<"our object is empty";
//          return;
//      }
//      qDebug()<<our_object->facets_count<<"\t"<<our_object->vertex_count<<"\n";

//      for (int i = 0; i < our_object->facets_count /*&& i <
//      our_object->facets_count*3*/;i+=3) {
//          qDebug() << our_object->facets_array[i] <<
//          our_object->facets_array[1+i] << our_object->facets_array[2+i] <<
//          "facets\n";
//      }
//      for (int i = 0; i < our_object->vertex_count*3 /*&& i <
//      our_object->vertex_count*3*/;i+=3) {
//          qDebug() << our_object->vertex_array[i] <<
//          our_object->vertex_array[1+i] <<our_object->vertex_array[2+i]
//          <<"vertex\n";
//      }
//  }
