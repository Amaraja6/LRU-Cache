#include "doublylinkedlist.h"
Node *append(Node *tail, const char *sendername, const char *filename)
{
  if (tail)
  {
    Node *newnode = newNode(sendername, filename);
    Node *curr = tail;

    curr = tail;
    tail = newnode;
    tail->Prev = curr;
    curr->Next = tail;
  }

  return tail;
}

Node *prepend(Node *head, const char *sendername, const char *filename)
{
  if (head)
  {
    Node *curr = head;
    Node *newnode = newNode(sendername, filename);
    head = newnode;
    head->Next = curr;
    curr->Prev = head;
  }
  return head;
}

Node *deleteLast(Node *tail)
{
  if (tail)
  {
    Node *curr = tail;
    tail = tail->Prev;
    tail->Next = NULL;
    free(curr);
  }
  return tail;
}

Node *selectNodeAndPrepend(Node *head, Node **tail, Node *node)
{
  if (head && node && *tail)
  {
    Node *curr = node;
    if (head != curr)
    {
      if (*tail == curr)
      {
        curr = *tail;
        *tail = (*tail)->Prev;
      }

      Node *before = curr->Prev;
      Node *after = curr->Next;
      before->Next = after;

      if (after)
      {
        after->Prev = before;
      }

      curr->Next = head;
      head->Prev = curr;
      head = curr;
      head->Prev = NULL;
    }
  }
  return head;
}

void destroyList(Node *head)
{
  if (head)
  {
    Node *itr = head;
    while (itr)
    {
      Node *temp = itr;
      itr = itr->Next;
      free(temp);
    }
  }
}
void printList(Node *head)
{
  if (head)
  {
    int sno = 1;
    Node *temp = head;
    while (temp != NULL)
    {
      printf("\n%d.)%s", sno++, temp->SenderName);
      temp = temp->Next;
    }
  }
}
