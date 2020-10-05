// This implements algo for all palindromic decomposition of a string

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int stringHash(char *str, int mod) {
  const int magic = 997, i = 0, val= 0;

  while (str[i] != '\0') {
    val = ((val * magic) + str[i]) % mod;
    i++;
  }
  return val;
}

// clear all the bits except the least significant set bit : y = x & ~(x-1)
// clear the least significant set bit : y = x & (x-1)

typedef enum {
  FALSE,
  TRUE
} bool;

struct substr{
  int sidx;
  int endidx;
};
  
struct node {
  struct node *next;
  struct substr *item;
};

struct node* alloc_node(struct substr *s) {
  struct node *n = malloc(sizeof(struct node));
  if (n) {
    n->item = s;
    n->next = NULL;
  }
  return n;
}

void push(struct node** head, struct node* n) {
  if(!n)
    return;
  if (!(*head) || !head)
    return;
  n->next = (*head)->next;
  (*head)->next = n;
  return;
}

int push_item(struct node** head, struct substr *s)
{
  struct node* n = alloc_node(s);
  if (!n)
    return -1;
  push(head, n);
  return 0;
}

struct node* pop(struct node** head) {
  if (!(*head) || !head)
    return NULL;
  if (!(*head)->next) {
    // popping from empty stack
    return NULL;
  }

  struct node* n = (*head)->next;
  (*head)->next = n->next;
  return n;
}

struct substr* pop_item(struct node** head) {
  struct node* n = pop(head);
  struct substr *s;
  if (!n)
    return NULL;
  s = n->item;
  free(n);
  return s;
}

void printsubstr(char *s, int st, int end) {
  assert(st <= end);
  for (int i=st; i<=end; i++) {
    printf("%c", s[i]);
  }
  printf(" ;; ");
  return;
}

bool isPalindrome(char *s, int start, int len) {
  assert(len >=1 );
  int end = start + len - 1 ;
  if (start == end) // single letter is palindromic
    return TRUE;
  //int st = start, e = end;
  for(; start < end; start++, end--) {
    if (s[start] != s[end])
      return FALSE;
  }
  //printsubstr(s, st, e);
  return TRUE;
}


void printStackSubStr(char *s, struct node *head) {
  struct substr *substr;
  struct node *n = head->next;
  while(n) {
    substr = n->item;
    printsubstr(s, substr->sidx, substr->endidx);
    n= n->next;
  }
  printf("\n");
}

struct substr* alloc_substr(int st, int end) {
  struct substr *s = malloc(sizeof(struct substr));
  if (s) {
    s->sidx = st;
    s->endidx = end;
  }
  return s;
}

void GeneratePalinDecom(int offset, char *s, struct node **stackHead) {
  
  if (offset == strlen(s)  ) {
    printStackSubStr(s, *stackHead);
    return;
  }
  for (int k = offset+1; k <= strlen(s); k++) {
    if (isPalindrome(s, offset, k-offset) == TRUE) {
      struct substr *subs = alloc_substr (offset, k-1);
      assert(subs);
      push_item(stackHead, subs);
      GeneratePalinDecom(offset +1, s, stackHead);
      subs = pop_item(stackHead);
      assert(subs);
      free(subs);
    } /* if */
  } /* for */
  return;
}

int main(int argc, char** argv) {
  struct node * stackHead = malloc (sizeof(struct node));
  stackHead->next = NULL;
  stackHead->item = NULL;

  char str[] = "madam";
  GeneratePalinDecom(0, str, &stackHead);
}
