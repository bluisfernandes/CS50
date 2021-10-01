#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //asks the name and print the results
    string name = get_string("What is your name? ");
    printf("hello, %s! \n", name);
}