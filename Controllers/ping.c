#include "../Headers/includes.h"

int ping(char operation[])
{
    char *token;
    int pid, sig, flg = -1;
    token = strtok(operation, " \t");
    if (token != NULL) 
    {
        pid = atoi(token);
    } 
    else 
    {
        printf("Enter valid pid\n");
        return 1;
    }
    token = strtok(NULL, " \t");
    if (token != NULL) 
    {
        sig = atoi(token);
    } 
    else 
    {
        printf("Enter valid  signal\n");
        return 1;
    }
    for (int i = 0; i < acjobs; i++)
    {
        if(spid[i] == pid)
        {
            flg = i;
            break;
        }
    }
    sig = sig%32;
    if(flg == -1)
    {
        printf("pid: %d does not exist\n", pid);
        return 1;
    }
    if(kill(pid, sig) < 0)
    {
        printf("Error in sending signal\n");
        return 1;
    }
    printf("Signal %d sent to %d\n", sig, pid);
}
