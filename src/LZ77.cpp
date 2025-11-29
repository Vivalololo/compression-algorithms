#include "LZ77.h"


// Преобразование числа в бинарную строку фиксированной длины
std::string toBinary(uint32_t value, int bits) {
    std::string out(bits, '0');
    for (int i = bits - 1; i >= 0; --i) {
        out[i] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    return out;
}

// LZ77 для бинарных строк (алфавит {0,1})
std::string lz77_compress_binary(const std::string& input) {
    const int WINDOW = 4096;   // max offset
    const int MAX_LEN = 255;   // 8 бит длина

    std::string out;

    size_t pos = 0;
    while (pos < input.size()) {

        size_t best_offset = 0;
        size_t best_length = 0;

        size_t start = (pos > WINDOW) ? pos - WINDOW : 0;

        // Найдём наилучшее совпадение в окне
        for (size_t j = start; j < pos; ++j) {
            size_t length = 0;

            while (pos + length < input.size()
                   && input[j + length] == input[pos + length]
                   && length < MAX_LEN) 
                    {
                        length++;
                    }

            if (length > best_length) {
                best_length = length;
                best_offset = pos - j;
            }
        }

        // Если нет нормального совпадения → литерал
        if (best_length < 3) {
            out.push_back('1');        // literal marker
            out.push_back(input[pos]); // the bit
            pos++;
            continue;
        }

        // Печатаем ссылку
        out.push_back('0');                         // marker
        out += toBinary(best_offset, 12);           // offset (12 bits)
        out += toBinary(best_length, 8);            // length (8 bits)

        pos += best_length;
    }

    return out;
}

uint32_t fromBinary(const std::string& s, size_t pos, int bits) {
    uint32_t v = 0;
    for (int i = 0; i < bits; ++i) {
        v <<= 1;
        if (s[pos + i] == '1') v |= 1;
        else if (s[pos + i] != '0')
            throw std::runtime_error("Invalid bit in binary string");
    }
    return v;
}

std::string lz77_decompress_binary(const std::string& encoded) {
    std::string out;
    size_t pos = 0;

    while (pos < encoded.size()) {

        char marker = encoded[pos];
        pos++;

        if (marker == '1') {
            // literal
            if (pos >= encoded.size())
                throw std::runtime_error("Unexpected end after literal marker");

            out.push_back(encoded[pos]);
            pos++;
        }
        else if (marker == '0') {
            // reference: 12 bits offset + 8 bits length
            if (pos + 12 + 8 > encoded.size())
                throw std::runtime_error("Unexpected end in reference block");

            uint32_t offset = fromBinary(encoded, pos, 12);
            pos += 12;

            uint32_t length = fromBinary(encoded, pos, 8);
            pos += 8;

            if (offset == 0)
                throw std::runtime_error("Offset can't be 0 in LZ77");

            // Copy length bytes from out.size() - offset
            size_t start = out.size() - offset;

            if (start >= out.size())
                throw std::runtime_error("Invalid offset in LZ77 decode");

            for (uint32_t i = 0; i < length; ++i) {
                out.push_back(out[start + i]);
            }
        }
        else {
            throw std::runtime_error("Invalid marker (not 0 or 1)");
        }
    }

    return out;
}

