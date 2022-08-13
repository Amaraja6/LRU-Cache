#include "models/node.h"
Node *newNode(const char *sendername, const char *filename)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node)
    {
        strcpy(node->SenderName, sendername);
        strcpy(node->FileName, filename);
        node->Next = NULL;
        node->Prev = NULL;
    }
    return node;
}

void destroyNode(Node* node){
    if(node){
        if(node->Prev){
            free(node->Prev);
        }
        if(node->Next){
            free(node->Next);
        }
    }
    return;
}