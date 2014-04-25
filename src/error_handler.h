#ifndef _ERROR_HANDLER
#define _ERROR_HANDLER

#include "settings.h"
#include "server_handler.h"

#define ERROR_PAGE_404_OK (open(ERROR_PAGE_404, O_RDONLY, 0) != -1)

void errorHandler(int, int);

void errorHandler(int sockfd, int code)
{
    int fd, length;
    char* ptr = NULL;

    switch(code)
    {
        case 404:

            if(ERROR_PAGE_404_OK)
                sendResource(ERROR_PAGE_404, sockfd, 1);
            else
                send(sockfd, "Page Not Found!", 15, 0);

        break;

        case 500:
            send(sockfd, "Server Interval Error", 20, 0);
        break;
    }
}

#endif
