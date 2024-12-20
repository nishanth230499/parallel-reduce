#include "reduce.h"

#include <cstdlib>
#include <iostream>

#include "get_time.h"

using Type = long long;

int main(int argc, char* argv[]) {
  size_t n = 1e9;
  int num_rounds = 3;
  if (argc >= 2) {
    n = atoll(argv[1]);
  }
  if (argc >= 3) {
    num_rounds = atoi(argv[2]);
  }

  long long sequential_sum = 0;
  parlay::timer sequential_time;
  for(size_t i = 0; i < n; i++) {
    sequential_sum += i;
  }
  sequential_time.stop();
  std::cout << "Sequential Sum: " << sequential_sum << std::endl;
  std::cout << "Sequential Run Time: " << sequential_time.total_time() << std::endl;

  double total_time = 0;
  Type start = 0;
  for (int i = 0; i <= num_rounds; i++) {
    parlay::timer t;
    long long ans = reduce(start, n); 
    t.stop();

    if (i == 0) {
      std::cout << "Total sum: " << ans << std::endl;
      std::cout << "Warmup round running time: " << t.total_time() << std::endl;
    } else {
      std::cout << "Round " << i << " running time: " << t.total_time()
                << std::endl;
      total_time += t.total_time();
    }
  }
  std::cout << "Average running time: " << total_time / num_rounds << std::endl;

  return 0;
}
