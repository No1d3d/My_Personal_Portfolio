#ifndef S21_SMART_CALC_V20_INTERFACES_GRAPH_CONTROLLER_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_GRAPH_CONTROLLER_INTERFACE_H_

#include <QString>

namespace s21 {

class GraphControllerInterface {
 public:
  virtual ~GraphControllerInterface() = default;  // защищенный деструктор

  virtual void SetGraphExpression(const QString &str) = 0;
  virtual void SetGraphBeginX(double new_x) = 0;
  virtual void SetGraphEndX(double new_x) = 0;
  virtual void SetGraphBeginY(double new_y) = 0;
  virtual void SetGraphEndY(double new_y) = 0;
  virtual void SetGraphYScaleAuto(bool flag) = 0;

  virtual void CalculateGraph() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_GRAPH_CONTROLLER_INTERFACE_H_