#ifndef S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_INTERFACE_H_

#include <string>

#include "graph_model_public_interface.h"

namespace s21 {

class GraphModelInterface : public GraphModelPublicInterface {
 public:
  virtual ~GraphModelInterface() = default;  // защищенный деструктор

  virtual void SetGraphExpression(const std::string& new_expression) = 0;
  virtual void SetGraphBeginX(double new_x) = 0;
  virtual void SetGraphEndX(double new_x) = 0;
  virtual void SetGraphBeginY(double new_y) = 0;
  virtual void SetGraphEndY(double new_y) = 0;
  virtual void SetGraphYScaleAuto(bool flag) = 0;

  virtual void CalculateGraph() = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_INTERFACE_H_