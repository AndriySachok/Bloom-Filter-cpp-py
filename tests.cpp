#include "bloom_filter.h"
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

void runTests() {
  auto start_time = std::chrono::high_resolution_clock::now();

  int available_size = 10000, actual_fill_size = 10000;
  BloomFilter bloomFilter(
      available_size, actual_fill_size); // перший параметр - загальний розмір,
  // другий - розмір, що планується бути зайнятим(використовується у випадку,
  // коли не вказана к-сть хеш-функцій)
  string base_ip = "192.168.0.";
  bloomFilter.add(base_ip + to_string(1));
  bloomFilter.add(base_ip + to_string(2));
  bloomFilter.add(base_ip + to_string(3));

  for (int i = 1; i < actual_fill_size; i++) {
    if (bloomFilter.check_is_not_in_filter(base_ip + to_string(i)))
      cout << "\033[32m not in filter " << base_ip + to_string(i) << endl;
    else
      cout << "\033[31m probably in filter " << base_ip + to_string(i) << endl;
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time);
  std::cout << "Time taken: " << duration.count() << " milliseconds"
            << std::endl;
}

int main() {
  runTests();
  return 0;
}
