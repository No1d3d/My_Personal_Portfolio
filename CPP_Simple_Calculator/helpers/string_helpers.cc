#include "string_helpers.h"

#include <cctype>

namespace s21 {
namespace string_helpers {

void TrimLeft(std::string_view& text) noexcept {
  std::size_t index = 0;
  while (index < text.size() && std::isspace(text[index])) {
    ++index;
  }
  text.remove_prefix(index);
}

}  // namespace string_helpers
}  // namespace s21