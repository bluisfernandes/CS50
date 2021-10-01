#include <stdio.h>
#include <cs50.h>


int main(void)
{

    

    //Read the credit_number
    long credit_number = get_long("Number: ");


    

    long number = credit_number;
    int value_i;
    int sum = 0;
    bool even_i = false;
    int len = 0;
    int begin = 0;



    //Check's the digits, multiply by 2 or only sum.
    do
    {
        value_i = number % 10;
        number = number / 10.0;

        //every 2 digits (even or odd/ true or false)
        if (even_i)
        {
            value_i = value_i * 2;

            //if bigger than 9, sum the digitis
            if (value_i > 9)
            {
                value_i -= 9;
            }
        }

        sum = sum + value_i;
        even_i = !even_i;
        
        
        //retuns the length of number and the 2first digits
        len++;
        if (number >= 10 && number <= 99)
        {
            begin = number;
        }
        
    }
    while (number > 0);
    
    
    //If remaining is <> 0 is INVALID

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    

    //Rules to know the company name, with the length and 2 first digits

    if (len == 15 && (begin == 34 || begin == 37))
    {
        printf("AMEX\n");
    
        
    }
    else if (len == 16 && (begin >= 51 && begin <= 55))
    {
        printf("MASTERCARD\n");
    
        
    }
    else if ((len == 13 || len == 16) && (begin >= 40 && begin <= 49))
    {
        printf("VISA\n");
    
        
    }
    else
    {
        printf("INVALID\n");
    }




}