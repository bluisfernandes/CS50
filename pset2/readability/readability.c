#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(void)
{
    
    string text = get_string("Text :");
    int letters = 0;
    int words = 0;
    int sentences = 0;
    float index;
    float L;
    float S;
    
    int len = strlen(text);
    
    
    //for each character, a loop count if is a letter, a entire word or a sentence
    
    for (int i = 0; i < len; i++)
    {
        //if there is a space, a word is complete
        if (text[i] == ' ')
        {
            words++;
        }
        // at the end of a sentence, count one more.
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        // for every letter, lower or upcase, count one more
        else if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++;
        }
    }
    words++;
    
    
    // find L and S
    L = (float) letters / words * 100;
    S = (float) sentences / words * 100;
    
    
    // find index
    
    index = 0.0588 * L - 0.296 * S - 15.8;
    
    
    // print the results
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Grade %.0f\n", index);
    }
    
}