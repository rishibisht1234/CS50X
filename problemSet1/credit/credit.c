#include <cs50.h>
#include <stdio.h>

void isvalid(long n);

int main(void)
{
    long number = get_long("Number: ");

    isvalid(number);
}

void isvalid(long n)
{
    int sum_odd = 0;
    int sum_even = 0;
    int i = 0;
    int start1;
    int start2;
    while (n > 0)
    {
        if (i % 2 == 0)
        {
            sum_even += n % 10;
        }
        else
        {
            int inner_number = (n % 10) * 2;
            int inner_sum = 0;
            while (inner_number > 0)
            {
                inner_sum += inner_number % 10;
                inner_number /= 10;
            }
            sum_odd += inner_sum;
        }

        if (n / 10 == 0)
        {
            start1 = n;
        }
        else if (n / 100 == 0)
        {
            start2 = n;
        }

        n /= 10;
        i++;
    }
    int sum = sum_even + sum_odd;

    // printf("sum is %i\nnumber of digits is %i\nstarting1 = %i\nstarting2 = %i\n",
    // sum,i,start1,start2);

    if (sum % 10 == 0 && (i == 13 || i == 16) && start1 == 4)
    {
        printf("VISA\n");
    }
    else if (sum % 10 == 0 && (i == 15) && (start2 == 34 || start2 == 37))
    {
        printf("AMEX\n");
    }
    else if (sum % 10 == 0 && (i == 16) &&
             (start2 == 51 || start2 == 52 || start2 == 53 || start2 == 54 || start2 == 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
