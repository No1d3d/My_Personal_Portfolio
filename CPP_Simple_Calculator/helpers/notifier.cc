#include "notifier.h"

#include <algorithm>  // std::for_each

namespace s21 {

void Notifier::RegisterObserver(ObserverUpdateInterface* object) {
  update_observers_.push_back(object);
}

void Notifier::RegisterObserver(ObserverErrorInterface* object) {
  error_observers_.push_back(object);
}

void Notifier::RemoveObserver(ObserverUpdateInterface* object) {
  update_observers_.remove(object);
}

void Notifier::RemoveObserver(ObserverErrorInterface* object) {
  error_observers_.remove(object);
}

void Notifier::NotifyUpdateObservers() {
  std::for_each(update_observers_.cbegin(), update_observers_.cend(),
                [](auto&& item) { item->OnUpdate(); });
}

void Notifier::NotifyErrorObservers(
    const std::pair<std::string, std::string>& error) {
  std::for_each(error_observers_.cbegin(), error_observers_.cend(),
                [&error](auto&& item) { item->OnError(error); });
}

}  // namespace s21
