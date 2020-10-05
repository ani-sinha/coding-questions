// This generates a balanced binary search tree from a sorted array

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef enum {
  false,
  true,
} bool;

struct bst_node {
  int val;
  struct bst_node *left;
  struct bst_node *right;
};

int arr[] = {3, 5, 7, 8, 20, 35, 50, 90, 105, 200, 500};


void isBalanced(struct bst_node *n, bool *balanced, int *height) {
  bool b;
  int hl, hr;
  
  if (!n) {
    *balanced = true;
    *height = 0;
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

struct bst_node* bstFromSorted(int* a, int low, int high) {
  int mid;
  struct bst_node *node;
  
  if (high <  low)
    return NULL;
  node = malloc(sizeof(struct bst_node));
  assert(node);
  mid = low + (high - low) /2;
  node->val = a[mid];
  node->left = bstFromSorted(a, low, mid-1);
  node->right = bstFromSorted(a, mid+1, high);
  return node;
}

void traverseInOrder(struct bst_node *n) {
  if (n) {
    traverseInOrder(n->left);
    printf("%d ", n->val);
    traverseInOrder(n->right);
  }
  return;
}

void deleteNode(struct bst_node **root, int key) {
  struct bst_node *key_node = NULL, *parent = NULL, *r, *n = *root;
  while(n) {
    if (n->val < key) {
      parent = n;
      n = n->right;
    }
    else if (n->val > key) {
      parent =n;
      n = n->left;
    }
    else if (n->val == key) {
      key_node = n;
      break;
    }
  }
  
  if (!key_node) {
    printf("Unable to find key %d\n", key);
    return;
  }

  
  if (key_node->right) {
    for (r = key_node->right; r->left; r = r->left);
    r->left = key_node->left; // attach the left subtree
    if (!parent) { // node we are deleting is the root node; update root
      (*root) = key_node->right;
    } else { // attach the right subtree
      if(parent->left == key_node)
	parent->left = key_node->right;
      else
	parent->right = key_node->right;
    }
    free(key_node);
  } else if (key_node && !parent) {
    (*root) = key_node->left;
    free(key_node);
  } else if (parent->left == key_node) {
    parent->left = key_node->left;
    free(key_node);
  } else {// parent->right == key_node
    parent->right = key_node->left;
    free(key_node);
  }
  return;
}

int main(int argc, char** argv) {
  struct bst_node *n;
  bool bal;
  int h;
  n = bstFromSorted(arr, 0, (sizeof(arr)/sizeof(arr[0])) -1);
  isBalanced(n, &bal, &h);
  if (bal) {
    printf("Tree is balanced\n");
  } else
    printf("Tree is not balanced\n");
  
  traverseInOrder(n);
  printf("\n");
  deleteNode(&n, 21);
  traverseInOrder(n);
  printf("\n");
  for(int i = 0; i<(sizeof(arr)/sizeof(arr[0])) -1; i++ ) {
    printf("deleting node %d\n", arr[i]);
    deleteNode(&n, arr[i]);
    traverseInOrder(n);
    printf("\n");
  }
  printf("\n");
  
  return 0;
}
