#include "../Headers/includes.h"

int background(char operation[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("New process creation failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        // setpgid(0,0);
        char *argu[TOKENS], op[TOKENS][TOKEN_SIZE];
        for(int i = 0; i < TOKENS; i++) 
            memset(op[i], 0, TOKEN_SIZE);
        op[0][0] = operation[0];
        int len  = strlen(operation), j = 0, k = 0;
        for(int i=1; i<len; i++)
        {
            k++;
            if(operation[i] == ' ' || operation[i] == 9)
            {
                op[j][k] = '\0';
                // printf("%s  ", op[j]);
                j++;
                k = -1;
            }
            else
            {    
                op[j][k] = operation[i];
                op[j][k+1] = '\0';
            }
        }
        for (int i = 0; i < j; i++)
        {
            argu[i] = op[i];
        }
        argu[j] = NULL;
        
        if(execvp(argu[0], argu) < 0)
        {
            printf("shell: command not found: %s\n", op[0]);
            exit(12);
        }
        printf("running in bg");
        exit(12);
    }
    else if(acjobs < JOBS)
    {
        spid[acjobs] = pid;
        acjobs++;
        printf("pid: %d\n", pid);
    }
    return 1;
}