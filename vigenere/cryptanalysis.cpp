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
vector<int> calculate_distances(string text, vector<string> patterns) {
    vector<int> distances;

    for (string pattern : patterns) {
        vector<int> positions;

        for (int i = 0; i <= (int)text.length() - (int)pattern.length(); i++) {
            if (text.substr(i, pattern.length()) == pattern)
                positions.push_back(i);
        }

        for (int i = 1; i < (int)positions.size(); i++)
            distances.push_back(positions[i] - positions[i - 1]);
    }

    return distances;
}

vector<int> find_factors(vector<int> distances) {
    vector<int> factors;

    for (int d : distances) {
        for (int i = 2; i <= 20; i++) {
            if (d % i == 0)
                factors.push_back(i);
        }
    }

    return factors;
}
vector<int> kasiski_analysis(vector<int> factors) {
    map<int, int> count;

    for (int x : factors)
        count[x]++;

    vector<pair<int, int>> temp;

    for (auto x : count)
        temp.push_back({x.second, x.first});

    sort(temp.rbegin(), temp.rend());

    vector<int> candidates;

    for (auto x : temp)
        candidates.push_back(x.second);

    return candidates;
}

double calculate_ic(string group) {
    int n = group.length();

    if (n <= 1)
        return 0;

    int freq[26] = {0};

    for (char c : group)
        freq[c - 'A']++;

    int sum = 0;

    for (int i = 0; i < 26; i++)
        sum += freq[i] * (freq[i] - 1);

    return (double)sum / (n * (n - 1));
}
