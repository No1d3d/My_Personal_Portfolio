#ifndef UBERCONTROLLER_H
#define UBERCONTROLLER_H

#include <QColor>
#include <QObject>
#include <QSettings>
#include <QStack>

#include "model.h"

class UberController : public QObject {
  Q_OBJECT
 public:
  explicit UberController(QObject* parent = nullptr);
  ~UberController();

  Model* model = nullptr;

  void save_settings();
  void load_settings();
  Model::Condition step_back();
  void GetCondition(Model::Condition conditon);

  QStack<Model::Condition> cond_stack;

  QSettings* settings;

 signals:
};

#endif  // UBERCONTROLLER_H
