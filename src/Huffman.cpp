#include "Huffman.h"

using namespace std;

// =============================
// HUFFMAN COMPRESSION
// =============================
struct HuffNode {
    char ch;
    int freq;
    HuffNode *left, *right;
    HuffNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

struct Compare {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

void huffmanBuildCodes(HuffNode *root, string path, map<char,string> &codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = path;
        return;
    }
    huffmanBuildCodes(root->left, path + "0", codes);
    huffmanBuildCodes(root->right, path + "1", codes);
}

map<char,string> huffmanEncode(const string &text) {
    map<char,int> freq;
    for (char c : text) freq[c]++;

    priority_queue<HuffNode*, vector<HuffNode*>, Compare> pq;
    for (auto &p : freq) pq.push(new HuffNode(p.first, p.second));

    while (pq.size() > 1) {
        HuffNode *a = pq.top(); pq.pop();
        HuffNode *b = pq.top(); pq.pop();
        HuffNode *parent = new HuffNode('\0', a->freq + b->freq);
        parent->left = a;
        parent->right = b;
        pq.push(parent);
    }

    HuffNode *root = pq.top();
    map<char,string> codes;
    huffmanBuildCodes(root, "", codes);

    cout << "Huffman table:\n";
    for (auto &p : freq)
        cout << p.first << " freq=" << p.second << " code=" << codes[p.first] << "\n";

    return codes;
}

string huffmanCompress(const string &text, map<char,string> &codes) {
    string out;
    for (char c : text) out += codes[c];
    return out;
}

string huffmanDecode(const string &bin, map<char,string> &codes) {
    map<string,char> back;
    for (auto &p : codes) back[p.second] = p.first;

    string cur, out;
    for (char b : bin) {
        cur.push_back(b);
        if (back.count(cur)) {
            out.push_back(back[cur]);
            cur.clear();
        }
    }
    return out;
}