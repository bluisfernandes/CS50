#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


bool check_duplicates(string key);

int main(int argc, string argv[])
{
    string key;
    
    
    //argc must be 2, with "./substitution" and "key"
    //argv[0] is "./substitution"
    //argv[0] is "key"
    //key must have 26 characteres
    
    if (argc == 2)
    {
        if (strlen(argv[1]) != 26)
        {
            printf("%ld\n", strlen(argv[1]));
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        key = argv[1];
        
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if ((key[i] < 'A' || key[i] > 'Z') && (key[i] < 'a' || key[i] > 'z'))
            {
                printf("Key with error %c (%d).\n", key[i], (int) key[i]);
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    } 
    else 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    
    
    //check if there is a duplicated letter in key
    if (check_duplicates(key) == false)
    {
        return 1;
    }
   
    
    //input plaintext
    string plaintext = get_string("planitext:  ");
    
    //length of plaintext and ciphertext
    int len = strlen(plaintext);

    // array to store the answer (ciphertext)
    char ciphertext[len];
    
    
    
    
    for (int i = 0, j = 0; i < len; i++)
    {
        // j - find the position of letter of plaintext in the key
        // with position j, le tetter to be used is the lower of key
        // if letter of plaintext are uppercase, so discount 32 to be uppercase too.
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            j = plaintext[i] - 'A';
            ciphertext[i] = tolower(key[j]) - 32;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            j = plaintext[i] - 'a';
            ciphertext[i] = tolower(key[j]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    
        
    }
    

    //print chipertext
    //if print all chiphertext with %s, like a string, an error occurs (?)
    
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
    
}


  

//check if there is a duplicated letter in key
//retur true if is ok
bool check_duplicates(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                return false;
            }
        }
    }
    return true;
}