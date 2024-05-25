#ifndef FNV_H
#define FNV_H

#include <cstdint>
#include <iostream>
#include <string>

const uint64_t FNV_prime_64 = 1099511628211;
const uint64_t offset_basis_64 = 14695981039346656037ULL;

uint64_t fnv1_64(const std::string &str, const int &funcIndex) {
  uint64_t hash_value = offset_basis_64;

  for (char c : str + std::to_string(funcIndex)) {
    hash_value = (hash_value * FNV_prime_64) ^ static_cast<int>(c);
  }

  return hash_value;
}

#endif
