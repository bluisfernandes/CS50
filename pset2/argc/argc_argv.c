#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    //insert yor name while opening the prompt
    //        ./argc_argv Bruno
    
    
    if(argc == 2)
    {
        printf("Hello, %s\n", argv[1]);
    }
    else
    {
        printf("Hello, world\n");
    }
    
    
}