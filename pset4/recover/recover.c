#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
  
int main(int argc, char *argv[])
{
    //checks usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    // try to open the source file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Unable to open %s.\n", argv[1]);
        return 1;
    }

    BYTE bytes[512];

    //initialize the variables
    // count is -1 to sum 1 in the very first to stay == 000.jpeg
    int count = -1;
    bool file_opened = false;
    char file_name[9];

    // read the 512 bytes of file source
    while (fread(bytes, sizeof(BYTE), 512, file))
    {
        //check if there is a .jpg signature
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
        {
          
            //now that there is a signature, file is opened and will be written or appended to it.
            file_opened = true;
            
            //define the file name
            count++;
            sprintf(file_name, "%03.f.jpg", (float) count);
            
            //open a new destination file to write
            FILE *destination = fopen(file_name, "w");
            if (destination == NULL)
            {
                fclose(file);
                return 1;
            }
            //write the bytes
            fwrite(bytes, sizeof(BYTE), 512, destination);
            fclose(destination);

        }
        else
        {
            if (file_opened)
            {
                //write(append) the bytes only when there was a signature
                FILE *destination = fopen(file_name, "a");
                fwrite(bytes, sizeof(BYTE), 512, destination);
                fclose(destination);
            }
        }
    }
    fclose(file);
}