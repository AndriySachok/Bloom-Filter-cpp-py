#include "bloom_filter.h"
#include "fnv.h"
#include <cstdint>

bool BloomFilter::check_is_not_in_filter(std::string str) {
  for (int i = 0; i < BloomFilter::hashFuncs; i++) {
    // хешування рядка
    uint64_t hash = fnv1_64(str, i);

    // зміна довжини хешу під заданий розмір фільтру
    uint64_t resizedHash = hash % this->bits.size();

    // перевірка на наявність у фільтрі
    if (this->bits[resizedHash] == 0)
      return true;
  }
  return false;
}

void BloomFilter::add(std::string str) {
  for (int i = 0; i < BloomFilter::hashFuncs; i++) {
    // хешування рядка
    uint64_t hash = fnv1_64(str, i);

    // зміна довжини хешу під заданий розмір фільтру
    uint64_t resizedHash = hash % this->bits.size();

    // оновлення фільтру
    this->bits[resizedHash] = true;
  }
}
