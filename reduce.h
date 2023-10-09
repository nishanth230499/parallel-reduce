#include "parallel.h"

using namespace parlay;

template <class T>
T reduce(T start, long long n) {
  if (n < 1150) {
    T seq_sum = 0;
    for(int i = 0; i < n; i++) {
      seq_sum += (start + i);
    }
    return seq_sum;
  } else {
    T v1, v2;
    auto f1 = [&]() { v1 = reduce(start, n / 2); };
    auto f2 = [&]() { v2 = reduce(start + n / 2, n - n / 2); };
    par_do(f1, f2);
    return v1 + v2;
  }
}
