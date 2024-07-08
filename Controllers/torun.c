#include "../Headers/includes.h"


int checker(char operation[], char symb)
{
    int len = strlen(operation);
    for(int i=0; i<len; i++)
        if(operation[i] == symb)
            return 1;
    return 0;
}
int checker2(char operation[], char symb[])
{
    int len = strlen(operation);
    for(int i=0; i<len; i++)
        if(operation[i] == symb[0])
            if(operation[i] == symb[1])
                return 1;
    return 0;
}

int torun(char operation[])
{
    for (int i = 0; i < acjobs; i++)
    {
        exitcode(spid[i]);
        // printf("pid: %d\n", spid[i]);
    }
    while(operation[0] == ' ' || operation[0] == ';' || operation[0] == 9)
    {
        char op[TOKEN_SIZE];
        strcpy(op, &operation[1]);
        strcpy(operation, op);
    }
    if(!strlen(operation))
        return 0;
    if (checker(operation, '>') || checker(operation, '<') || checker2(operation, ">>"))
    {
        redirection(operation);
        return 1;
    }
    else if (checker(operation, '|'))
    {
        pipes(operation);
        return 1;
    }
    else if (checker(operation, '&'))
    {
        background(operation);
        return 1;
    }
    else if(!strncasecmp(operation, "pwd", 3))
    {
        char cur[PATH_SIZE];
        getcwd(cur, sizeof(cur));
        printf("%s\n", cur);
    }
    else if(!strncasecmp(operation, "wrap", 4))
    {
        if(operation[4] == ' ' || operation[4] == 9 || operation[4] == '\0')
        {
            wrap(&operation[5]);
        }
    }
    else if(!strncasecmp(operation, "peek", 4))
    {
        if(operation[4] == ' ' || operation[4] == 9 || operation[4] == '\0')
        {
            peek(&operation[5]);
        }
    }
    else if(!strncasecmp(operation, "ping", 4))
    {
        if(operation[4] == ' ' || operation[4] == 9 || operation[4] == '\0')
        {
            ping(&operation[5]);
        }
    }
    else if(!strncasecmp(operation, "iman", 4))
    {
        if(operation[4] == ' ' || operation[4] == 9 || operation[4] == '\0')
        {
            iMan(&operation[5]);
        }
    }
    else if(!strncasecmp(operation, "bg", 2))
    {
        if(operation[2] == ' ' || operation[2] == 9 || operation[2] == '\0')
        {
            // printf("bg");
            bg(&operation[3]);
        }
    }
    else if(!strncasecmp(operation, "fg", 2))
    {
        if(operation[2] == ' ' || operation[2] == 9 || operation[2] == '\0')
        {
            // printf("fg");
            fg(&operation[3]);
        }
    }
    else if(!strncasecmp(operation, "seek", 4))
    {
        if(operation[4] == ' ' || operation[4] == 9)
        {
            seek(&operation[5]);
        }
    }
    else if(!strncasecmp(operation, "proclore", 8))
    {
        if(operation[8] == ' ' || operation[8] == 9 || operation[8] == '\0')
        {
            proclore(&operation[9]);
        }
    }
    else if(!strncasecmp(operation, "neonate -n", 10))
    {
        if(operation[10] == ' ' || operation[10] == 9 || operation[10] == '\0')
        {
            // printf("neonate -n %d\n", atoi(&operation[11]));
            neonate(atoi(&operation[11]));
        }
    }
    else if(!strncasecmp(operation, "pastevents", 10))
    {
        if(operation[10] == ' ' || operation[10] == 9 || operation[10] == '\0')
        {
            pastevents(&operation[11]);
        }
    }
    else if (!strncasecmp(operation, "clear", 5))
    {
        printf("\033[H\033[J");
    }
    else if (!strncasecmp(operation, "activities", 10))
    {
        activities();
    }
    else if (!strncasecmp(operation, "sleep", 5)) // impliment checker for sleep 
    {
        if(atoi(&operation[5]) > 2)
        {
            char prmt[TOKEN_SIZE];
            char hname[USERNAME_SIZE];
            struct passwd *pp = getpwuid(getuid()); 
            gethostname(hname, sizeof(hname)); 
            snprintf(prmt, TOKEN_SIZE, "<%s@%s:%s %d> ", pp->pw_name, hname,"sleeping seconds: ", atoi(&operation[5]));
            printf("%s \n", prmt);
            sleep(atoi(&operation[5]));
        }
        else
            sleep(atoi(&operation[5]));
    }
    // else if (!strncasecmp(operation, "echo", 4))
    // {
    //     if(operation[4] == ' ' || operation[4] == 9 || operation[4] == '\0')
    //     {
    //         printf("%s \n", &operation[5]);
    //     }
    // }
    else
    {
        // printf("shell: %s\n", operation);
        strcat(operation, " ");
        execute(operation);
    } 
    return 1;
}