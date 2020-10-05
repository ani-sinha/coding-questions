#include <stdio.h>
#include <stdlib.h>

typedef enum {
  false,
  true,
}bool;

struct node {
  int val;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct qnode {
  struct node *treenode;
  struct qnode *prev;
  struct qnode *next;
};

struct node *root;

struct queue {
  struct qnode *head;
  struct qnode *tail;
  int len;
};

struct qnode* alloc_qnode() {
  struct qnode *n = malloc(sizeof(struct qnode));
  if (n) {
       n->next = n->prev = NULL;
       n->treenode = NULL;
  }
  return n;
}

void enqueue(struct queue *q, struct node *n) {
  struct qnode *qn;
  if (!n)
    return;
 
  qn = alloc_qnode();
  if (qn) {
    qn->treenode = n;
    qn->next = q->head;
    if (q->head)
      q->head->prev = qn;
    if(!q->tail)
      q->tail = qn;
    q->head = qn;
    q->len++;
  }
}

struct node* dequeue(struct queue *q) {
  struct qnode *qn = q->tail;
  struct node *n = NULL;
  if(qn) {
    n = qn->treenode;
    q->tail = qn->prev;
    free(qn);
    q->len--;
  }
  return n;
}

struct node* alloc_node (int val)
{
  struct node *r = (struct node*) malloc(sizeof(struct node));
  r->left = r->right = r->parent = NULL;
  r->val = val;
  return r;
}

void insert(struct node *r, int val ) {
  if (r) {
    if (r->val < val)
      if (r->right)
	insert(r->right, val);
      else {
	r->right = alloc_node(val);
	if (r->right)
	  r->right->parent = r;
      }
    else
      if (r->left)
	insert (r->left, val);
      else {
	r->left = alloc_node(val);
	if (r->left)
	  r->left->parent = r;
      }
  } else {
    r = alloc_node(val);
    root = r;
  }
}


void traverse_inorder(struct node *r) {
  if (!r)
    return;
  traverse_inorder(r->left);
  printf("node val: %d\n", r->val);
  traverse_inorder(r->right);
}

void traverse_inorder_norecursion(struct node *r) {
  struct node* prev = NULL, *current = r, *next = NULL;
  
  while(current) {
    // going down
    if (current->parent == prev) {
      if (current->left) {
	next = current->left;
      } else {
	printf("node val: %d\n", current->val);
	if (current->right) {
	  next = current->right;
	} else
	  next = current->parent;
      }
    } else if (current->left == prev) {
      // going up
      printf("node val: %d\n", current->val);
      	if (current->right) {
	  next = current->right;
	} else
	  next = current->parent;
    } else {
      next = current->parent;
    }
    prev = current;
    current = next;

  } /* while */ 
}


struct node* lca(struct node* n, int lowval, int highval) {
  int t;
  if (highval < lowval) {
    t = lowval;
    lowval = highval;
    highval = t;
  }
  
  while(n->val < lowval || n->val > highval) {
    while(n->val < lowval)
      n = n->right;
    while( n->val > highval)
      n = n->left;
  }
  return n;
}

struct node* successor(struct node *n) {
  if (n->right) {
    n = n->right;
    while(n->left)
      n = n->left;
    return n;
  }
  while(n->parent && n->parent->right == n)
    n = n->parent;
  return n->parent;
}

int height(struct node *n) {
  int rh= 0, lh= 0, h;
  if (!n)
    return 0;
  if(n->right == NULL && n->left == NULL) {
    return 1;
  }
  if (n->right)
    rh = height(n->right);
  if (n->left)
    lh = height(n->left);
  return (rh >= lh? rh +1: lh+1);
}

void printNodesAtLevel(struct node* n, int l) {

  if (!n)
    return;
  if (l ==1) {
    printf("%d ", n->val);
    return;
  }
  printNodesAtLevel(n->left, l-1);
  printNodesAtLevel(n->right, l-1);
  
}
void level_traversal(struct node *n) {
  int h;

  h = height (n);
  for(int i = 1; i<=h; i++) {
    printNodesAtLevel(n, i);
    printf("\n");
  }
}

void level_traversal_queue(struct node *n)
{
  struct queue q;
  q.head = q.tail = NULL;
  q.len = 0;
  while(n) {
    printf("%d ", n->val);
    enqueue(&q, n->left);
    enqueue(&q, n->right);
    n = dequeue(&q);
  }
}

void level_traversal_2(struct node *n) {
  struct queue q;
  q.head = q.tail = NULL;
  int level = 0, i=0, level_len = 0;
  q.len = 0;
  if (n)
    enqueue(&q, n);
  while(q.len) {
    printf("\n");
    level_len = q.len;
    for (i=0;i<level_len;i++) {
      n = dequeue(&q);
      printf("level: %d, nodeval: %d\n", level, n->val);
      if (n->left)
	enqueue(&q, n->left);
      if (n->right)
	enqueue(&q, n->right);
    }
    level++;
  }
}

struct node* find(struct node *n, int val) {
  if (n) {
    if (n->val == val)
      return n;
    if (n->val < val)
      return find(n->right, val);
    else
      return find(n->left, val);
  }
  return NULL;
}

void isBalanced(struct node *n, bool *balanced, int *height) {
  bool b;
  int hl, hr;
  
  if (!n) {
    *balanced = true;
    *height = -1;
    return;
  }
  isBalanced( n->right, &b, &hr );
  if (!b) {
      *balanced = false;
      *height = 0;
      return;
  }

  isBalanced( n->left, &b, &hl );
  if (!b) {
      *balanced = false;
      *height = 0;
      return;
  }

  // both left and right subtrees are balanced.
  *balanced = (hl>hr? hl-hr : hr-hl) <=1;
  *height = (hl > hr)? (hl+1) : (hr+1);
  return;
}

bool is_symmetric(struct node* n1, struct node* n2) {
  if (!n1 && !n2)
    return true;
  if (!n1 || !n2)
    return false;
  if (n1->val != n2->val)
    return false;
  return is_symmetric(n1->left, n2->right) &&
    is_symmetric(n1->right, n2->left);
}

bool is_unival(struct node *n) {
  if (!n)
    return true;
  if (n->val != n->left->val)
    return false;
  if (n->val != n->right->val)
    return false;
  return is_unival(n->left) && is_unival(n->right);
}

int count_unival(struct node *n)
{
  int sum;
  if (!n)
    return 0;
  sum = count_unival(n->left) + count_unival(n->right);
  if (is_unival(n))
    sum+=1;
  return sum;
}

void flatten_tree(struct node **head, struct node *root) {
  static struct node *prev;

  if (!root)
    return;

  flatten_tree(head, root->left);

  if (!prev) 
    *head = root;
  else {
    root->left = prev;
    prev->right = root;
  }

  prev = root;

  flatten_tree(head, root->right);
}

void print_list(struct node *head)
{
  while(head) {
    printf("%d ", head->val);
    head = head->right;
  }
  printf("\n");
}
int main(int argc, char** argv) {
  struct node* n;
  struct node *ll_head;
  bool balanced = true;
  int h;
  int nodeval[] = {15, 7, 2, 10, 40, 25, 50, 1, 3, 100, 51, 250, 45};
  int i, sz = sizeof(nodeval)/sizeof(nodeval[0]);
  for (i=0; i<sz;i++) {
    insert(root, nodeval[i]);
  }
  isBalanced(root, &balanced, &h);
  if (balanced)
    printf("Tree is balanced\n");
  else
    printf("Tree is not balanced\n");
  
  traverse_inorder(root);
  // no recursion inorder traversal
  printf("inorder without recursion\n");
  traverse_inorder_norecursion(root);
  n = lca(root, 10, 25);
  printf("LCA for nodes 10 & 25 is : %d\n", n->val);
  n = find(root, 10);
  n = successor(n);
  printf("successor for node 10 is %d\n", n->val);
  printf("height of the tree is %d\n", height(root));

  level_traversal(root);
  printf("\n");
  level_traversal_queue(root);
  level_traversal_2(root);
  flatten_tree(&ll_head, root);

  print_list(ll_head);

  return 0;
}

