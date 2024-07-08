#include"../Headers/includes.h"

int redirection(char operation[])
{
    int loc1 = 0, loc2 = 0, loc3 = 0, flg2 = 0, flg1 = 0, flg3 = 0, lc = 0;
    int len = strlen(operation);
    int fc = len;
    for(int i=0; i<len; i++)
    {
        if(operation[i] == '>')
        {
            if(i+1<len && operation[i+1] == '>')
            {
                flg3 += 1;
                loc3 = i+1;
                fc = i;
            }
            else if(i-1>=0 && operation[i-1] != '>')
            {
                flg2 += 1;
                loc2 = i;
                fc = i;
            }
        }
        else if(operation[i] == '<')
        {
            flg1 += 1;
            loc1 = i;
            lc = i;
        }
    }
    if(flg2 + flg3 > 1 || flg1 > 1)
    {
        printf(" multiple redirections not allowed\n");
        return 0;
    }
    char ip[PATH_SIZE], op[PATH_SIZE], jkk[PATH_SIZE], jkkk[PATH_SIZE], opp[COMMAND_SIZE];
    memset(ip, 0, PATH_SIZE);
    memset(op, 0, PATH_SIZE);
    memset(jkk, 0, PATH_SIZE);
    memset(jkkk, 0, PATH_SIZE);
    memset(opp, 0, PATH_SIZE);
    int inputFile;
    int outputFile;
    int out_backup;
    int in_backup;
    out_backup = dup(STDOUT_FILENO);
    in_backup = dup(STDIN_FILENO);
    int idx = 0;
    if(flg1)
    {
        loc1++;
        while(operation[loc1] == ' ' || operation[loc1] == '\t')
        {
            loc1++;
        }
        while(operation[loc1] != ' ' && operation[loc1] != '\t' && loc1 < len)
        {
            ip[idx] = operation[loc1];
            idx++;
            loc1++;
        }
        ip[loc1] = '\0';
        pathfinder(ip, jkk);
        // printf("%s\n", jkk);
        inputFile = open(jkk, O_RDONLY);
        if(!inputFile) 
        {
            printf("input file was not found");
            return 0;
        }
        if(dup2(inputFile, STDIN_FILENO) == -1) 
        {
            printf("unable to redirect input\n");
            return 0;
        }
    }
    idx = 0;
    if(flg2)
    {
        loc2++;
        while(operation[loc2] == ' ' || operation[loc2] == '\t')
        {
            loc2++;
        }
        while(operation[loc2] != ' ' && operation[loc2] != '\t' && loc2 < len)
        {
            op[idx] = operation[loc2];
            idx++;
            loc2++;
        }
        op[loc2] = '\0';
        pathfinder(op, jkkk);
        outputFile = open(jkkk, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (!outputFile) 
        {
            printf("output file was not found \n");
            return 0;
        }
        if (dup2(outputFile, STDOUT_FILENO) == -1) 
        {
            printf("unable to redirect output\n");
            return 0;
        }
    }
    else if (flg3) 
    {
        loc3++;
        while(operation[loc3] == ' ' || operation[loc3] == '\t')
        {
            loc3++;
        }
        while(operation[loc3] != ' ' && operation[loc3] != '\t' && loc3 < len)
        {
            op[idx] = operation[loc3];
            idx++;
            loc3++;
        }
        op[loc3] = '\0';
        pathfinder(op, jkkk);
        outputFile = open(jkkk, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (!outputFile) 
        {
            printf("output file was not found \n");
            return 0;
        }
        if (dup2(outputFile, STDOUT_FILENO) == -1) 
        {
            printf("unable to redirect output\n");
            return 0;
        }
    }
    strncpy(opp, operation, fc);
    opp[fc] = '\0';
    for (int i = lc; i < loc1; i++)
    {
        opp[i] = ' ';
    }
    // printf("|%s|\n", opp);
    torun(opp);
    dup2(in_backup, STDIN_FILENO);
    dup2(out_backup, STDOUT_FILENO);
    return 0;
}