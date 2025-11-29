#ifndef LZ77
#define LZ77

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

std::string toBinary(uint32_t value, int bits);
std::string lz77_compress_binary(const std::string& input);
uint32_t fromBinary(const std::string& s, size_t pos, int bits);
std::string lz77_decompress_binary(const std::string& encoded);




#endif