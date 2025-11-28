#include "Shannon-Fano.h"


struct SFNode {
    char ch;
    int freq;
    std::string code;
};

void shannonFanoBuild(std::vector<SFNode*> &a, int l, int r) {
    if (l >= r) return;
    int total = 0;
    for (int i = l; i <= r; i++) total += a[i]->freq;

    int cur = 0, split = l;
    for (int i = l; i <= r; i++) {
        cur += a[i]->freq;
        if (cur * 2 >= total) {
            split = i;
            break;
        }
    }

    for (int i = l; i <= split; i++) a[i]->code.push_back('0');
    for (int i = split + 1; i <= r; i++) a[i]->code.push_back('1');

    shannonFanoBuild(a, l, split);
    shannonFanoBuild(a, split + 1, r);
}

std::map<char, std::string> shannonFanoEncode(const std::string &text) {
    std::vector<SFNode> table(256);
    for (int i = 0; i < 256; i++) { table[i].ch = i; table[i].freq = 0; }
    for (char c : text) table[(unsigned char)c].freq++;

    std::vector<SFNode*> symbols;
    for (auto &x : table) if (x.freq > 0) symbols.push_back(&x);

    sort(symbols.begin(), symbols.end(), [&](SFNode* a, SFNode* b){return a->freq > b->freq;});

    shannonFanoBuild(symbols, 0, symbols.size() - 1);

    std::map<char, std::string> codes;
    std::cout << "Shannon-Fano table:\n";
    for (auto s : symbols) {
        std::cout << s->ch << " freq=" << s->freq << " code=" << s->code << "\n";
        codes[s->ch] = s->code;
    }
    return codes;
}

std::string shannonFanoCompress(const std::string &text, std::map<char, std::string> &codes) {
    std::string out;
    for (char c : text) out += codes[c];
    return out;
}

std::string shannonFanoDecode(const std::string &bin, std::map<char, std::string> &codes) {
    std::map<std::string, char> back;
    for (auto &p : codes) back[p.second] = p.first;

    std::string cur, out;
    for (char b : bin) {
        cur.push_back(b);
        if (back.count(cur)) {
            out.push_back(back[cur]);
            cur.clear();
        }
    }
    return out;
}
