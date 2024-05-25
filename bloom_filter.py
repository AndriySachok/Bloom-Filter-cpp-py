import math
from bitarray import bitarray
import time

FNV_prime_64 = 1099511628211
offset_basis_64 = 14695981039346656037


class BloomFilter(object):

    def __init__(self, size, number_expected_elements=100000):
        self.size = size
        self.number_expected_elements = number_expected_elements

        self.bloom_filter = bitarray(self.size)
        self.bloom_filter.setall(0)

        self.number_hash_functions = round(
            (self.size / self.number_expected_elements) * math.log(2)
        )

    def fnv1_64(self, s, funcIndex):
        hash_value = offset_basis_64
        for char in s + str(funcIndex):
            hash_value = (
                hash_value * FNV_prime_64
            ) & 0xFFFFFFFFFFFFFFFF  # Constrain to 64 bits

            hash_value = hash_value ^ ord(char)
            hash_value = hash_value & 0xFFFFFFFFFFFFFFFF  # Constrain to 64 bits

        return hash_value

    def add_to_filter(self, item):
        for i in range(self.number_hash_functions):
            resizedHash = self.fnv1_64(item, i) % self.size
            self.bloom_filter[resizedHash] = 1

    def check_is_not_in_filter(self, item):
        for i in range(self.number_hash_functions):
            resizedHash = self.fnv1_64(item, i) % self.size
            if self.bloom_filter[resizedHash] == 0:
                return True
        return False


available_size = 1000
actual_fill_size = 1000
bloom_filter = BloomFilter(available_size, actual_fill_size)
base_ip = "192.168.0."
start_time = time.time() * 1000

for i in range(0, actual_fill_size):
    bloom_filter.add_to_filter(base_ip + str(i))


for i in range(0, available_size):
    if bloom_filter.check_is_not_in_filter(base_ip + str(i)):
        print("not in filter " + base_ip + str(i))
    else:
        print("probably in filter " + base_ip + str(i))

end_time = time.time() * 1000
elapsed_time = end_time - start_time

print("Time taken:", elapsed_time, "milliseconds")
