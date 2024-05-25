#include "bloom_filter.h"
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

void runTests() {

  int available_size = 1000, actual_fill_size = 100, counter = 0;
  BloomFilter bloomFilter(available_size, actual_fill_size,
                          3); // перший параметр - загальний розмір,
  // другий - розмір, що планується бути зайнятим(використовується у випадку,
  // коли не вказана к-сть хеш-функцій)
  string base_ip = "192.168.0.";
  auto start_time = chrono::high_resolution_clock::now();

  for (int i = 0; i < actual_fill_size; i++) {
    bloomFilter.add(base_ip + to_string(i));
  }

  for (int i = 0; i < available_size; i++) {
    if (bloomFilter.check_is_not_in_filter(base_ip + to_string(i)))
      cout << "\033[32m not in filter " << base_ip + to_string(i) << endl;
    else {
      cout << "\033[31m probably in filter " << base_ip + to_string(i) << endl;
      counter++;
    }
  }

  auto end_time = chrono::high_resolution_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << endl
            << "Collision Counter: " << counter - actual_fill_size;
}

int main() {
  runTests();
  return 0;
}
