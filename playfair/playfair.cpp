#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cctype>

using namespace std;

// Generate 5x5 Playfair key matrix
vector<vector<char>> generate_key_matrix(string keyword) {
    vector<vector<char>> matrix(5, vector<char>(5));
    bool used[26] = {false};

    string key = "";

    // Process keyword
    for (char ch : keyword) {
        ch = toupper(ch);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            key += ch;
            used[ch - 'A'] = true;
        }
    }

    // Add remaining alphabets
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A']) {
            key += ch;
            used[ch - 'A'] = true;
        }
    }

    // Fill matrix
    int k = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = key[k++];
        }
    }

    return matrix;
}


// Remove spaces/special characters and combine I/J
string prepare_plaintext(string plaintext) {
    string result = "";

    for (char ch : plaintext) {
        if (isalpha(ch)) {
            ch = toupper(ch);

            if (ch == 'J')
                ch = 'I';

            result += ch;
        }
    }

    return result;
}

