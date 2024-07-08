#include"../Headers/includes.h"

int iMan(char operation[])
{
    // inspo from https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c
    char buffer[1024], request[1024];
    int strong_open = 0, flggg = 0, n; 
    sprintf(request, "GET /?topic=%s&section=all HTTP/1.1\r\nHost: man.he.net\r\n\r\n", operation);
    // printf("%s\n", request);
    struct hostent *server = gethostbyname("man.he.net");
    if (server == NULL) 
    {
        printf("Error in DNS resolution\n");
        return 0;
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        printf("Error opening socket\n");
        return 0;
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        printf("Error connecting to server\n");
        close(sockfd);
        return 0;
    }
    if(write(sockfd, request, strlen(request)) < 0) 
    {
        printf("Error sending request\n");
        close(sockfd);
        return 0;
    }
    while ((n = read(sockfd, buffer, sizeof(buffer))) > 0) 
    {
        const char *ptr = buffer;
        while (*ptr && flggg == 0)
        {
            if (strncmp(ptr, "</STRONG>", 9) == 0) 
            {
                strong_open = 1;
                ptr += 9;
            } 
            else if (strncmp(ptr, "</PRE>", 6) == 0) 
            {
                if (strong_open == 1)
                {
                    flggg = 1;
                    break;
                }
                ptr += 6;
            } 
            else if (strong_open) 
            {
                putchar(*ptr);
                ptr++;
            } 
            else
                ptr++;
        }    
    }
    printf("\n");
    if(strong_open == 0) 
    {
        printf("Error no such command\n");
    }
    if(n < 0) 
    {
        printf("Error reading response\n");
    }
    close(sockfd);
    return 0;
}