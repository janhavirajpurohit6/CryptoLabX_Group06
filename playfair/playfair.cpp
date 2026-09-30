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

vector<string> create_digraphs(string plaintext) {
    vector<string> digraphs;

    int i = 0;

    while (i < plaintext.length()) {

        char first = plaintext[i];

        // Last character
        if (i + 1 >= plaintext.length()) {
            digraphs.push_back(string(1, first) + "X");
            i++;
        }
        else {
            char second = plaintext[i + 1];

            // Repeated letters
            if (first == second) {
                digraphs.push_back(string(1, first) + "X");
                i++;
            }
            else {
                digraphs.push_back(string(1, first) + string(1, second));
                i += 2;
            }
        }
    }

    return digraphs;
}
void find_position(
    const vector<vector<char>>& matrix,
    char ch,
    int& row,
    int& col
) {
    if (ch == 'J')
        ch = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string encrypt_pair(
    string pair,
    const vector<vector<char>>& matrix
) {
    int r1, c1, r2, c2;

    find_position(matrix, pair[0], r1, c1);
    find_position(matrix, pair[1], r2, c2);

    // Same row
    if (r1 == r2) {
        return string(1, matrix[r1][(c1 + 1) % 5]) +
               string(1, matrix[r2][(c2 + 1) % 5]);
    }

    // Same column
    else if (c1 == c2) {
        return string(1, matrix[(r1 + 1) % 5][c1]) +
               string(1, matrix[(r2 + 1) % 5][c2]);
    }

    // Rectangle rule
    else {
        return string(1, matrix[r1][c2]) +
               string(1, matrix[r2][c1]);
    }
}
string decrypt_pair(
    string pair,
    const vector<vector<char>>& matrix
) {
    int r1, c1, r2, c2;

    find_position(matrix, pair[0], r1, c1);
    find_position(matrix, pair[1], r2, c2);

    // Same row
    if (r1 == r2) {
        return string(1, matrix[r1][(c1 + 4) % 5]) +
               string(1, matrix[r2][(c2 + 4) % 5]);
    }

    // Same column
    else if (c1 == c2) {
        return string(1, matrix[(r1 + 4) % 5][c1]) +
               string(1, matrix[(r2 + 4) % 5][c2]);
    }

    // Rectangle rule
    else {
        return string(1, matrix[r1][c2]) +
               string(1, matrix[r2][c1]);
    }
}


// Playfair encryption
string playfair_encrypt(
    const vector<string>& digraphs,
    const vector<vector<char>>& matrix
) {
    string ciphertext = "";

    for (string pair : digraphs) {
        ciphertext += encrypt_pair(pair, matrix);
    }

    return ciphertext;
}

string playfair_decrypt(
    string ciphertext,
    const vector<vector<char>>& matrix
) {
    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i += 2) {
        string pair = ciphertext.substr(i, 2);
        plaintext += decrypt_pair(pair, matrix);
    }

    return plaintext;
}