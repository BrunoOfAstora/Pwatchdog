#ifndef WD_H_H
#define WD_H_H
#define _OPEN_SYS
#define _GNU_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <syslog.h>

pid_t waitpid(pid_t pid, int *status_ptr, int options);
#define MAX_BUFFER_SIZE 1024

typedef struct{
    char filename[100];
    FILE *file;
    struct tm timestamp;
}LogFile;


#endif