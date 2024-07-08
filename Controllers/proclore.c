#include"../Headers/includes.h"

int proclore(char operation[])
{
    int p = shell_pid;
    if(strlen(operation))
        p = atoi(operation);
    char tempProc[1000] = {'\0'}, exec[1000] = {'\0'};
    sprintf(tempProc, "/proc/%d/status", p);
    sprintf(exec, "/proc/%d/exe", p);
    FILE *fp = fopen(tempProc, "r");
    FILE *fp2 = fopen(exec, "r");
    if(fp == NULL)
    {
        printf("%s\n", tempProc);
        printf("file not opened\n");
        return 0;
    }
    char line[256];     
    printf("pid - %d\n", p);
    while (fgets(line, sizeof(line), fp)) 
    	if(strstr(line, "Name:") || strstr(line, "State:") || strstr(line, "PPid:") ||  strstr(line, "VmSize:"))         
    		printf("%s", line);         
    pid_t process_group = getpgid(p);     
    printf("Process Group: %d\n", process_group);        
    if(fp2 == NULL)
    {
        printf("%s\n", exec);
        printf("file not opened\n");
        return 0;
    }
    char executable_path[PATH_SIZE];   
    ssize_t exe_path_length = readlink(exec, executable_path, sizeof(executable_path) - 1);     
    if(exe_path_length != -1) 
    {         
    	executable_path[exe_path_length] = '\0';         
    	printf("Executable Path: %s\n", executable_path);     
    } 
    else    
    	printf("No executable path found \n");     
    return 0;
}

