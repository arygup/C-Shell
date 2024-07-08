#include "../Headers/includes.h"

int fg(char operation[])
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
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    kill(pid, SIGCONT);
    if (tcsetpgrp(0, getpgid(pid))) 
    {
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        printf("no acess to terminal\n");
        return 0;
    }
    int status;
    waitpid(pid, &status, WUNTRACED);
    // tcsetpgrp purpose is to set the foreground process group id of a terminal, 
    // which is the process group of the last process that was moved to the foreground.
    tcsetpgrp(0, shell_pid);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return 0;
}
