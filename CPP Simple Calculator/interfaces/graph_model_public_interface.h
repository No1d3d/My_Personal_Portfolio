#ifndef S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_PUBLIC_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_PUBLIC_INTERFACE_H_

#include <string>
#include <vector>

#include "observer/observer_graph_interfaces.h"

namespace s21 {

class GraphModelPublicInterface {
 public:
  virtual ~GraphModelPublicInterface() = default;  // защищенный деструктор

  virtual double GetGraphXBegin() = 0;
  virtual double GetGraphXEnd() = 0;
  virtual double GetGraphYBegin() = 0;
  virtual double GetGraphYEnd() = 0;
  virtual bool GetGraphYScaleAuto() = 0;
  virtual const std::vector<std::pair<double, double>>& GetGraphPoints() = 0;

  virtual void RegisterObserver(GraphObserverUpdateInterface* object) = 0;
  virtual void RegisterObserver(GraphObserverErrorInterface* object) = 0;
  virtual void RemoveObserver(GraphObserverUpdateInterface* object) = 0;
  virtual void RemoveObserver(GraphObserverErrorInterface* object) = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_GRAPH_MODEL_PUBLIC_INTERFACE_H_