#include"../Headers/includes.h"

int pastevents(char operation[])
{
    char hfilepath[PATH_SIZE];
    snprintf(hfilepath, PATH_SIZE, "%s/%s", historey, "/history.txt");
    if(strlen(operation) && !strcmp(operation, "purge"))
    {
        if (remove(hfilepath) != 0) 
            printf("not able to purge.\n");
        else 
            return 1;
    }
    FILE *hf = fopen(hfilepath, "r+");
    if(hf == NULL) 
    {
        printf("No history \n");
        return 1;
    }
    fseek(hf, 0, SEEK_END);
    long file_size = ftell(hf);

    char buffer[COMMAND_SIZE], out[50][TOKEN_SIZE], ogcmd[TOKEN_SIZE], runcmd[TOKEN_SIZE];
    memset(ogcmd, 0, TOKEN_SIZE);
    memset(runcmd, 0, TOKEN_SIZE);
    for(int i = 0; i < 50; i++) 
        memset(out[i], 0, TOKEN_SIZE);
    int ltr = 15, lr = 0, nnn = 0;
    for (long i = file_size - 1; i >= 0 && lr < ltr; i--) 
    {
        fseek(hf, i, SEEK_SET);
        int c = fgetc(hf);
        if (c == '\n') 
        {
            nnn++;
            if(nnn <= 2)
            {
                // printf("%d %s\n", nnn, buffer);
                strcpy(ogcmd, buffer);
                memset(buffer, 0, sizeof(buffer));
                continue;
            }
            if(lr == 1)
            {
                if(strcmp(out[0], buffer) == 0)
                {
                    memset(buffer, 0, sizeof(buffer));
                    continue;
                }
            }
            strcpy(out[lr], buffer);
            lr++;
            memset(buffer, 0, sizeof(buffer));
        } 
        else 
        {
            memmove(buffer + 1, buffer, sizeof(buffer) - 1);
            buffer[0] = c;
        }
    }
    if(lr == 0)
    {
        fclose(hf);
        if (remove(hfilepath) != 0) 
            printf("not able to purge.\n");
        else 
            return 1;
    }
    if(lr < ltr && lr != 0)
    {
        strcpy(out[lr], buffer);
        lr++;
    }
    if(!strlen(operation))
        for (int i = 0; i < lr; i++)
            printf("%s \n", out[i]);
    char tokenized[TOKENS][TOKEN_SIZE];
    int tokn, flgg = 0;
    if(strlen(operation) && !strncasecmp(operation, "execute", 7))
    {
        if(lr >= atoi(&operation[7]))
        {
            // printf("%d %d\n", atoi(&operation[7]),lr);
            strcpy(runcmd, out[atoi(&operation[7])]);
            for (int i = 0; i < TOKENS; i++)
                memset(tokenized[i], 0, TOKEN_SIZE);
            tokn = token(out[atoi(&operation[7])], tokenized);
            for (int i = 0; i < tokn; i++) 
            {
                torun(tokenized[i]);
                // printf("%s\n", tokenized[i]);
            }
            flgg++;
        }
        else 
            printf("command not found, only %d commands availaible you enetered %d\n", lr, atoi(&operation[7]));
    }
    int result = ftruncate(fileno(hf), 0);
    if (result != 0) {
        perror("Error truncating file");
        fclose(hf);
        return 1;
    }
    fclose(hf);
    for (int i = 0; i < TOKENS; i++)
        memset(tokenized[i], 0, TOKEN_SIZE);
    tokn = token(ogcmd, tokenized);
    FILE *hhs = fopen(hfilepath, "r+");
    for(int i = lr-1; i >= 0; i--)
    {
        fputs(out[i], hhs);
        fputs("\n", hhs);
    }
    if(tokn > 1)
    {
        for (int i = 0; i < tokn; i++) 
        {
            int xx = 0;
            while(tokenized[i][xx] == ' ' || tokenized[i][xx] == ';' || tokenized[i][xx] == 9)
                xx++;
            if(strlen(tokenized[i]) > 1 && strncasecmp(&tokenized[i][xx], "pastevents", 10))
            {
                fputs(tokenized[i], hhs);
                fputs(" ;", hhs);
            }
        }
    }
    if(flgg)
    {
        fputs(runcmd, hhs);
        fputs(" ;", hhs);   
    }
    fputs("\n", hhs);
    fclose(hhs);
    return 0;
}


