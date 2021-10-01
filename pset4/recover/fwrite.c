#include <stdio.h>


char file_name[10];
int count = 0;
int main()
{
    //FILE *file = NULL;
    
    while(count<4)
    {
        // if(count == 5)
        // {
        //     fclose(file);
        // }
        
        sprintf(file_name, "x%03.f.txt", (float) count);
        //count++;
        FILE *file = fopen(file_name, "w");
        fprintf(file,"here %d\nnow\n", count);
        fclose(file);
        count++;
    }
    
    // *file = *fopen("teste1.txt", "w");
    // fprintf(file,"hereq\nnowq\n");
    // fclose(file);
    
}