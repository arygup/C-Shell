#include "../Headers/includes.h"

int bg(char operation[])
{
    int pid, flg = -1;
    pid = atoi(operation);
    // printf("pid: %d\n", pid);
    for (int i = 0; i < acjobs; i++)
    {
        if(spid[i] == pid)
        {
            flg = i;
            break;
        }
    }
    if(flg == -1)
    {
        printf("pid: %d does not exist\n", pid);
        return 1;
    }
    if(kill(pid, SIGCONT) < 0)
    {
        printf("Error in sending signal\n");
        return 1;
    }
    printf("Signal SIGCONT sent to %d\n", pid);
}
