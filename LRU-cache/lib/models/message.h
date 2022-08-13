#include <time.h>
#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_SENDER_NAME 50
#define MAX_BODY 1000
typedef struct Message Message;
struct Message
{
    char SenderName[MAX_SENDER_NAME];
    struct tm *TimeAndDate;
    char Body[MAX_BODY];
};
Message *newMessage(const char *sendername, const char *body);
void destroyMessage(Message *message);
void printMessage(Message* message);
#endif