
#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits.h>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <valarray>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

template<typename T>
class _DisplayType;

template<typename T>
void _displayType(T&& t);

#define PEEK(x) LOG(INFO) << #x << ": [" << (x) << "]"

/* template end */

class A {
 public:
  virtual ~A() = default;
  virtual int foo() {
    return 0;
  }
};

class B : public A {
 public:
  int foo() override {
    return 1;
  }

  std::vector<std::map<int, int>> bar(int, const std::string&) {
    return {
    {
      {0, 0}
    }
    };
  }
  std::vector<std::map<int, int>> bar(const std::string&) {
    return {
      {
        {1, 1}
      }
    };
  }
  template <typename R, typename... Args>
  using method_ptr_t = std::vector<R> (B::*)(int, const Args&...);

  template <typename R, typename... Args>
  std::vector<R> forward(method_ptr_t<R, Args...> m, int v, const Args&... args);
};

template <typename R, typename... Args>
std::vector<R> B::forward(method_ptr_t<R, Args...> m, int v, const Args&... args) {
  return (this->*m)(v, args...);
}

TEST(Foo, Bar) {
  B b;
  A* a = &b;
  using Mptr = int(A::*)();
  Mptr ptr = &A::foo;
  LOG(INFO) << "virtual method pointer: " << ptr;
  EXPECT_EQ(1, (a->*ptr)());
  std::string ss("aa");
  EXPECT_EQ(1, b.forward(&B::bar, 0, ss)[0].count(0));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  return RUN_ALL_TESTS();
}

