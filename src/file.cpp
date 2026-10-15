#include <array>
#include <file.hpp>
#include <string_view>
#include <cstdlib>

std::array<int, 2> find_values(std::string_view str) {
  int first = str.find("_");
  int last = str.find_last_of("_");
  int a = std::atoi(str.substr(first + 1, last).data());
  int b = std::atoi(str.substr(last + 1, str.find(".png")).data());
  return {a, b};
}
