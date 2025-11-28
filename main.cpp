#include "src/Huffman.h"
#include "src/Shannon-Fano.h"
#include <iostream>

using namespace std;


int main() {
    string text = "hello world";

    cout << "===== SHANNON–FANO =====\n";
    auto sfCodes = shannonFanoEncode(text);
    string sfBin = shannonFanoCompress(text, sfCodes);
    cout << "Encoded: " << sfBin << "\n";
    cout << "Decoded: " << shannonFanoDecode(sfBin, sfCodes) << "\n\n";

    cout << "===== HUFFMAN =====\n";
    auto hCodes = huffmanEncode(text);
    string hBin = huffmanCompress(text, hCodes);
    cout << "Encoded: " << hBin << "\n";
    cout << "Decoded: " << huffmanDecode(hBin, hCodes) << "\n";

    return 0;
}