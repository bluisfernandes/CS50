// Implements a dictionary's functionality

#include <stdbool.h>
//add
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "dictionary.h"

// Number of buckets in hash table
// 26 letters + "'"
const unsigned int N = 27*27; //pow(27, 1); //max  6 letters = 27^6

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Hash table
node *table[N];

//words in dictionary
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //to dooo
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    //number of available letter: (a-z) + (')
    const int p = 27;
    
    //const unsigned int N = pow(27, 6); //max  6 letters = 27^6
    
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



// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //table[];
    
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        printf("ops\n");
        return false;
    }
    
    char dict_word[46];
    while(fscanf(file, "%s", dict_word) != EOF && count < 9137)
    {
        //count words in dictionary
        count++;
        
        
        printf("%s  \t%d\t", dict_word, count);
        printf("h=%u\t", hash(dict_word));
        printf("\n");
        
        
        //save in hash table
        
    }
    fclose(file);
    return true;
}




// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return true;
}
