
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string encrypt(string text, char key[])
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        char ch = text[i];

        if (isalpha(ch))
        {
            if (isupper(ch))
                result += key[ch - 'A'];
            else
                result += tolower(key[ch - 'a']);
        }
        else
        {
            result += ch;
        }
    }

    return result;
}

void display_key(char key[])
{
    cout << "\nSUBSTITUTION KEY\n";
    cout << "-------------------------\n";

    cout << "Plain : ";
    for (int i = 0; i < 26; i++)
        cout << char('A' + i);

    cout << "\nCipher: ";
    for (int i = 0; i < 26; i++)
        cout << key[i];

    cout << endl;
}

int main()
{
    ifstream input("plaintext.txt");

    if (!input)
    {
        cout << "Could not open plaintext.txt\n";
        return 1;
    }

    string plaintext;
    string line;

    while (getline(input, line))
    {
        plaintext += line;
        plaintext += '\n';
    }

    input.close();

    // Monoalphabetic substitution key
    char key[26] =
    {
        'Q','W','E','R','T','Y','U','I','O','P',
        'A','S','D','F','G','H','J','K','L','Z',
        'X','C','V','B','N','M'
    };

    string ciphertext = encrypt(plaintext, key);

    ofstream output("ciphertext.txt");

    if (!output)
    {
        cout << "Could not create ciphertext.txt\n";
        return 1;
    }

    output << ciphertext;
    output.close();

    display_key(key);

    cout << "\nEncryption completed.\n";
    cout << "Ciphertext saved in ciphertext.txt\n";

    return 0;
}
