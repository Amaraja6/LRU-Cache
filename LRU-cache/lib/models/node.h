#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#ifndef NODE_H
#define NODE_H
typedef struct Node Node;
struct Node
{
    char SenderName[100];
    char FileName[300];
    Node *Prev;
    Node *Next;
};

/*
    function used for creating a new node
    gets sendername and filename as parameters
    and creates a node by allocationg 50 bytes for each names
    returns the newly created node
*/
Node *newNode(const char *sendername, const char *filename);


/*
    function used for destroying a node
    gets node pointer as parameter and de allocated space for the node
    returns void
*/
void destroyNode(Node* node);
#endif