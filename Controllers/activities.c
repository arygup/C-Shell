#include "../Headers/includes.h"

void PI(int pid, char cmdLine[], char state[]) 
{
    // inspired from https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
    if(pid <= 0)
    {
        strcpy(cmdLine, "0");
        return;
    }
    char procFileName[1000];
    snprintf(procFileName, sizeof(procFileName), "/proc/%d/status", pid);
    FILE *fp = fopen(procFileName, "r");
    if (fp == NULL) 
    {
        printf("Error opening status file\n");
        return;
    }
    while (fgets(cmdLine, sizeof(cmdLine), fp) != NULL) 
    {
        if (strstr(cmdLine, "State:") != NULL) 
        {
            sscanf(cmdLine, "State:\t%c", &state);
        }
    }
    fclose(fp);
    snprintf(procFileName, sizeof(procFileName), "/proc/%d/cmdline", pid);
    FILE *fp2 = fopen(procFileName, "r");
    if (fp2 == NULL) 
    {
        printf("Error opening cmdline file\n");
        return;
    }
    fgets(cmdLine, sizeof(cmdLine), fp2);
    fclose(fp2);
    if(state == 'R')
    {
        strcpy(state, "Running");
    }
    else
    {
        strcpy(state, "Stopped");
    }
}


int activities()
{
    for (int i = 0; i < acjobs - 1; i++) 
    {
        for (int j = i + 1; j < acjobs; j++) 
        {
            if (spid[i] > spid[j]) {
                int temp = spid[i];
                spid[i] = spid[j];
                spid[j] = temp;
            }
        }
    }
    for (int i = 0; i < acjobs; i++) 
    {
        char cmdLine[1024], state[1024];
        PI(spid[i], cmdLine, state);
        if(strncmp(cmdLine, "0", 1))
            printf("%d : %s - %s\n", spid[i], cmdLine, state);
    }
    return 0;
}

int exitcode(pid_t pid) 
{
    int status;
    char processName[256];
    siginfo_t info;
    info.si_pid = 0;
    if(waitid(P_PID, pid, &info, WEXITED | WNOHANG) == -1) 
    {
        // printf("waitid\n");
        return -1;
    }
    if(info.si_pid == 0) 
    {
        // printf("PID %d still running or not found.\n", pid);
        return -1;
    } 
    else if(info.si_code == CLD_EXITED) 
    {
        char commPath[256];
        snprintf(commPath, sizeof(commPath), "/proc/%d/comm", pid);
        FILE *commFile = fopen(commPath, "r");
        if (commFile != NULL) 
        {
            if(fgets(processName, sizeof(processName), commFile) != NULL) 
            {
                processName[strcspn(processName, "\n")] = '\0'; 
                printf("Process with PID %d (%s) exited with status %d.\n", pid, processName, info.si_status);
            }
            fclose(commFile);
        } 
        else 
        {
            printf("Process with PID %d exited with status %d.\n", pid, info.si_status);
        }
    } 
    return 0;
}
