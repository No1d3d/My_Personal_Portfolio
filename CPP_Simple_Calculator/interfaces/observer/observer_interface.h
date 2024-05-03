#ifndef S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_
#define S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_

#include <string>   // std::string
#include <utility>  // std::pair

namespace s21 {

class ObserverUpdateInterface {
 public:
  virtual ~ObserverUpdateInterface() = default;

  virtual void OnUpdate() = 0;
};

class ObserverErrorInterface {
 public:
  virtual ~ObserverErrorInterface() = default;

  virtual void OnError(const std::pair<std::string, std::string> &error) = 0;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_
