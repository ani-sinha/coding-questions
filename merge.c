#include <stdio.h>

struct node {
  int n;
  struct node *next;
};

struct node* merge ( struct node *a, struct node *b) {
  struct node *head;
  struct node *r;

  //if (!a && !b)
  //  return NULL;

  if (!a ) {
    return b;
  } else if (!b)
    return a;

  if (a->n < b->n) {
    head = a;
    a = a->next;
  } else {
    head = b;
    b= b->next;
  }

  r = head;
  while(a && b) {
    if (a->n < b->n) {
      r->next = a;
      a = a->next;
    } else {
      r->next = b;
      b = b->next;
    }
    r = r->next;
  }
  if (a)
    r->next = a;
  else
    r->next = b;

  return head;
}
