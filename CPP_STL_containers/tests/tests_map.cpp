#include <map>

#include "tests.h"

TEST(map, DefaultMapConstructor) {
  s21::map<int, char> s21_empty_map;
  std::map<int, char> og_empty_map;
  EXPECT_EQ(s21_empty_map.empty(), og_empty_map.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> og_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(s21_map.size(), og_map.size());
  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, char> s21_map = {};
  std::map<int, char> og_map = {};
  EXPECT_EQ(s21_map.size(), og_map.size());
  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> s21_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> og_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21_map_copy = s21_map;
  std::map<int, int> og_map_copy = og_map;
  EXPECT_EQ(s21_map_copy.size(), og_map_copy.size());
  auto s21_it = s21_map_copy.begin();
  auto og_it = og_map_copy.begin();
  for (; s21_it != s21_map_copy.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> s21_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> og_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21_map_copy = std::move(s21_map);
  std::map<int, int> og_map_copy = std::move(og_map);
  EXPECT_EQ(s21_map.size(), og_map.size());
  EXPECT_EQ(s21_map_copy.size(), og_map_copy.size());
  auto s21_it = s21_map_copy.begin();
  auto og_it = og_map_copy.begin();
  for (; s21_it != s21_map_copy.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }
}

TEST(map, MapOperator) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> og_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  s21_map['a'] = "Alisa";
  og_map['a'] = "Alisa";
  og_map['b'] = "Ben";
  EXPECT_TRUE(s21_map['a'] == og_map['a']);
  EXPECT_FALSE(s21_map['b'] == og_map['b']);
  EXPECT_TRUE(s21_map['c'] == og_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(s21_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> og_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  s21_map.at('a') = "Alisa";
  og_map.at('a') = "Alisa";
  og_map.at('b') = "Ben";
  EXPECT_TRUE(s21_map['a'] == og_map['a']);
  EXPECT_FALSE(s21_map['b'] == og_map['b']);
  EXPECT_TRUE(s21_map['c'] == og_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> s21_map;
  std::map<char, std::string> og_map;
  EXPECT_TRUE(s21_map.empty() == og_map.empty());
  s21_map.insert('z', "wow");
  EXPECT_FALSE(s21_map.empty() == og_map.empty());
  EXPECT_EQ(s21_map.size(), 1);
}

TEST(map, MapClear) {
  s21::map<int, int> s21_map;
  std::map<int, int> og_map;
  s21_map.clear();
  og_map.clear();
  EXPECT_EQ(s21_map.empty(), og_map.empty());
  s21_map.insert(std::make_pair(1, 1));
  og_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(s21_map.empty(), og_map.empty());
  s21_map.clear();
  og_map.clear();
  EXPECT_EQ(s21_map.empty(), og_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> s21_map;
  std::map<int, char> og_map;
  s21_map.insert(std::make_pair(1, 'a'));
  s21_map.insert(std::make_pair(2, 'a'));
  s21_map.insert(std::make_pair(3, 'a'));
  og_map.insert(std::make_pair(1, 'a'));
  og_map.insert(std::make_pair(2, 'a'));
  og_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }

  auto pr1 = s21_map.insert(std::make_pair(1, 'a'));
  auto pr2 = og_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> s21_map;
  std::map<int, char> og_map;
  s21_map.insert(1, 'a');
  s21_map.insert(2, 'a');
  s21_map.insert(3, 'a');
  og_map.insert(std::make_pair(1, 'a'));
  og_map.insert(std::make_pair(2, 'a'));
  og_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }

  auto pr1 = s21_map.insert(1, 'a');
  auto pr2 = og_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> s21_map;
  std::map<int, char> og_map;
  s21_map.insert(1, 'a');
  s21_map.insert(2, 'a');
  s21_map.insert(3, 'a');
  og_map.insert(std::make_pair(1, 'a'));
  og_map.insert(std::make_pair(2, 'a'));
  og_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }

  auto pr1 = s21_map.insert_or_assign(1, 'b');
  auto i = og_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapErase) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> og_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(s21_map.size(), og_map.size());
  s21_map.erase(s21_map.begin());
  og_map.erase(og_map.begin());
  EXPECT_EQ(s21_map.size(), og_map.size());
  auto s21_it = s21_map.begin();
  auto og_it = og_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++og_it) {
    EXPECT_TRUE((*s21_it).first == (*og_it).first);
    EXPECT_TRUE((*s21_it).second == (*og_it).second);
  }
}

TEST(map, MergeMap) {
  s21::map<int, int> my_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> my_map_merge = {{3, 3}, {4, 4}};

  std::map<int, int> orig_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> orig_map_merge = {{3, 3}, {4, 4}};

  my_map.merge(my_map_merge);
  orig_map.merge(orig_map_merge);

  auto my_it = my_map.begin();
  auto orig_it = orig_map.begin();
  for (; my_it != my_map.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE((*my_it).first == (*orig_it).first);
    EXPECT_TRUE((*my_it).second == (*orig_it).second);
  }
  EXPECT_EQ(my_map_merge.contains(4), orig_map_merge.contains(4));
  EXPECT_EQ(my_map_merge.contains(3), orig_map_merge.contains(3));
}
