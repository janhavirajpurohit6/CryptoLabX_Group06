#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

string clean_ciphertext(string text) {
    string result;

    for (char c : text) {
        if (isalpha(c))
            result += toupper(c);
    }

    return result;
}

vector<string> find_repeated_patterns(string text) {
    vector<string> patterns;

    for (int len = 3; len <= 5; len++) {
        map<string, int> count;

        for (int i = 0; i <= (int)text.length() - len; i++) {
            string s = text.substr(i, len);
            count[s]++;
        }

        for (auto x : count) {
            if (x.second > 1)
                patterns.push_back(x.first);
        }
    }

    return patterns;
}