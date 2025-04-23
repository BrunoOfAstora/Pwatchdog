#ifndef WATCHDOG_MAIN_HEADER_H
#define WATCHDOG_MAIN_HEADER_H
#define _OPEN_SYS

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status_ptr, int options);

typedef struct{
	char filename[100];
	FILE *file;
	struct tm timestamp;
}LogFile;

#endif