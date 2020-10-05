#include <stdio.h>
#include <stdlib.h>


/* linked list reversal */
/* stack push, pop */

struct node {
  int val;
  struct node *next;
};

void printnodes(struct node* head);
void deletenodes(struct node** head);

struct node* alloc_node(int nodeval) {
  struct node *n = malloc(sizeof(struct node));
  if (n) {
    n->val = nodeval;
    n->next = NULL;
  }
  return n;
}


int rand_mimnmax(int min, int max) {
  return ((min+rand()) %(max +1));
}

int generate_list(struct node **head, int nodes)
{
  struct node* newnode, *current;
  int nodeval;
  if (!head || !*head)
    return 1;

  current = *head;
  while(nodes) {
    nodeval = rand_mimnmax(100, 500);
    newnode = alloc_node(nodeval);
    if (!newnode) {
      deletenodes(head);
      return 1;
    }
    if (current == *head)
      (*head)->next = newnode;
    else
      current->next = newnode;
    current = newnode;
    nodes--;
  }
  return 0;
}

void deletenodes(struct node** head) {
  struct node* current;
  struct node* t;
  if (!head || !*head)
    return;
  current = (*head)->next;
  while(current) {
    t = current;
    current = current->next;
    free(t);
  }
  (*head)->next = current;
}

void printnodes(struct node* head) {
  int i = 0;
  if (!head)
    return;
  while (head) {
    printf("[%d]:%d -> ", i++, head->val);
    head = head->next;
  }
  printf("NULL\n");
  return;
}


void reverselist(struct node** head) {
  struct node *prev=NULL, *current, *next;
  if (!head || !(*head))
    return;
  if (!(*head)->next) // empty list
    return;
  // single node
  if (!(*head)->next->next)
    return;
  
  current = (*head)->next;
  while(current) {
    next = current->next;
    current->next = prev; //reversal
    prev = current;
    current = next;
  }
  (*head)->next = prev;
  return;
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

int push_item(struct node** head, int data)
{
  struct node* n = alloc_node(data);
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

int pop_item(struct node** head) {
  struct node* n = pop(head);
  int val;
  if (!n)
    return -1;
  val = n->val;
  free(n);
  return val;
}

struct node* merge (struct node* m, struct node *n) {
  struct node *head, *r;
  if (!m || !n )
    return NULL;
  if (m->val < n->val) {
    head = m;
    m = m->next;
  } else {
    head = n;
    n = n->next;
  }
  r = head;
  while(m && n) {
    if (m->val < n->val) {
      r->next = m;
      m = m->next;
    }
    else {
      r->next = n;
      n = n->next;
    }
    r = r->next;
  }

  if (m) {
    r->next = m;
  }
  else {
    r->next = n;
  }
  return head;
}

struct node* split(struct node* n)
{
  struct node *slow, *fast, *newhead;
  if (!n || !n->next)
    return n;
  
  slow = n;
  fast = n->next->next;
  while(fast) {
    slow = slow->next;
    fast = fast->next;
    if (fast)
      fast = fast->next;
  }
  newhead = slow->next;
  slow->next = NULL;
  return newhead;
}

struct node* sort(struct node* head) {
  struct node* r;
  struct node* l;

  l = head;
  if (l && l->next) {
    r = split(l);
    r = sort(r);
    l = sort(l);
    l = merge(l,r);
  }
  return l;
}

struct node* add_two_nodes(struct head* node1, struct head* node2)
{
  int sum = 0, carry = 0;
  int val1 = 0, val2 = 0;
  struct node *newnode, *head = NULL, *current;

  while(node1 || node2) {
    if (node1) {
      val1 = node1->val;
      node1 = node1->next;
    } else {
      val1 = 0;
    }

    if (node2) {
      val2 = node2->val;
      node2 = node2->next;
    } else {
      val2 = 0;
    }

    sum = (val1 + val2 + carry) % 10;
    carry = (val1 + val2 + carry) / 10;
    newnode = alloc_node(sum);
    if (!head) {
      head = newnode;
      current = head;

    }
    else {
      current->next = newnode;
      current = current->next;
    }
  }
  return head;
}

int main(int argc, char** argv) {
  struct node* head = malloc(sizeof(struct node));
  int sz = 10, item;
  if (!head) {
    return -1;
  }
  if (argc == 2) {
    sz = atoi(argv[1]);
  }

  printf("inserting %d elements into the linked list\n", sz);
  
  head->val = sz;
  head->next = NULL;
  if (generate_list(&head, sz)) {
    printf ("Error while allocating list nodes\n");
    return -1;
  }
  printnodes(head->next);
  reverselist(&head);
  printf("reversed list: \n");
  printnodes(head->next);
  printf("pushing items 600 and 700\n");
  if (push_item(&head, 600) == -1)
    return -1;
  if (push_item(&head, 700) == -1)
    return -1;
  printnodes(head->next);
  item = pop_item(&head);
  if (item != -1)
    printf("popped item: %d\n", item);

  printnodes(head->next);
  printf("Sorted list : \n");
  head->next = sort(head->next);
  printnodes(head->next);
  deletenodes(&head);
  return 0;
}
