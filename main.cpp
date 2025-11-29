#include "src/Huffman.h"
#include "src/Shannon-Fano.h"
#include "src/LZ77.h"
#include "src/LZ78.h"
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
        std::cout << "OK: matches!\n\n";
    else
        std::cout << "ERROR: mismatch!\n\n";

    
    std::cout << "===== LZ78 =====\n";
    std::string text2 = "ABABABAABABAABBBBCCCCCXYZXYZ";
    auto compressed = lz78_compress(text);
    auto decompressed = lz78_decompress(compressed);
    std::cout << "Original:   " << text << "\n";
    std::cout << "Decoded:    " << decompressed << "\n\n";
    std::cout << "Tokens:\n";
    for (auto& t : compressed)
        std::cout << "(" << t.index << ", '" << t.nextChar << "')\n";


    return 0;
}