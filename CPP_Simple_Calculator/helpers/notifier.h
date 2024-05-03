#ifndef S21_SMART_CALC_V20_HELPERS_NOTIFIER_H_
#define S21_SMART_CALC_V20_HELPERS_NOTIFIER_H_

#include <list>

#include "../interfaces/observer/observer_interface.h"

namespace s21 {

class Notifier final {
 public:
  void RegisterObserver(ObserverUpdateInterface* object);
  void RegisterObserver(ObserverErrorInterface* object);
  void RemoveObserver(ObserverUpdateInterface* object);
  void RemoveObserver(ObserverErrorInterface* object);
  void NotifyUpdateObservers();
  void NotifyErrorObservers(const std::pair<std::string, std::string>& error);

 private:
  std::list<ObserverUpdateInterface*> update_observers_;
  std::list<ObserverErrorInterface*> error_observers_;
};

}  // namespace s21

#endif  // S21_SMART_CALC_V20_HELPERS_NOTIFIER_H_