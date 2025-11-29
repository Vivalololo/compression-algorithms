//#pragma once
#ifndef LZ78
#define LZ78
#include <string>
#include <unordered_map>
#include <vector>


struct LZ78Token {
    int index;
    char nextChar;
};

std::vector<LZ78Token> lz78_compress(std::string& input);
std::string lz78_decompress(std::vector<LZ78Token>&);

#endif