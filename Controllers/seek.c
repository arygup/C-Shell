#include"../Headers/includes.h"


int finderr(char name[], char path[])
{
    char full_path[PATH_SIZE];
    if(path[strlen(path)-1] != '/')
        strcpy(&path[strlen(path)], "/\0");
    DIR *dir = opendir(path);
    if(dir == NULL) 
        return 0;
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) 
    {
        if(entry->d_name[0] == '.')     
            continue;
        struct stat file_stat;
        snprintf(full_path, sizeof(full_path), "%s%s", path, entry->d_name);
        int fg = 0, ll = strlen(full_path);
        for (int i = 1; i < ll; i++)
        {
            if(full_path[i] == '/' && full_path[i-1] == '/' && i+1 < ll)
            {
                fg++;
                full_path[i] = full_path[i+1];
            }
        }
        if(fg)
            full_path[ll-1] = '\0';
        if(stat(full_path, &file_stat) == -1) 
            continue;
        if(S_ISDIR(file_stat.st_mode))
            finderr(name, full_path);
        if(!strcmp(name, entry->d_name))
            printf("%s \n", full_path);
    }
}

int seek(char operation[])
{
    int len  = strlen(operation), d = 0, f = 0, e = 0, z = 0;
    for (int i = 0; i < len; i++)
    {
        if(operation[i] == '-')
        {
            if(len > i+1 && operation[i+1] == 'e')
            {
                e++;
                z = i+2;
            }
            if(len > i+1 && operation[i+1] == 'd')
            {
                d++;
                z = i+2;
            }
            if(len > i+1 && operation[i+1] == 'f')
            {
                f++;
                z = i+2;
            }
        }
    }
    if(f && d)
    {
        printf("both f and d cant be used together \n");
        return 0;
    }
    char output[TOKEN_SIZE], path[TOKEN_SIZE], name[TOKEN_SIZE];
    while(operation[z] == ' ' || operation[z] == 9)
        z++;
    int k = z+1;
    while(operation[k] != ' ' && operation[k] != 9)
    {
        k++;
        if(k > len-1)
            break;
    }
    strncpy(name, &operation[z], k-z);
    while(operation[k] == ' ' || operation[k] == 9)
        k++;
    // printf("%d %d %d\n", z, k, strlen(operation));
    // printf("%d %d %d\n", d, e, f);
    strcpy(output, &operation[k]);
    pathfinder(output, path);
    int len_path = strlen(path);
    // printf("path %s \n", output);
    // printf("called path ;%s; \n", path);
    // printf("actual name ;%s; \n", name);
    char *finder[PATH_SIZE], *ptr, pt[PATH_SIZE], full_path[TOKEN_SIZE], *ans[TOKEN_SIZE];
    int count = 0, stkptr = 0, an = 0;
    finder[0] = (char *)malloc(strlen(path) + 1);
    strcpy(finder[0], path);
    while(count >= 0)
    {
        strcpy(path, finder[count]);
        free(finder[count]);
        count--;
        // if(!strncmp(path, "/Volumes/", 9))
        //     continue;
        // printf("path ;%s; \n", path);
        DIR *dir = opendir(path);
        if(path[strlen(path)-1] != '/')
            strcpy(&path[strlen(path)], "/\0");
        if(dir == NULL) 
        {
            perror("Unable to open directory");
            fprintf(stderr, "Error code: %d\n", errno);
            printf("%s %d\n", path, count+1);
            continue;
        }
        struct dirent *entry;
        while((entry = readdir(dir)) != NULL) 
        {
            if(entry->d_name[0] == '.')     
                continue;
                //if(entry->d_name[1] == '.' || strlen(entry->d_name) < 2)
            struct stat file_stat;
            snprintf(full_path, sizeof(full_path), "%s%s", path, entry->d_name);
            int fg = 0, ll = strlen(full_path);
            for (int i = 1; i < ll; i++)
            {
                if(full_path[i] == '/' && full_path[i-1] == '/' && i+1 < ll)
                {
                    fg++;
                    full_path[i] = full_path[i+1];
                }
            }
            if(fg)
                full_path[ll-1] = '\0';
            if(stat(full_path, &file_stat) == -1) 
                continue;
            if(S_ISDIR(file_stat.st_mode))
            {
                count++;
                finder[count] = (char *)malloc(strlen(full_path)+1);
                strcpy(finder[count], full_path);
            }
            if(!strncmp(name, entry->d_name, strlen(name)))
            {
                if(S_ISDIR(file_stat.st_mode)) // f d 
                {
                    if(d == 1 || (d == 0 && f == 0))
                    {
                        ans[an] = (char *)malloc(strlen(full_path)+1);
                        strcpy(ans[an], full_path);
                        an++;
                    }
                }
                else if(((d == 0 && f == 0) || f == 1) && entry->d_name[strlen(name)] == '.')
                {
                    ans[an] = (char *)malloc(strlen(full_path)+1);
                    strcpy(ans[an], full_path);
                    an++;
                }
            }
            // printf("%s \n", full_path);
        }
        closedir(dir);
        // printf("%d ", count);
    }
    
    if(an == 0)
    {
        printf("no ans found \n");
        return 0;
    }
    if(e && an == 1)
    {
        strcpy(full_path, ans[0]);
        // printf(";%s; \n", full_path);
        // printf(";%s; \n", ans[0]);
        struct stat statbuf;
        if(stat(full_path, &statbuf) == -1) 
        {
            printf("stat err\n");
            free(ans[0]);
            return 0;
        }
        if(S_ISDIR(statbuf.st_mode)) 
        {
            if(access(full_path, X_OK) != 0) 
            {
                printf("The folder is not executable.\n");
                free(ans[0]);
                return 0;
            }
            snprintf(path, sizeof(path), "%s %s", "wrap", full_path);
            torun(path);
            free(ans[0]);
            return 0;
        }
        else if(access(full_path, R_OK) != 0) 
        {
            printf("The file is not readable.\n");
            free(ans[0]);
            return 0;
        }
    }
    for (int i = 0; i < an; i++)
    {
        printf("./%s \n", &ans[i][len_path]);
        free(ans[i]);
    }
    return 0;
}


