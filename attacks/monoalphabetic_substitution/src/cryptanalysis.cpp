#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// --------------------------------------------------
// Frequency Analysis
// --------------------------------------------------

void frequency_analysis(string text)
{
    int count[26] = {0};
    int total = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (isalpha(text[i]))
        {
            char ch = toupper(text[i]);
            count[ch - 'A']++;
            total++;
        }
    }

    cout << "\nLETTER FREQUENCY\n";
    cout << "-------------------------\n";

    // Display in descending order
    bool used[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        int biggest = -1;
        int pos = -1;

        for (int j = 0; j < 26; j++)
        {
            if (!used[j] && count[j] > biggest)
            {
                biggest = count[j];
                pos = j;
            }
        }

        if (pos != -1 && count[pos] > 0)
        {
            used[pos] = true;

            double percentage = 0;

            if (total > 0)
                percentage = (count[pos] * 100.0) / total;

            cout << char('A' + pos)
                 << " : " << count[pos]
                 << " (" << percentage << "%)" << endl;
        }
    }

    cout << "\nMost frequent letters:\n";

    for (int i = 0; i < 3; i++)
    {
        int biggest = -1;
        int pos = -1;

        for (int j = 0; j < 26; j++)
        {
            if (count[j] > biggest)
            {
                biggest = count[j];
                pos = j;
            }
        }

        if (pos != -1 && count[pos] > 0)
        {
            cout << char('A' + pos) << endl;
            count[pos] = -1;
        }
    }
}


// --------------------------------------------------
// Word Frequency Analysis
// --------------------------------------------------

void word_frequency_analysis(string text)
{
    string words[1000];
    int counts[1000];
    int n = 0;

    for (int i = 0; i < 1000; i++)
        counts[i] = 0;

    string word = "";

    for (int i = 0; i <= text.length(); i++)
    {
        if (i < text.length() && isalpha(text[i]))
        {
            word += toupper(text[i]);
        }
        else
        {
            if (word.length() > 0)
            {
                int found = -1;

                for (int j = 0; j < n; j++)
                {
                    if (words[j] == word)
                    {
                        found = j;
                        break;
                    }
                }

                if (found == -1)
                {
                    words[n] = word;
                    counts[n] = 1;
                    n++;
                }
                else
                {
                    counts[found]++;
                }

                word = "";
            }
        }
    }

    cout << "\nWORD FREQUENCY\n";
    cout << "-------------------------\n";

    for (int i = 0; i < n; i++)
    {
        cout << words[i] << " : " << counts[i] << endl;
    }

    cout << "\nONE LETTER WORDS\n";

    for (int i = 0; i < n; i++)
    {
        if (words[i].length() == 1)
            cout << words[i] << " : " << counts[i] << endl;
    }

    cout << "\nTWO LETTER WORDS\n";

    for (int i = 0; i < n; i++)
    {
        if (words[i].length() == 2)
            cout << words[i] << " : " << counts[i] << endl;
    }

    cout << "\nTHREE LETTER WORDS\n";

    for (int i = 0; i < n; i++)
    {
        if (words[i].length() == 3)
            cout << words[i] << " : " << counts[i] << endl;
    }

    cout << "\nREPEATED WORDS\n";

    for (int i = 0; i < n; i++)
    {
        if (counts[i] > 1)
            cout << words[i] << " : " << counts[i] << endl;
    }
}


// --------------------------------------------------
// Pattern Analysis
// --------------------------------------------------

string get_pattern(string word)
{
    int numbers[50];
    int nextNumber = 0;

    for (int i = 0; i < 50; i++)
        numbers[i] = -1;

    string pattern = "";

    for (int i = 0; i < word.length(); i++)
    {
        int value = word[i] - 'A';

        if (numbers[value] == -1)
        {
            numbers[value] = nextNumber;
            nextNumber++;
        }

        pattern += char('0' + numbers[value]);
    }

    return pattern;
}

void pattern_analysis(string text)
{
    string word = "";

    cout << "\nWORD PATTERNS\n";
    cout << "-------------------------\n";

    for (int i = 0; i <= text.length(); i++)
    {
        if (i < text.length() && isalpha(text[i]))
        {
            word += toupper(text[i]);
        }
        else
        {
            if (word.length() > 1)
            {
                cout << word << " : " << get_pattern(word) << endl;
            }

            word = "";
        }
    }
}


// --------------------------------------------------
// Apply Current Substitution
// key[cipher letter] = plaintext letter
// '-' means unknown
// --------------------------------------------------

string apply_substitution(string text, char key[])
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        char ch = text[i];

        if (isalpha(ch))
        {
            ch = toupper(ch);

            if (key[ch - 'A'] != '-')
                result += key[ch - 'A'];
            else
                result += '_';
        }
        else
        {
            result += ch;
        }
    }

    return result;
}


// --------------------------------------------------
// Display Partial Plaintext
// --------------------------------------------------

void display_partial_plaintext(string text, char key[])
{
    cout << "\nPARTIAL PLAINTEXT\n";
    cout << "-------------------------\n";

    string result = apply_substitution(text, key);

    cout << result << endl;
}


// --------------------------------------------------
// Verify Solution
// plaintext + recovered key -> ciphertext
// --------------------------------------------------

bool verify_solution(string plaintext, string ciphertext, char key[])
{
    string result = "";

    for (int i = 0; i < plaintext.length(); i++)
    {
        char ch = plaintext[i];

        if (isalpha(ch))
        {
            ch = toupper(ch);

            bool found = false;

            for (int j = 0; j < 26; j++)
            {
                if (key[j] == ch)
                {
                    result += char('A' + j);
                    found = true;
                    break;
                }
            }

            if (!found)
                result += ch;
        }
        else
        {
            result += ch;
        }
    }

    if (result == ciphertext)
        return true;

    return false;
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    ifstream file("ciphertext.txt");

    if (!file)
    {
        cout << "Could not open ciphertext.txt\n";
        return 0;
    }

    string ciphertext;
    string line;

    while (getline(file, line))
    {
        ciphertext += line;
        ciphertext += '\n';
    }

    file.close();

    cout << "MONOALPHABETIC SUBSTITUTION CRYPTANALYSIS\n";
    cout << "==========================================\n";

    cout << "\nCIPHERTEXT:\n";
    cout << ciphertext << endl;

    frequency_analysis(ciphertext);

    word_frequency_analysis(ciphertext);

    pattern_analysis(ciphertext);

    // Current guesses
    // key[ciphertext letter] = plaintext letter
    char key[26];

    for (int i = 0; i < 26; i++)
        key[i] = '-';

    // --------------------------------------------------
    // Enter substitutions manually
    // Example:
    // Q E
    // W T
    // --------------------------------------------------

    char cipherLetter;
    char plainLetter;

    while (true)
    {
        cout << "\nCurrent partial plaintext:\n";
        display_partial_plaintext(ciphertext, key);

        cout << "\nEnter substitution (cipher plaintext)";
        cout << "\nEnter 0 0 when finished: ";

        cin >> cipherLetter >> plainLetter;

        if (cipherLetter == '0' && plainLetter == '0')
            break;

        cipherLetter = toupper(cipherLetter);
        plainLetter = toupper(plainLetter);

        if (cipherLetter >= 'A' && cipherLetter <= 'Z' &&
            plainLetter >= 'A' && plainLetter <= 'Z')
        {
            key[cipherLetter - 'A'] = plainLetter;
        }
        else
        {
            cout << "Invalid input.\n";
        }
    }

    cout << "\nFINAL RECOVERED PLAINTEXT\n";
    cout << "==========================\n";

    display_partial_plaintext(ciphertext, key);

    cout << "\nRECOVERED KEY\n";
    cout << "==========================\n";

    for (int i = 0; i < 26; i++)
    {
        if (key[i] != '-')
        {
            cout << char('A' + i)
                 << " -> "
                 << key[i] << endl;
        }
    }

    return 0;
}