#include"../Headers/includes.h"
int compare(char *a, char *b) 
{ 
    return strcmp(a, b);
} 
int listdirct(char path[], int show_hidden, int long_format) 
{
    DIR *dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Unable to open directory");
        fprintf(stderr, "Error code: %d\n", errno);
        printf("opendir \n");
        return 0;
    }
    struct dirent *entry;
    int num = 0;
    char output[50][TOKEN_SIZE];
    for(int i = 0; i < 50; i++) 
        memset(output[i], 0, TOKEN_SIZE);
    
    while((entry = readdir(dir)) != NULL) 
    {
        if (!show_hidden && entry->d_name[0] == '.') 
            continue;
        strcpy(output[num], entry->d_name);
        num++;
    }
    qsort(output, num, TOKEN_SIZE*sizeof(char), compare);
    for (int i = 0; i < num; i++)
    {
        char full_path[PATH_SIZE];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, output[i]);
        struct stat statbuf;
        if(stat(full_path, &statbuf) == -1) 
        {
            printf("stat err\n");
            continue;
        }
        if (long_format) 
        {
            printf("%c%s ", 
                S_ISDIR(statbuf.st_mode) ? 'd' :
                S_ISREG(statbuf.st_mode) ? '-' :
                S_ISLNK(statbuf.st_mode) ? 'l' :
                S_ISCHR(statbuf.st_mode) ? 'c' :
                S_ISBLK(statbuf.st_mode) ? 'b' :
                S_ISFIFO(statbuf.st_mode) ? 'p' : 
                S_ISSOCK(statbuf.st_mode) ? 's' : '?'
            );
            printf("%s %s %s %8ld ", 
                (statbuf.st_mode & S_IRUSR) ? "r" : "-",
                (statbuf.st_mode & S_IWUSR) ? "w" : "-",
                (statbuf.st_mode & S_IXUSR) ? "x" : "-",
                (long)statbuf.st_size
            );
            struct passwd *user_info = getpwuid(statbuf.st_uid);
            struct group *group_info = getgrgid(statbuf.st_gid);
            printf("%s %s ", user_info->pw_name, group_info->gr_name);
        }
        if(S_ISDIR(statbuf.st_mode)) 
            printf("%s%s%s", COLOR_DIR, output[i], COLOR_NORMAL);
        else if(statbuf.st_mode & S_IXUSR) 
            printf("%s%s%s", COLOR_EXEC, output[i], COLOR_NORMAL);
        else 
            printf("%s%s%s", COLOR_FILE, output[i], COLOR_NORMAL);
        printf("\n");
    }
    closedir(dir);
    return 0;
}


// void print_file_info(const char *filename, const struct stat *file_stat) 
// {
//     printf((S_ISDIR(file_stat->st_mode)) ? "d" : "-");
//     printf((file_stat->st_mode & S_IRUSR) ? "r" : "-");
//     printf((file_stat->st_mode & S_IWUSR) ? "w" : "-");
//     printf((file_stat->st_mode & S_IXUSR) ? "x" : "-");
//     printf((file_stat->st_mode & S_IRGRP) ? "r" : "-");
//     printf((file_stat->st_mode & S_IWGRP) ? "w" : "-");
//     printf((file_stat->st_mode & S_IXGRP) ? "x" : "-");
//     printf((file_stat->st_mode & S_IROTH) ? "r" : "-");
//     printf((file_stat->st_mode & S_IWOTH) ? "w" : "-");
//     printf((file_stat->st_mode & S_IXOTH) ? "x" : "-");
//     printf(" %hu", file_stat->st_nlink);
//     struct passwd *pw = getpwuid(file_stat->st_uid);
//     struct group *gr = getgrgid(file_stat->st_gid);
//     printf(" %s %s", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
//     printf(" %lld", (long long)file_stat->st_size);
//     char time_str[20];
//     strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat->st_mtime));
//     printf(" %s", time_str);
//     printf(" %s\n", filename);
// }
// int listdirct(char path[], int a, int l)
// {
//     DIR *dir = opendir(path);
//     if(dir == NULL) 
//     {
//         printf("opendir \n");
//         return 0;
//     }
//     struct dirent *entry;
//     while((entry = readdir(dir)) != NULL) 
//     {
//         if(!a && entry->d_name[0] == '.')     
//             continue;
//         char full_path[TOKEN_SIZE];
//         snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
//         struct stat file_stat;
//         if (stat(full_path, &file_stat) == -1) 
//         {
//             printf("stat \n");
//             continue;
//         }
//         if(l) 
//             print_file_info(entry->d_name, &file_stat);
//         else 
//             printf("%s\n", entry->d_name);
//     }
//     return 1;
// }

int peek(char operation[])
{
    int len = strlen(operation), l = 0, a = 0, z = 0;
    int i = len - 1;
    while (i >= 0 && (operation[i] == ' ' || operation[i] == '\t')) 
    {
        operation[i] = '\0'; 
        i--;
    }
    len  = strlen(operation);
    for (int i = 0; i < len; i++)
    {
        if(operation[i] == '-')
        {
            if(len > i+1 && operation[i+1] == 'a')
            {
                a++;
                z = i+1;
                if(len > i+2 && operation[i+2] == 'l')
                {
                    l++;
                    z++;
                }
            }
            if(len > i+1 && operation[i+1] == 'l')
            {
                l++;
                z = i+1;
                if(len > i+2 && operation[i+2] == 'a')
                {
                    a++;
                    z++;
                }
            }
        }
    }
    if(a > 1 || l > 1)
    {
        printf("Invalid command\n");
        return 0;
    }
    
    char output[TOKEN_SIZE], path[TOKEN_SIZE];
    // z++;
    z = strlen(operation) - 1;
    while(operation[z] != ' ' && operation[z] != 9 && z >= 0)
    {
        z--;
    }
    z++;
    // printf("%d \n", z);
    if(z == 1)
    {
        strcpy(output, "~\0");
    }
    else
    {
        strcpy(output, &operation[z]);
    }
    // printf("l %d a %d \n", l, a);
    // printf("%s \n", output);
    pathfinder(output, path);
    printf("actual path %s \n", path);
    listdirct(path, a, l);
        
    return 0;
}