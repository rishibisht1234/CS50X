#include <cs50.h>
#include <stdio.h>

void print_row(int n, int h);

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    for (int i = 1; i <= h; i++)
    {
        print_row(i, h);
    }
}


void print_row(int n, int h)
{
    int space = h - n;
    for (int i = 0; i < space; i++)
    {
        printf(" ");
    }
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    printf("\n");
}
