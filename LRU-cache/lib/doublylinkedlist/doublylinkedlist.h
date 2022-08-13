#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"models/node.h"
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
Node* append(Node* tail,const char *sendername,const char *filename);
Node* prepend(Node* head,const char *sendername,const char *filename);
Node* deleteLast(Node* tail);
Node* selectNodeAndPrepend(Node* head,Node** tail,Node* node);
void printList(Node* head);
void destroyList(Node *head);
#endif