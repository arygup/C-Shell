#include"../Headers/includes.h"

void die(const char *s) 
{
    // perror(s);
    exit(1);
}

void disableRawMode(struct termios *orig_termios) 
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode(struct termios *orig_termios) 
{
    if (tcgetattr(STDIN_FILENO, orig_termios) == -1) 
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = *orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) 
        die("tcsetattr");
}

int neonate(int time_arg) 
{
    // insp from tut
    if (time_arg <= 0) 
    {
        printf("Invalid time_arg. Please provide a positive integer.\n");
        return 1; 
    }
    struct termios orig_termios;
    char c;
    int pid;
    enableRawMode(&orig_termios);

    pid = fork();
    if (pid < 0) 
    {
        printf("Error in fork\n");
        disableRawMode(&orig_termios);
        return 1; 
    } 
    else if (pid == 0) 
    {
        char line[NAME_SIZE], *token;
        long int ped = 0;
        while(1)
        {
            FILE *stfl = fopen("/proc/loadavg", "r");
            if (stfl == NULL)
            {  
                printf("file not opening\n");
                exit(1);
            }
            memset(line, 0, sizeof(line));
            if(fgets(line, NAME_SIZE, stfl) != NULL)
            {
                ped = 0;
                token = strtok(line, " ");
                while(token != NULL)
                {
                    ped = atoi(token);
                    token = strtok(NULL, " ");
                }
                printf("%lld\n", ped);
            }
            sleep(time_arg);
            fclose(stfl);
        }
        exit(0);
    } 
    else 
    {
        while(1)
        {
            struct timeval tv;
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            int inp = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
            if(inp > 0) 
            {
                if(read(STDIN_FILENO, &c, 1) == 1) 
                {
                    if (c == 'x') 
                    {
                        printf("terminating the printing\n");
                        if (kill(pid, SIGKILL) != 0) 
                        {
                            printf("Error in kill\n");
                            disableRawMode(&orig_termios);
                            return 1; 
                        }
                        disableRawMode(&orig_termios);
                        return 0; 
                    }
                }
            }
        }
    }
    disableRawMode(&orig_termios);
    return 0;
}