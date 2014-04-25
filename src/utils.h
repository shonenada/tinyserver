#ifndef _UTILS
#define _UTILS

int getFileSize(int);
char* getCurrentTime();

#include <time.h>
#include "server_handler.h"

int getFileSize(int fd) {
   struct stat stat_struct;
   if(fstat(fd, &stat_struct) == -1)
      return -1;
   return (int)stat_struct.st_size;
}

char* getCurrentTime()
{
    time_t rawtime;
    struct tm * timeinfo = NULL;
    time(&rawtime);
    timeinfo = (struct tm *) localtime(&rawtime);
    return asctime(timeinfo);
}

#endif
