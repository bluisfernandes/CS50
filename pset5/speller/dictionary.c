// Implements a dictionary's functionality

#include <stdbool.h>
//add
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Number of buckets in hash table
// 26 letters + "'"
const unsigned int N = 27 * 27 * 27 * 27 * 27; //pow(27, 1); //max  6 letters = 27^6

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

git add
// Hash table
node *table[N];

//words in dictionary
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    //run for all possible words searching if they're equal
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp -> next)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            return true;
        }   
    }
    
    
    
    return false;
}


//number of available letter: (a-z) + (')
const int p = 27;
long double p_pow[LENGTH + 1] ;

int flag = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    //initializes p_pow
    if(flag == 0)
    {
        p_pow[0] = 1;
        for(int i = 1; i < LENGTH; i++)
        {
            p_pow[i] = p_pow[i - 1] * p;
        }
        flag = 1;
    }
    
    
    
    //const unsigned int N = pow(27, 6); //max  6 letters = 27^6
    
    unsigned int hash0 = 0;
    
    
    //for all letters in buckets or for all letters in word
    for (unsigned int i = 0, j = N; j > 1 && i < strlen(word); j = j / p)
    {
        //if letter is an ('), go to last letter (after z): number 26.
        if (word[i] == '\'')
        {
            hash0 = hash0 + p_pow[i] * (word[i] - '\'' + 26);  
        }
        else
        {
            hash0 = hash0 + p_pow[i] * (tolower(word[i]) - 'a');  
        }
        
        //increment power by p.
        //p_pow = p_pow * p;
        
        i++;
    }
    return hash0;
}



// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //loads dictionary file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }
    
    //set to NULL all values in hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
        //table[i] -> next = NULL;
    }
    
    char dict_word[LENGTH + 1];
    while (fscanf(file, "%s", dict_word) != EOF)
    {
        //count words in dictionary
        count++;
        
        //save in hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        
        //set values to n
        strcpy(n->word, dict_word);
        n-> next = table[hash(dict_word)];
        
        //change pointer of hash table to n
        table[hash(dict_word)] = n;
        
    }

    fclose(file);
    return true;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //return count, of load
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // for all buckets in hash tabble:
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            // We point to the next node first
            node *tmp = table[i]->next;
            // Then, we can free the first node
            free(table[i]);
            // Now we can set the list to point to the next node
            table[i] = tmp;
            // If list is null, when there are no nodes left, our while loop will stop
        }
        
    }
    return true;
}
