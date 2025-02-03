Is it possible to print a variable's type in standard C++?
> https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
~~~
#include <iostream>
#include <string_view>

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

int& foo_lref();
int&& foo_rref();
int foo_value();

int main() {
  int i = 0;
  const int ci = 0;
  std::cout << "decltype(i) is " << type_name<decltype(i)>() << '\n';
  std::cout << "decltype((i)) is " << type_name<decltype((i))>() << '\n';
  std::cout << "decltype(ci) is " << type_name<decltype(ci)>() << '\n';
  std::cout << "decltype((ci)) is " << type_name<decltype((ci))>() << '\n';
  std::cout << "decltype(static_cast<int&>(i)) is " << type_name<decltype(static_cast<int&>(i))>() << '\n';
  std::cout << "decltype(static_cast<int&&>(i)) is " << type_name<decltype(static_cast<int&&>(i))>() << '\n';
  std::cout << "decltype(static_cast<int>(i)) is " << type_name<decltype(static_cast<int>(i))>() << '\n';
  std::cout << "decltype(foo_lref()) is " << type_name<decltype(foo_lref())>() << '\n';
  std::cout << "decltype(foo_rref()) is " << type_name<decltype(foo_rref())>() << '\n';
  std::cout << "decltype(foo_value()) is " << type_name<decltype(foo_value())>() << '\n';
}
~~~
