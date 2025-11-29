#include "LZ78.h"


std::vector<LZ78Token> lz78_compress(std::string& input) {
    std::unordered_map<std::string, int> dict;
    dict[""] = 0;

    std::vector<LZ78Token> output;
    std::string current;
    int dictIndex = 1;

    for (char c : input) {
        std::string candidate = current + c;

        if (dict.count(candidate)) {
            // продолжаем фразу
            current = candidate;
        } else {
            // записываем токен
            output.push_back({ dict[current], c });

            // добавляем новую фразу в словарь
            dict[candidate] = dictIndex++;

            // сброс текущей фразы
            current.clear();
        }
    }

    // если осталась незавершённая фраза
    if (!current.empty()) {
        output.push_back({ dict[current.substr(0, current.size() - 1)],
                           current.back() });
    }

    return output;
}


std::string lz78_decompress(std::vector<LZ78Token> &tokens)
{
    std::vector<std::string> dict;
    dict.push_back(""); // индекс 0

    std::string output;

    for (auto& t : tokens) {
        if (t.index >= dict.size())
            throw std::runtime_error("LZ78: invalid index");

        std::string entry = dict[t.index] + t.nextChar;
        output += entry;
        dict.push_back(entry);
    }

    return output;
}

