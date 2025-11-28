#ifndef SHANNON_FANO_H
#define SHANNON_FANO_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>

std::map<char, std::string> shannonFanoEncode(const std::string& text);
std::string shannonFanoCompress(const std::string& text, std::map<char,std::string>& codes);
std::string shannonFanoDecode(const std::string& bin, std::map<char,std::string>& codes);

#endif