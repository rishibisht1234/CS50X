#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
// index = 0.0588 * L - 0.296 * S - 15.8;
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);
int compute_grade(string text);

int main(void)
{
    string text = get_string("Text: ");
    int grade = compute_grade(text);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int compute_grade(string text)
{
    int w = count_words(text);
    float L = (count_letters(text) / (float) w) * 100;
    float S = (count_sentences(text) / (float) w) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

int count_sentences(string text)
{
    int sentences = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

int count_letters(string text)
{
    int letters = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int count = 0;
    int len = strlen(text);

    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}
