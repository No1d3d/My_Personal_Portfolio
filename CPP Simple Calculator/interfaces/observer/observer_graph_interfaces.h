#ifndef S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_GRAPH_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_GRAPH_INTERFACE_H_

#include "observer_interface.h"

namespace s21 {

class GraphObserverUpdateInterface : public ObserverUpdateInterface {
 public:
  virtual ~GraphObserverUpdateInterface() = default;
};

class GraphObserverErrorInterface : public ObserverErrorInterface {
 public:
  virtual ~GraphObserverErrorInterface() = default;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_GRAPH_INTERFACE_H_
