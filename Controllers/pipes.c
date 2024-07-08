#include"../Headers/includes.h"


int pipes(char input[])
{
    int in_backup = dup(STDIN_FILENO);
    int out_backup = dup(STDOUT_FILENO);
    int currentIn = dup(STDIN_FILENO);
    int len  = strlen(input), j = 0, k = 0;
    if(len > 0 && input[len - 1] == '\n') 
        input[len - 1] = '\0';
    len  = strlen(input);
    char output[TOKENS][TOKEN_SIZE];
    for (int i = 0; i < TOKENS; i++)
        memset(output[i], 0, TOKEN_SIZE);
    output[0][0] = input[0];
    for(int i=1; i<len; i++)
    {
        k++;
        if(input[i] == '|')
        {
            j++;
            k = -1;
            // output[j][k] = input[i];
            // output[j][k] = '\0';
        }
        else
        {    
            output[j][k] = input[i];
            output[j][k+1] = '\0';
        }
    }
    // for (int i = 0; i < j+1; i++)
    // {
    //     printf("%s\n", output[i]);
    // }
    // return 1;
    int ppes[j+1][2];
    for (int i = 0; i < j + 1; i++)
    {   
        pipe(ppes[i]);
        dup2(currentIn, STDIN_FILENO);
        if (i != j)
        {
            dup2(ppes[i][1], STDOUT_FILENO);
        } else {
            dup2(out_backup, STDOUT_FILENO);
        }
        torun(output[i]);
        close(ppes[i][1]);
        close(ppes[i + 1][0]);
        dup2(ppes[i][0], currentIn);
    }
    close(ppes[j][0]);
    close(currentIn);
    dup2(in_backup, STDIN_FILENO);
    dup2(out_backup, STDOUT_FILENO);
}