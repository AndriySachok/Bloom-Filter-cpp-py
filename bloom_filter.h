#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

class BloomFilter {
private:
  std::vector<bool> bits;
  int hashFuncs, num_expected_elements;

public:
  BloomFilter(int len, int len_to_be_filled, int k = -1) {
    for (int i = 0; i < len; i++) {
      bits.push_back(false);
    }

    if (k != -1) {
      assert(k > 0);
      hashFuncs = k;
    } else {
      hashFuncs = round((static_cast<float>(len) / len_to_be_filled) * log(2));
      std::cout << "Number of hash functions: " << hashFuncs << std::endl;
    }
  }

  bool check_is_not_in_filter(std::string);
  void add(std::string);
};

#endif
