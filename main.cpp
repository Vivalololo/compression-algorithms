#include "src/Huffman.h"
#include "src/Shannon-Fano.h"
#include <iostream>


int main() {
    std::string text = "hello world!";

    std::cout << "===== SHANNON–FANO =====\n";
    auto sfCodes = shannonFanoEncode(text);
    std::string sfBin = shannonFanoCompress(text, sfCodes);
    std::cout << "Encoded: " << sfBin << "\n";
    std::cout << "Decoded: " << shannonFanoDecode(sfBin, sfCodes) << "\n\n";

    std::cout << "===== HUFFMAN =====\n";
    auto hCodes = huffmanEncode(text);
    std::string hBin = huffmanCompress(text, hCodes);
    std::cout << "Encoded: " << hBin << "\n";
    std::cout << "Decoded: " << huffmanDecode(hBin, hCodes) << "\n";

    return 0;
}