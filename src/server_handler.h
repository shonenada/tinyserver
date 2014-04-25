#ifndef _SERVER_HANDLER
#define _SERVER_HANDLER

/** Send server information to client **/
void sendHTTPInfo(int);

/** Send HTTP status code to client **/
void sendHTTPCode(int, int);

void parse(char*, char*, int);
void sendResource(char*, int, int);
void handleConnection(int, struct sockaddr_in*);

#include "utils.h"
#include "http_codes.h"
#include "http_methods.h"
#include "error_handler.h"

/** Send server information to client **/
void sendHTTPInfo (int sockfd) {
    send(sockfd, "Server: Simple Server\r\n\r\n", 25, 0);
}

/** Send HTTP status code to client **/
void sendHTTPCode(int sockfd, int code) {
    char* response = (char*) malloc(sizeof(char) * 50);
    strcpy(response, "HTTP/1.1 ");

    char* infor = (char*) malloc(sizeof(char) * 100);

    switch (code) {
        case 100: 
            response = strcat(response, "100 ");
            response = strcat(response, CODE_100);
        break;

        case 101:
            response = strcat(response, "101 ");
            response = strcat(response, CODE_101);
        break;

        case 200:
            response = strcat(response, "200 ");
            response = strcat(response, CODE_200);
        break;

        case 201:
            response = strcat(response, "201 ");
            response = strcat(response, CODE_201);
        break;

        case 202:
            response = strcat(response, "202 ");
            response = strcat(response, CODE_202);
        break;

        case 203:
            response = strcat(response, "203 ");
            response = strcat(response, CODE_203);
        break;

        case 204:
            response = strcat(response, "204 ");
            response = strcat(response, CODE_204);
        break;

        case 205:
            response = strcat(response, "205 ");
            response = strcat(response, CODE_205);
        break;

        case 206:
            response = strcat(response, "206 ");
            response = strcat(response, CODE_206);
        break;

        case 300:
            response = strcat(response, "300 ");
            response = strcat(response, CODE_100);
        break;

        case 301:
            response = strcat(response, "301 ");
            response = strcat(response, CODE_301);
        break;

        case 302:
            response = strcat(response, "302 ");
            response = strcat(response, CODE_302);
        break;

        case 303:
            response = strcat(response, "302 ");
            response = strcat(response, CODE_302);
        break;

        case 304:
            response = strcat(response, "304 ");
            response = strcat(response, CODE_304);
        break;

        case 305:
            response = strcat(response, "305 ");
            response = strcat(response, CODE_305);
        break;

        case 306:
            response = strcat(response, "306 ");
            response = strcat(response, CODE_306);
        break;

        case 307:
            response = strcat(response, "307 ");
            response = strcat(response, CODE_307);
        break;

        case 400:
            response = strcat(response, "400 ");
            response = strcat(response, CODE_400);
        break;

        case 401:
            response = strcat(response, "401 ");
            response = strcat(response, CODE_401);
        break;

        case 402:
            response = strcat(response, "402 ");
            response = strcat(response, CODE_402);
        break;

        case 403:
            response = strcat(response, "403 ");
            response = strcat(response, CODE_403);
        break;

        case 404:
            response = strcat(response, "404 ");
            response = strcat(response, CODE_404);
        break;

        case 405:
            response = strcat(response, "405 ");
            response = strcat(response, CODE_405);
        break;

        case 406:
            response = strcat(response, "406 ");
            response = strcat(response, CODE_406);
        break;

        case 407:
            response = strcat(response, "407 ");
            response = strcat(response, CODE_407);
        break;

        case 408:
            response = strcat(response, "408 ");
            response = strcat(response, CODE_408);
        break;

        case 409:
            response = strcat(response, "409 ");
            response = strcat(response, CODE_409);
        break;

        case 410:
            response = strcat(response, "410 ");
            response = strcat(response, CODE_410);
        break;

        case 411:
            response = strcat(response, "411 ");
            response = strcat(response, CODE_411);
        break;

        case 412:
            response = strcat(response, "412 ");
            response = strcat(response, CODE_412);
        break;

        case 413:
            response = strcat(response, "413 ");
            response = strcat(response, CODE_413);
        break;

        case 414:
            response = strcat(response, "414 ");
            response = strcat(response, CODE_414);
        break;

        case 415:
            response = strcat(response, "415 ");
            response = strcat(response, CODE_415);
        break;

        case 416:
            response = strcat(response, "416 ");
            response = strcat(response, CODE_416);
        break;

        case 417:
            response = strcat(response, "417 ");
            response = strcat(response, CODE_417);
        break;

        case 500:
            response = strcat(response, "500 ");
            response = strcat(response, CODE_500);
        break;

        case 501:
            response = strcat(response, "501 ");
            response = strcat(response, CODE_501);
        break;

        case 502:
            response = strcat(response, "502 ");
            response = strcat(response, CODE_502);
        break;

        case 503:
            response = strcat(response, "503 ");
            response = strcat(response, CODE_503);
        break;

        case 504:
            response = strcat(response, "504 ");
            response = strcat(response, CODE_504);
        break;
        
        case 505:
            response = strcat(response, "505 ");
            response = strcat(response, CODE_505);
        break;

        default:
        break;
    }

    response = strcat(response, "\r\n");
    send (sockfd, response, strlen(response), 0);
    sendHTTPInfo(sockfd);

    errorHandler(sockfd, code);
}

void parse(char* request, char* ptr, int sockfd) {

    if(strncmp(request, "OPTIONS ", 8) == 0)
    {
        ptr = request + 8;
        HTTP_OPTIONS(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "GET ", 4) == 0)
    {
        ptr = request + 4;
        HTTP_GET(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "HEAD ", 5) == 0)
    {
        ptr = request + 5;
        HTTP_HEAD(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "POST ", 5) == 0)
    {
        ptr = request + 5;
        HTTP_POST(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "PUT ", 4) == 0)
    {
        ptr = request + 4;
        HTTP_PUT(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "DELETE ", 7) == 0)
    {
        ptr = request + 7;
        HTTP_DELETE(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "TRACE ", 6) == 0)
    {
        ptr = request + 6;
        HTTP_TRACE(request, ptr, sockfd);
        return ;
    }

    if(strncmp(request, "CONNECT ", 8) == 0)
    {
        ptr = request + 8;
        HTTP_CONNECT(request, ptr, sockfd);
        return ;
    }
    
    sendHTTPCode(sockfd, 405);

}

void sendResource (char* resource, int sockfd, int isError) {

    int fd, length;
    unsigned char* ptr;

    // open file.
    fd = open(resource, O_RDONLY, 0);

    // fd == -1 means there is no file.
    if (fd == -1) {
        if(!isError)
            sendHTTPCode(sockfd, 404);
    }
    else {
        if ((length = getFileSize(fd)) == -1) {
            exit(1);
        }
        if ((ptr = (unsigned char *) malloc(length)) == NULL) {
            exit(1);
        }
        if(!isError)
            sendHTTPCode(sockfd, 200);

        read (fd, ptr, length);
        send (sockfd, ptr, length, 0);
        free (ptr);
    }
    close(fd);
}

void handleConnection (int sockfd, struct sockaddr_in* client_addr_ptr) {

    unsigned char *ptr = NULL, request[500];

    int length = recv(sockfd, request, 500, 0);

    ptr = strstr(request, " HTTP/");

    if (ptr == NULL) {
        sendHTTPCode (sockfd, 400);
    }
    else {
        *ptr = 0;
        ptr = NULL;
        parse (request, ptr, sockfd);

    }
    shutdown (sockfd, SHUT_RDWR);
}

#endif
