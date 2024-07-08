#include "../Headers/includes.h"

void promptUser() 
{
    char prompt[PATH_SIZE], hostname[USERNAME_SIZE], currDir[PATH_SIZE];
    struct passwd *p = getpwuid(getuid()); 
    gethostname(hostname, sizeof(hostname)); 
    getcwd(currDir, sizeof(currDir));
    if(strncmp(homee, currDir, strlen(homee)) == 0) 
        snprintf(prompt, PATH_SIZE, "<%s@%s:~%s> ", p->pw_name, hostname,&currDir[strlen(homee)]);
    else
        snprintf(prompt, PATH_SIZE, "<%s@%s:%s> ", p->pw_name, hostname, currDir);
    printf("%s", prompt);
    strcpy(historey, p->pw_dir);
}