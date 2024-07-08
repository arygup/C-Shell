#include"../Headers/includes.h"

void pathfinder(char arg[], char buffer[]) 
{
    if(arg[0] == '/') 
    {
        strcpy(buffer, arg);
        return;
    }
    else if(arg[0] == '-') 
    {
        strcpy(buffer, prevhomee);
        if(!strlen(buffer))
            strcpy(buffer, homee);
        return;
    }
    else if(arg[0] == '.' && arg[1] == '.') 
    {
        char cwd[PATH_SIZE];
        getcwd(cwd, sizeof(cwd));
        int l = strlen(cwd), z = 0;
        for(int i = 0; i < l; i++)
            if(cwd[i] == '/') 
                z = i;
        // printf("%d %d\n", z, l);
        strncpy(buffer, cwd, z);
        // if(z == 0)
        // {
        //     strcpy(buffer, "/\0");
        //     return;
        // }
        strcpy(&buffer[z], &arg[2]);
        printf("%s\n", buffer);
        return;
    }
    else if(arg[0] == '.' && arg[1] == '/')
    {
        char cwd[PATH_SIZE];
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, &arg[1]);
        strcpy(buffer, cwd);
    }
    else if(arg[0] == '.')
    {
        char cwd[PATH_SIZE];
        getcwd(cwd, sizeof(cwd));
        strcpy(buffer, cwd);
        return;
    }
    else if(arg[0] == '~') 
    {
        strcpy(buffer, homee);
        if(arg[1] == '/') 
        {
            strcat(buffer, "/");
            int idx = 2;
            int bufferIdx = strlen(buffer);
            while(arg[idx] != '\0') 
                buffer[bufferIdx++] = arg[idx++];
            buffer[bufferIdx] = '\0';
        }
        return;
    } 
    else 
    {
        char cwd[PATH_SIZE];
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, arg);
        strcpy(buffer, cwd);
        return;
    }
}
int wrap(char operation[])
{
    int len  = strlen(operation), j = 0, k = 0;
    char output[50][TOKEN_SIZE];
    for(int i = 0; i < 50; i++) 
        memset(output[i], 0, TOKEN_SIZE);
    output[0][0] = operation[0];
    // printf("%s\n",operation);
    for(int i=1; i<len; i++)
    {
        k++;
        if(operation[i] == ' ' || operation[i] == 9)
        {
            output[j][k] = '\0';
            // printf("%s  ", output[j]);
            j++;
            k = -1;
        }
        else
        {    
            output[j][k] = operation[i];
            output[j][k+1] = '\0';
        }
    }
    for (int i = 0; i < j+1; i++)
    {
        // printf("%s\n", output[i]);
        char absoluteDir[PATH_SIZE];
        pathfinder(output[i], absoluteDir);
        printf("%s\n", absoluteDir);
        char cwd[PATH_SIZE];
        getcwd(cwd, sizeof(cwd));
        if(chdir(absoluteDir) == -1) 
        {
            printf("Error in chdir \n");
            return 0;
        }
        strcpy(prevhomee, cwd);
    }
    return 0;
}