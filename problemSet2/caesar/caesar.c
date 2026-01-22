#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_key(int argc, string argv[]);
string encrypt(string text, int key);

int main(int argc, string argv[])
{
    if (!is_valid_key(argc, argv))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    if (key < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plain_text = get_string("plaintext:  ");
    string cypher_text = encrypt(plain_text, key);

    printf("ciphertext: %s\n", cypher_text);

    return 0;
}

string encrypt(string text, int key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (islower(c))
        {
            c = ((c - 'a') + key) % 26 + 'a';
        }
        else if (isupper(c))
        {
            c = ((c - 'A') + key) % 26 + 'A';
        }
        text[i] = c;
    }
    return text;
}

bool is_valid_key(int argc, string argv[])
{
    if (argc != 2)
    {
        return false;
    }
    string s = argv[1];
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
