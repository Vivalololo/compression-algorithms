#include "src/Huffman.h"
#include "src/Shannon-Fano.h"
#include "src/LZ77.h"
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
    std::cout << "Decoded: " << huffmanDecode(hBin, hCodes) << "\n\n";

    std::cout << "===== LZ77 =====\n";
    std::string data = "01010101010101010111";
    std::string encoded = lz77_compress_binary(data);
    std::cout << "Input:  \t" << data << "\n";
    std::cout << "Encoded:\t" << encoded << "\n";
    std::string dec = lz77_decompress_binary(encoded);
    std::cout << "Decoded:\t" << dec << "\n";

    if (data == dec)
        std::cout << "OK: matches!\n";
    else
        std::cout << "ERROR: mismatch!\n";

    return 0;
}