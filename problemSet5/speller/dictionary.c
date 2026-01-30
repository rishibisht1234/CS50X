// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *ptr = table[index];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // TODO: Improve this hash function
    unsigned long hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = (hash_value * 31) + toupper(word[i]);
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        int index = hash(word);
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->next = NULL;

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i = 0;
    for (i = 0; i < N; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *temp = ptr->next;
            free(ptr);
            ptr = temp;
        }
    }
    if (i == N)
        return true;
    return false;
}
