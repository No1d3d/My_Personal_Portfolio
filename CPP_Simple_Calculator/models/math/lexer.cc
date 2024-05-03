#include "lexer.h"

#include <algorithm>  // for std::transform
#include <cctype>     // for std::isdigit
#include <stdexcept>  // for std::invalid_argument | std::logic_error

#include "../../helpers/fast_float.h"
#include "../../helpers/string_helpers.h"

namespace s21 {

std::list<Lexeme> Lexer::ParseLexemes(const std::string& input) {
  std::list<Lexeme> lexemes_list;
  std::string lower_string{input};

  std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(),
                 [](unsigned char ch) { return std::tolower(ch); });

  std::string_view view{lower_string};
  string_helpers::TrimLeft(view);

  while (!view.empty()) {
    if (std::isdigit(view.front())) {
      auto [lexeme, new_view] = GetNumberLexemeFromString(view);
      view = new_view;
      lexemes_list.push_back(lexeme);
    } else {
      auto [lexeme, new_view] = GetNonNumberLexemeFromString(view);

      if (lexeme.type == kUnknownLexeme) {
        throw std::invalid_argument("Unknown lexeme in input string");
      }

      view = new_view;
      lexemes_list.push_back(lexeme);
    }
    string_helpers::TrimLeft(view);
  }
  return lexemes_list;
}

void Lexer::FixLexemesList(std::list<Lexeme>& lexemes_list) {
  Lexer::FixUnPlusMinusLexemesList(lexemes_list);

  int lbracket_create = 0;
  int lrbracket_check = 0;

  auto lexemes_begin = lexemes_list.begin();
  auto lexemes_end = lexemes_list.end();

  for (int i = 0; lexemes_begin != lexemes_end; ++lexemes_begin, ++i) {
    Lexeme check = *lexemes_begin;
    Lexeme last;

    if (i > 0) {
      auto tmp = lexemes_begin;
      last = *(--tmp);
    }

    if (lbracket_create > 0 && check.type == kLBracketLexeme) {
      ++lrbracket_check;
    }

    if (lbracket_create > 0 && check.type == kRBracketLexeme) {
      --lrbracket_check;
    }

    if (i > 0 && last.IsFunction() && check.type != kLBracketLexeme) {
      lexemes_list.insert(lexemes_begin, Lexeme::MakeLexeme(kLBracketLexeme));

      ++lbracket_create;
      continue;
    }

    if (lbracket_create > 0 && !check.IsFunction() &&
        check.type != kLBracketLexeme && lrbracket_check == 0) {
      while (lbracket_create > 0) {
        lexemes_list.insert(lexemes_begin, Lexeme::MakeLexeme(kRBracketLexeme));

        --lbracket_create;
      }
    }
  }

  if (lbracket_create > 0) {
    while (lbracket_create > 0) {
      lexemes_list.insert(lexemes_end, Lexeme::MakeLexeme(kRBracketLexeme));

      --lbracket_create;
    }
  }
}

void Lexer::FixUnPlusMinusLexemesList(std::list<Lexeme>& lexemes_list) {
  auto lexemes_begin = lexemes_list.begin();
  auto lexemes_end = lexemes_list.end();
  int first = 0;
  Lexeme last;
  while (lexemes_begin != lexemes_end) {
    Lexeme check = *lexemes_begin;

    if (first == 0 || last.IsOperator() || last.type == kLBracketLexeme) {
      if (check.type == kAddLexeme) {
        *lexemes_begin = Lexeme::MakeLexeme(kUnPlusLexeme);
      } else if (check.type == kSubLexeme) {
        *lexemes_begin = Lexeme::MakeLexeme(kUnMinusLexeme);
      }
    }

    last = check;
    ++lexemes_begin;
    ++first;
  }
}

std::string Lexer::AddLexemeToString(const std::string& input_string,
                                     const Lexeme& add_lexeme) {
  std::list<Lexeme> lexemes_list = Lexer::ParseLexemes(input_string);

  if (lexemes_list.size() == 0) {
    if ((add_lexeme.IsOperator() && add_lexeme.IsBinary()) ||
        add_lexeme.type == kRBracketLexeme) {
      throw std::logic_error("Wrong operator");
    } else if (add_lexeme.IsFunction()) {
      lexemes_list.push_back(add_lexeme);
      lexemes_list.push_back(Lexeme::MakeLexeme(kLBracketLexeme));
    } else {
      lexemes_list.push_back(add_lexeme);
    }
  } else {
    Lexer::FixUnPlusMinusLexemesList(lexemes_list);
    Lexeme top = lexemes_list.back();
    if (add_lexeme.type == kUnMinusLexeme) {
      AddUnMinusToList(lexemes_list);
    } else if (add_lexeme.type == kLBracketLexeme) {
      if (top.IsConstant() || top.type == kRBracketLexeme) {
        lexemes_list.push_back(Lexeme::MakeLexeme(kMulLexeme));
      }
      lexemes_list.push_back(add_lexeme);
    } else if (add_lexeme.IsConstant()) {
      if (add_lexeme.type == kNumberLexeme && top.type == kNumberLexeme) {
        lexemes_list.back().str.append(add_lexeme.str);
      } else {
        if (top.IsConstant() || top.type == kRBracketLexeme) {
          lexemes_list.push_back(Lexeme::MakeLexeme(kMulLexeme));
        }
        lexemes_list.push_back(add_lexeme);
      }
    } else if (add_lexeme.IsFunction()) {
      if (top.IsConstant() || top.type == kRBracketLexeme) {
        lexemes_list.push_back(Lexeme::MakeLexeme(kMulLexeme));
      }
      lexemes_list.push_back(add_lexeme);
      lexemes_list.push_back(Lexeme::MakeLexeme(kLBracketLexeme));
    } else if (add_lexeme.IsOperator()) {
      if (top.type == kUnMinusLexeme || top.type == kUnPlusLexeme ||
          top.type == kLBracketLexeme) {
        throw std::logic_error("Wrong operator");
      } else if (top.IsOperator()) {
        lexemes_list.pop_back();
        lexemes_list.push_back(add_lexeme);
      } else {
        lexemes_list.push_back(add_lexeme);
      }
    } else if (add_lexeme.type == kRBracketLexeme) {
      if (top.type == kLBracketLexeme) {
        throw std::logic_error("Wrong operator");
      } else if (!IsLbracketExist(lexemes_list)) {
        throw std::logic_error("Wrong operator");
      } else if (top.IsOperator()) {
        if (top.type == kUnMinusLexeme || top.type == kUnPlusLexeme) {
          throw std::logic_error("Wrong operator");
        } else {
          lexemes_list.pop_back();
          lexemes_list.push_back(add_lexeme);
        }
      } else {
        lexemes_list.push_back(add_lexeme);
      }
    } else {
      lexemes_list.push_back(add_lexeme);
    }
  }

  std::string result_string = Lexer::LexemeListToString(lexemes_list);
  std::replace(result_string.begin(), result_string.end(), '~', '-');

  return result_string;
}

std::string Lexer::AddPointToString(const std::string& input_string) {
  std::list<Lexeme> lexemes_list = Lexer::ParseLexemes(input_string);

  if (lexemes_list.size() != 0) {
    Lexeme top = lexemes_list.back();
    if (top.type == kNumberLexeme) {
      if (top.str.find('.') == std::string::npos) {
        lexemes_list.back().str.append(".");
      }
    } else if (top.IsConstant() || top.type == kRBracketLexeme) {
      lexemes_list.push_back(Lexeme::MakeLexeme(kMulLexeme));
      lexemes_list.push_back(Lexeme::MakeLexeme(kNumberLexeme, 0, "0."));
    } else {
      lexemes_list.push_back(Lexeme::MakeLexeme(kNumberLexeme, 0, "0."));
    }
  } else {
    lexemes_list.push_back(Lexeme::MakeLexeme(kNumberLexeme, 0, "0."));
  }

  std::string result_string = Lexer::LexemeListToString(lexemes_list);

  return result_string;
}

std::string Lexer::RemoveLexemeFromStringEnd(const std::string& input_string) {
  std::list<Lexeme> lexemes_list = Lexer::ParseLexemes(input_string);

  if (lexemes_list.size() != 0) {
    Lexeme top = lexemes_list.back();
    if (top.type == kNumberLexeme) {
      lexemes_list.back().str.erase(--(lexemes_list.back().str.end()));
      if (lexemes_list.back().str.length() == 0) {
        lexemes_list.pop_back();
      }
    } else {
      lexemes_list.pop_back();
      if (top.type == kLBracketLexeme) {
        if (lexemes_list.size() > 0) {
          Lexeme top2 = lexemes_list.back();
          if (top2.IsFunction()) {
            lexemes_list.pop_back();
          }
        }
      }
    }
  }

  std::string result_string = LexemeListToString(lexemes_list);

  return result_string;
}

std::string Lexer::LexemeListToString(const std::list<Lexeme>& lexemes_list) {
  std::string result_string;

  auto lexemes_begin = lexemes_list.begin();
  auto lexemes_end = lexemes_list.end();
  int last_number = static_cast<int>(lexemes_list.size() - 1);

  for (int i = 0; lexemes_begin != lexemes_end; ++lexemes_begin, ++i) {
    result_string.append((*lexemes_begin).str);
    if (i != last_number) {
      result_string.append(" ");
    }
  }

  return result_string;
}

std::pair<Lexeme, std::string_view> Lexer::GetNonNumberLexemeFromString(
    const std::string_view& view) {
  Lexeme lexeme;
  std::string_view new_view{view};

  for (auto [key, type] : types_map_) {
    if (view.compare(0, key.size(), key) == 0) {
      new_view.remove_prefix(key.size());
      lexeme = Lexeme::MakeLexeme(type);
      return {lexeme, new_view};
    }
  }

  return {lexeme, new_view};
}

std::pair<Lexeme, std::string_view> Lexer::GetNumberLexemeFromString(
    const std::string_view& view) {
  Lexeme lexeme;
  std::string_view new_view{view};

  double value{};
  const char* ptr_start = new_view.data();
  const char* ptr_end = new_view.data() + new_view.size();

  auto [ptr, error] = fast_float::from_chars(ptr_start, ptr_end, value);

  if (error != std::errc()) {
    throw std::invalid_argument("Invalid parsing from input string");
  }

  std::string::size_type ptr_diff = ptr - ptr_start;
  std::string num_string = std::string{new_view.substr(0, ptr_diff)};
  lexeme = Lexeme::MakeLexeme(kNumberLexeme, value, num_string);
  new_view.remove_prefix(ptr_diff);

  return {lexeme, new_view};
}

bool Lexer::IsLbracketExist(const std::list<Lexeme>& lexemes_list) {
  int lbracket_count = 0;
  int rbracket_count = 0;

  auto lexemes_begin = lexemes_list.begin();
  auto lexemes_end = lexemes_list.end();

  for (; lexemes_begin != lexemes_end; ++lexemes_begin) {
    if ((*lexemes_begin).type == kLBracketLexeme) {
      ++lbracket_count;
    } else if ((*lexemes_begin).type == kRBracketLexeme) {
      ++rbracket_count;
    }
  }

  if (lbracket_count > rbracket_count) {
    return true;
  } else {
    return false;
  }
}

void Lexer::AddUnMinusToList(std::list<Lexeme>& lexemes_list) {
  Lexeme top = lexemes_list.back();
  if (top.type == kRBracketLexeme) {
    lexemes_list.push_back(Lexeme::MakeLexeme(kMulLexeme));
    lexemes_list.push_back(Lexeme::MakeLexeme(kUnMinusLexeme));
  } else {
    int unminus_cnt = 0;
    bool need_restore_save = false;
    Lexeme save_lexeme;
    while (lexemes_list.size() > 0) {
      Lexeme check = lexemes_list.back();

      if (check.IsConstant()) {
        save_lexeme = check;
        need_restore_save = true;
        lexemes_list.pop_back();
        continue;
      }

      if (check.type == kUnPlusLexeme) {
        lexemes_list.pop_back();
        continue;
      }

      if (check.type == kUnMinusLexeme) {
        lexemes_list.pop_back();
        ++unminus_cnt;
        continue;
      }

      break;
    }

    if (unminus_cnt % 2 == 0) {
      lexemes_list.push_back(Lexeme::MakeLexeme(kUnMinusLexeme));
    }

    if (need_restore_save) {
      lexemes_list.push_back(save_lexeme);
    }
  }
}

}  // namespace s21