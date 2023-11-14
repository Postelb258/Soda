#include "include/test.hpp"

template <typename T>
void assert_constref(const T& left, const T& right,
                     std::function<bool(const T&, const T&)> predicate) {
  try {
    if (!predicate(left, right)) throw AssertionError<T>();

    std::cout << "Test is passed" << std::endl;
  } catch (const AssertionError<T>& e) {
    std::cerr << e.what() << std::endl;
  }
}

template <typename T>
void assert_ref(T& left, T& right, std::function<bool(T&, T&)> predicate) {
  try {
    if (!predicate(left, right)) throw AssertionError<T>();

    std::cout << "Test is passed" << std::endl;
  } catch (const AssertionError<T>& e) {
    std::cerr << e.what() << std::endl;
  }
}

template <typename T>
void assert_value(T left, T right, std::function<bool(T, T)> predicate) {
  try {
    if (!predicate(left, right)) throw AssertionError<T>();

    std::cout << "Test is passed" << std::endl;
  } catch (const AssertionError<T>& e) {
    std::cerr << e.what() << std::endl;
  }
}

template <typename T>
void assert_ptr(T* left, T* right, std::function<bool(T*, T*)> predicate) {
  try {
    if (!predicate(left, right)) throw AssertionError<T>();

    std::cout << "Test is passed" << std::endl;
  } catch (const AssertionError<T>& e) {
    std::cerr << e.what() << std::endl;
  }
}