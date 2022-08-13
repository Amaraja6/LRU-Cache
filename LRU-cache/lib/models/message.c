#include "message.h"
Message *newMessage(const char *sendername, const char *body)
{
    Message *message = (Message *)malloc(sizeof(Message));
    if (message)
    {
        strcpy(message->SenderName, sendername);
        strcpy(message->Body, body);
        const time_t ref = time(NULL);
        message->TimeAndDate = localtime(&ref);
    }
    return message;
}

void destroyMessage(Message *message)
{
    if (message)
    {
        if (message->TimeAndDate)
            free(message->TimeAndDate);
    }
    return;
}
void printMessage(Message *message)
{
    if (message)
    {
        printf("\nDate: %d - %d - %d", message->TimeAndDate->tm_mday,
               message->TimeAndDate->tm_mon + 1,
               message->TimeAndDate->tm_year + 1900);
        printf("\nTime: %d : %d : %d", message->TimeAndDate->tm_hour,
               message->TimeAndDate->tm_min,
               message->TimeAndDate->tm_sec);
        printf("\nSender name: %s", message->SenderName);
        printf("\nBody: %s", message->Body);
    }
}