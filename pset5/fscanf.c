#include <stdio.h>

int main(void)
{
    int count = 0;
    char *dir ="speller/dictionaries/large";
    FILE *file = fopen(dir, "r");
    if (!file)
    {
        printf("ops\n");
        return 1;
    }
    
    char word[46];
    

    while(fscanf(file, "%s", word) != EOF && count < 200000)
    {
        // fscanf(file, "%s", buffer);
        printf("%s\t%d\n", word, count);
        count++;
    }
    fclose(file);
    
    
    
}