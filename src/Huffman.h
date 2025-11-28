#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>

std::map<char, std::string> huffmanEncode(const std::string& text);
std::string huffmanCompress(const std::string& text, std::map<char,std::string>& codes);
std::string huffmanDecode(const std::string& bin, std::map<char,std::string>& codes);

#endif