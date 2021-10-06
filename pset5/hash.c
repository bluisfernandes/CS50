#include <stdio.h>
#include <string.h>
#include <math.h>

unsigned int hash(const char *word);


int main(void)
{
    char *list[]={"a","aaa","baa","z","abcdefghij"};
    
    //printf("%lu\n",strlen(list));
    for (int i = 0; i < 5; i++)
    {
        printf("%s: \thash:%d\n",list[i], hash(list[i]));
    }
}

unsigned int hash(const char *word)
{
    //number of available letter: (a-z) + (')
    const int p = 27;
    //number os buckets
    const unsigned int N = pow(27, 6); //max  6 letters = 27^6
    
    unsigned int hash0 = 0;
    long double p_pow = 1;
    
    //for all letters in buckets or for all letters in word
    for (long i = 0, j = N; j > 1 && i < strlen(word); j = j / p)
    {
        //if letter is an ('), go to last letter (after z): number 26.
        if (word[i] == '\'')
        {
            hash0 = hash0 + p_pow * (word[i] - '\'' + 26);  
        }
        else
        {
            hash0 = hash0 + p_pow * (word[i] - 'a');  
        }
        
        //increment power by p.
        p_pow = p_pow * p;
        
        i++;
    }
    return hash0;
}