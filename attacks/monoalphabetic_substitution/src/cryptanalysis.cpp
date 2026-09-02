#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

void frequency_analysis(string text)
{
    int count[26] = {0};
    int total = 0;

    for (int i = 0; i < text.length(); i++)
    {
        if (isalpha(text[i]))
        {
            count[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    cout << "\nFrequency Analysis\n";

    bool used[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        int max = -1;
        int pos = -1;

        for (int j = 0; j < 26; j++)
        {
            if (!used[j] && count[j] > max)
            {
                max = count[j];
                pos = j;
            }
        }

        if (pos != -1 && count[pos] > 0)
        {
            used[pos] = true;
            double percentage = count[pos] * 100.0 / total;

            cout << char('A' + pos) << " "
                 << count[pos] << " "
                 << percentage << "%\n";
        }
    }
}

void word_frequency_analysis(string text)
{
    string words[1000];
    int count[1000] = {0};
    int n = 0;
    string word = "";

    for (int i = 0; i <= text.length(); i++)
    {
        if (i < text.length() && isalpha(text[i]))
        {
            word += toupper(text[i]);
        }
        else if (word.length() > 0)
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
                count[n] = 1;
                n++;
            }
            else
            {
                count[found]++;
            }

            word = "";
        }
    }

    cout << "\nWord Frequency Analysis\n";

    for (int i = 0; i < n; i++)
    {
        if (count[i] > 1)
            cout << words[i] << " " << count[i] << "\n";
    }

    cout << "\nOne-letter words\n";
    for (int i = 0; i < n; i++)
        if (words[i].length() == 1)
            cout << words[i] << "\n";

    cout << "\nTwo-letter words\n";
    for (int i = 0; i < n; i++)
        if (words[i].length() == 2)
            cout << words[i] << "\n";

    cout << "\nThree-letter words\n";
    for (int i = 0; i < n; i++)
        if (words[i].length() == 3)
            cout << words[i] << "\n";

    cout << "\nRepeated words\n";
    for (int i = 0; i < n; i++)
        if (count[i] > 1)
            cout << words[i] << " " << count[i] << "\n";
}

string get_pattern(string word)
{
    int number[26];

    for (int i = 0; i < 26; i++)
        number[i] = -1;

    int next = 0;
    string pattern = "";

    for (int i = 0; i < word.length(); i++)
    {
        int x = word[i] - 'A';

        if (number[x] == -1)
        {
            number[x] = next;
            next++;
        }

        pattern += char('0' + number[x]);
    }

    return pattern;
}

void pattern_analysis(string text)
{
    string word = "";

    cout << "\nPattern Analysis\n";

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
                cout << word << " " << get_pattern(word) << "\n";
            }

            word = "";
        }
    }
}

string apply_substitution(string text, char key[])
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isalpha(text[i]))
        {
            char ch = toupper(text[i]);

            if (key[ch - 'A'] == '-')
                result += '_';
            else
                result += key[ch - 'A'];
        }
        else
        {
            result += text[i];
        }
    }

    return result;
}

void display_partial_plaintext(string text, char key[])
{
    cout << "\nPartial Plaintext\n";
    cout << apply_substitution(text, key) << "\n";
}

bool verify_solution(string plaintext, string ciphertext, char key[])
{
    string result = "";

    for (int i = 0; i < plaintext.length(); i++)
    {
        if (isalpha(plaintext[i]))
        {
            char ch = toupper(plaintext[i]);

            for (int j = 0; j < 26; j++)
            {
                if (key[j] == ch)
                {
                    result += char('A' + j);
                    break;
                }
            }
        }
        else
        {
            result += plaintext[i];
        }
    }

    return result == ciphertext;
}

int main()
{
    ifstream file("ciphertext.txt");

    if (!file)
    {
        cout << "Could not open ciphertext.txt\n";
        return 1;
    }

    string ciphertext, line;

    while (getline(file, line))
    {
        ciphertext += line;
        ciphertext += '\n';
    }

    file.close();

    frequency_analysis(ciphertext);
    word_frequency_analysis(ciphertext);
    pattern_analysis(ciphertext);

    char key[26];

    for (int i = 0; i < 26; i++)
        key[i] = '-';

    char cipher, plain;

    cout << "\nEnter substitutions (0 0 to stop)\n";

    while (true)
    {
        cin >> cipher >> plain;

        if (cipher == '0' && plain == '0')
            break;

        cipher = toupper(cipher);
        plain = toupper(plain);

        if (cipher >= 'A' && cipher <= 'Z' &&
            plain >= 'A' && plain <= 'Z')
        {
            key[cipher - 'A'] = plain;
            display_partial_plaintext(ciphertext, key);
        }
    }

    return 0;
}
