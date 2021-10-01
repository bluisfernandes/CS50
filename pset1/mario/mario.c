#include <cs50.h>
#include <stdio.h>

void draw(char c, int n);

int main(void)
{
    int n;

    //read the heigth of pyramid 1<=x<=8
    do
    {
        n = get_int("Heigh: ");
    }
    while (n < 1 || n > 8);

    //draw the pyramids
    for (int i = 1; i <= n; i++)
    {
        draw(' ', n - i);
        draw('#', i);
        draw(' ', 2);
        draw('#', i);
        printf("\n");
    }
}

void draw(char c, int n)
{
    for (int i = 1; i <= n ; i++)
    {
        printf("%c", c);
    }
}