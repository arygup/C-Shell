#ifndef __INCLUDES_H_
#define __INCLUDES_H_

// standard libraries
#include <stdio.h>
#include <grp.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


#define PATH_SIZE 20000
#define USERNAME_SIZE 2000
#define COMMAND_SIZE 20000
#define TOKENS 200
#define TOKEN_SIZE 2000
#define LS_ENTITIES 10000
#define NAME_SIZE 2000
#define JOBS 2000


#define COLOR_NORMAL "\x1B[0m"
#define COLOR_DIR "\x1B[34m"
#define COLOR_EXEC "\x1B[32m"
#define COLOR_FILE "\x1B[33m"

pid_t shell_pid;
int acjobs;
pid_t spid[JOBS];
char homee[PATH_SIZE];
char prevhomee[PATH_SIZE];
char historey[PATH_SIZE];


#include "prompt.h"
#include "token.h"
#include "torun.h"
#include "proclore.h"
#include "pastevents.h"
#include "wrap.h"
#include "background.h"
#include "peek.h"
#include "seek.h"
#include "iMan.h"
#include "neonate.h"
#include "execute.h"
#include "pipes.h"
#include "activities.h"
#include "ping.h"
#include "bg.h"
#include "fg.h"
#include "redirection.h"



#endif
