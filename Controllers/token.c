#include"../Headers/includes.h"

int token(char input[], char output[][TOKEN_SIZE])
{
    int len  = strlen(input), j = 0, k = 0;
    FILE *file;
    char hfilepath[PATH_SIZE];
    snprintf(hfilepath, PATH_SIZE, "%s/%s", historey, "/history.txt");
    file = fopen(hfilepath, "a");
    if(!file) 
    {
        printf("Error opening history file.\n");
        return 0;
    }
    if(strcmp(input, "\n") != 0)
    {
        fputs(input, file);
    }
    // fputs("\n", file);
    fclose(file);
    if(len > 0 && input[len - 1] == '\n') 
        input[len - 1] = '\0';
    len  = strlen(input);
    output[0][0] = input[0];
    for(int i=1; i<len; i++)
    {
        k++;
        if(input[i] == '&')
        {
            output[j][k] = input[i];
            output[j][k+1] = '\0';
            j++;
            k = -1;
        }
        else if(input[i] == ';')
        {
            j++;
            k = 0;
            output[j][k] = input[i];
            output[j][k+1] = '\0';
        }
        // else if(input[i] == ' ' || input[i] == 9)
        // {
        //     output[j][k] = '\0';
        //     k--;
        // }
        else
        {    
            output[j][k] = input[i];
            output[j][k+1] = '\0';
        }
    }
    return j+1;
}