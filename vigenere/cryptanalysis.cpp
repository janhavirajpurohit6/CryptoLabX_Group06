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
vector<string> split_into_groups(string text, int keyLength) {
    vector<string> groups(keyLength);

    for (int i = 0; i < (int)text.length(); i++)
        groups[i % keyLength] += text[i];

    return groups;
}

void frequency_analysis(vector<string> groups) {
    for (int i = 0; i < (int)groups.size(); i++) {
        int freq[26] = {0};

        for (char c : groups[i])
            freq[c - 'A']++;

        cout << "\nGroup " << i + 1 << ":\n";

        for (int j = 0; j < 26; j++)
            cout << char('A' + j) << " : " << freq[j] << "\n";
    }
}
int find_shift(string group) {
    double english[26] = {
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
        2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
        2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
        6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
        1.974, 0.074
    };

    int n = group.length();
    double best = 999999999;
    int bestShift = 0;

    for (int shift = 0; shift < 26; shift++) {
        int freq[26] = {0};

        for (char c : group) {
            int x = (c - 'A' - shift + 26) % 26;
            freq[x]++;
        }

        double score = 0;

        for (int i = 0; i < 26; i++) {
            double expected = n * english[i] / 100;

            if (expected > 0) {
                score += (freq[i] - expected) *
                         (freq[i] - expected) / expected;
            }
        }

        if (score < best) {
            best = score;
            bestShift = shift;
        }
    }

    return bestShift;
}

string find_key(vector<string> groups) {
    string key;

    for (string group : groups) {
        int shift = find_shift(group);
        key += char('A' + shift);
    }

    return key;
}