#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;

    //greater than or equal to 9
    do
    {
        start_size = get_int("Start Size: ");
    }
    while (start_size < 9);


    // TODO: Prompt for end size
    int end_size;


    //greater than or equal to the starting population size.
    do
    {
        end_size = get_int("End Size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    printf("Start: %i \nEnd: %i\n", start_size, end_size);

    float i_pop_size = start_size;
    int years = 0;

    for (int n = 1; i_pop_size < end_size; n++)
    {
        i_pop_size = i_pop_size + trunc(i_pop_size / 3.0) - trunc(i_pop_size / 4.0);
        years = n;
    }


    // TODO: Print number of years
    printf("Years: %i\n", years);
}
