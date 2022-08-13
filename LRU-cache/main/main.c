#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "models/node.h"
#include "models/message.h"
#include "filehandler/filehandler.h"
#include "doublylinkedlist/doublylinkedlist.h"
#include "hashmap/hashmap.h"

void init(Node **head, Node **tail, HashMap **map)
{
    *head = NULL;
    *tail = *head;
    *map = NULL;
}
Message *get(Node **head, Node **tail, HashMap **map, const char *sendername)
{
    if (*head && *tail && *map)
    {
        Node *node = obtain(*map, sendername);

        if (node)
        {
            Message *message = readMessage(node->FileName);

            if (message)
            {
                *head = selectNodeAndPrepend(*head, tail, node);
                return message;
            }
            printf("\nFailed to read message from database!");
            return NULL;
        }
        else
        {
            printf("\nNo message received from %s", sendername);
            return NULL;
        }
    }
    else
    {
        printf("\nLRU-cache Not initialized!");
    }
}
bool put(Node **head, Node **tail, HashMap **map, const char *sendername, const char *body)
{
    if (*head && *tail && *map)
    {

        Node *node = obtain(*map, sendername);

        if (node)
        {
            Message *message = newMessage(sendername, body);
            if (!writeMessage(message, node->FileName))
            {
                printf("\nFailed to replace message in database!");
                return false;
            }
            *head = selectNodeAndPrepend(*head, tail, node);
        }
        else
        {

            char encrypted[200];
            char filename[300];
            encryptString(sendername, encrypted);
            sprintf(filename, "%s.bin", encrypted);
            Message *message = newMessage(sendername, body);
            if (!writeMessage(message, filename))
            {
                printf("\nFailed to write message in database!");
                return false;
            }
            *head = prepend(*head, sendername, filename);
            *map = insert(*map, sendername, *head);
        }
        return true;
    }
    else
    {

        *map = newHashMap(5);
        char encrypted[200];
        char filename[300];
        encryptString(sendername, encrypted);
        sprintf(filename, "%s.bin", encrypted);
        Message *message = newMessage(sendername, body);
        if (!writeMessage(message, filename))
        {
            printf("\nFailed to write message in database!");
            return false;
        }
        *head = newNode(sendername, filename);
        *tail = *head;
        *map = insert(*map, sendername, *head);
        return true;
    }
}

int main()
{
    Node *head;
    Node *tail;
    HashMap *map;
    init(&head, &tail, &map);
    int ch = 0;
    do
    {
        printf("----------------------------------------------------------------------\n");
        printf("Most Recent Message!:\n");
        printList(head);
        printf("----------------------------------------------------------------------\n");
        printf("\nLRU-cache\n");
        printf("\n1.)Put Message\n2.)Get Message\n3.)Exit\n");
        printf("What do you want to do ?:");
        scanf("%d", &ch);
        getchar();
        switch (ch)
        {
        case 1:
        {
            char body[1000];
            char sendername[100];
            printf("\nEnter your name here:");
            fgets(sendername, 100, stdin);
            getchar();
            printf("\nEnter your message here:\n=>");
            fgets(body, 1000, stdin);
            getchar();
            if (put(&head, &tail, &map, sendername, body))
            {
                printf("\nMessage put successfully!");
            }
            else
            {
                printf("\nFailed to put message!");
            }
            break;
        }
        case 2:
        {
            char body[1000];
            char sendername[100];
            printf("\nEnter your name here:");
            fgets(sendername, 100, stdin);
            getchar();

            Message *message = get(&head, &tail, &map, sendername);
            if (message)
            {
                printf("-------------------------MESSAGE----------------------------\n");
                printMessage(message);
                printf("-------------------------THE END----------------------------\n");
            }
            else
            {
                printf("\nFailed to get message!");
            }
            break;
        }
        case 3:{
            printf("\nExit!!");
            break;
        }
        default:
        {
            printf("\nInvalid Entry please try again!!");
        }
        }
        getchar();
        system("cls");
    } while (ch != 3);
    destroyMap(map);
    destroyList(head);
    return 0;
}