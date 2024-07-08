#include"../Headers/includes.h"

int execute(char operation[])
{
    char *argu[TOKENS], op[TOKENS][TOKEN_SIZE], *token;
    for(int i = 0; i < TOKENS; i++) 
        memset(op[i], 0, TOKEN_SIZE);
    // op[0][0] = operation[0];
    // int len  = strlen(operation), j = 0, k = 0;
    // for(int i=1; i<len; i++)
    // {
    //     k++;
    //     if(operation[i] == ' ' || operation[i] == 9)
    //     {
    //         op[j][k] = '\0';
    //         // printf("%s  ", op[j]);
    //         j++;
    //         k = -1;
    //     }
    //     else
    //     {    
    //         op[j][k] = operation[i];
    //         op[j][k+1] = '\0';
    //     }
    // }
    // for (int i = 0; i < j; i++)
    // {
    //     argu[i] = &op[i][0];
    // }
    int idx = 0, tokenCount = 0;
    token = strtok(operation, " \t");
    while(token != NULL) 
    {
        tokenCount++;
        strcpy(op[idx++], token);
        argu[idx-1] = &op[idx-1][0];
        token = strtok(NULL, " \t");
        // printf("|%s|\n", argu[idx-1]);
    }
    argu[idx] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("New process creation failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        setpgid(pid, pid);
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        if (execvp(argu[0], argu) < 0)
        {
            printf("shell: command not found: %s\n", &op[0][0]);
            kill(pid, SIGTERM);
            return 0;
        }
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
    }
    else
    {
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, pid);
        int status;
        pid_t terminated_pid = waitpid(pid, &status, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpgid(0));
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
    }
    return 0;
}
