#ifndef __TEST_H
#define __TEST_H

#include <exception>
#include <functional>
#include <iostream>

#define TESTIT __attribute__((constructor))

template <typename T>
class AssertionError : public std::exception {
 private:
  T m_left;
  T m_right;

 public:
  char* what() {
    return "[error] Test is failed. Left(" + std::to_string(m_left) +
           ") and right(" + std::to_string(m_right) +
           ") does not match by predicate";
  }
};

template <typename T>
void assert_constref(const T& left, const T& right,
                     std::function<bool(const T&, const T&)>);

template <typename T>
void assert_value(T left, T right, std::function<bool(T, T)>);

template <typename T>
void assert_ref(T& left, T& right, std::function<bool(T&, T&)>);

template <typename T>
void assert_ptr(T* left, T* right, std::function<bool(T*, T*)>);

#endif