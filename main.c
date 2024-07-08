#include "Headers/includes.h"


int main() 
{

    //initializeConstants();
    // childHandler();
    acjobs = 0;
    shell_pid = getpid();
    getcwd(homee, sizeof(homee));
    int tokens;
    while(1) 
    {
        char input[COMMAND_SIZE];
        memset(input, 0, COMMAND_SIZE);
        char tokenizedInput[TOKENS][TOKEN_SIZE];
        for (int i = 0; i < TOKENS; i++)
            memset(tokenizedInput[i], 0, TOKEN_SIZE);
        promptUser();
        fgets(input, sizeof(input), stdin);
        tokens = token(input, tokenizedInput);
        for (int i = 0; i < tokens; i++) 
            torun(tokenizedInput[i]);
            // printf("%s\n", tokenizedInput[i]);
    }
}

