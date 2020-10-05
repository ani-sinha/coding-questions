#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// directed asyclic graph ...
// topological sort

struct nodes {
  struct nodes *outedges;
  int nodenum;
};

struct stacknode {
  struct stacknode *next;
  int nodenum;
};

struct stacknode *stackhead;


typedef enum {
  false,
  true,
}bool;

void push(int node) {
  struct stacknode *n = malloc(sizeof(struct stacknode));
  assert(n);
  n->nodenum = node;
  n->next = stackhead;
  stackhead = n;
}

int pop() {
  int node;
  struct stacknode *n;
  if (!stackhead)
    return -1;
  node = stackhead->nodenum;
  n = stackhead;
  stackhead = stackhead->next;
  free(n);
  return node;
}

void toposort(struct nodes *nodelist, int node, bool *visited) {

  visited[node] = true;
  for (int j=0; nodelist[node].outedges[j].nodenum;j++) {
    if (!visited[j])
      toposort(nodelist, j, visited);
  }
  push(node+1);
}

int main(int argc, char **argv) {
  bool* visited;
  int nnodes, nedges, node, edge;
  struct nodes* nodelist, *edgelist;
  printf("How many nodes? \n");
  scanf("%d", &nnodes);
  if (!nnodes)
    return 0;
  
  nodelist = malloc((nnodes+1) * sizeof(struct nodes));
  assert(nodelist);
  memset(nodelist, 0, (nnodes+1) * sizeof(struct nodes));
  visited = malloc(nnodes * sizeof(bool));
  assert(visited);
  memset(visited, false, nnodes * sizeof(bool));
  
  for (int i=0;i<nnodes;i++) {
    nodelist[i].nodenum = i+1;

    printf("How many outgoing edges from node: %d?", i+1);
    scanf("%d", &nedges);
    fflush(stdin);
    edgelist = malloc((nedges+1) * sizeof(struct nodes));
    assert(edgelist);
    memset(edgelist, 0, (nedges+1) * sizeof(struct nodes));
    nodelist[i].outedges = edgelist;
    if (!nedges)
      continue;

    printf("Enter outgoing edges ... \n");
  
    for (int j = 0; j< nedges; j++) {
      scanf("%d", &edge); fflush(stdin);
      edgelist[j].nodenum = edge;
      edgelist[j].outedges = NULL;
    } /* for nedges */
  } /* for nnodes */

  for (int i = 0; i< nnodes; i++) {
    if (!visited[i]) {
      toposort(nodelist, i, visited);
    }
  }

  printf("Sorted order is:\n");
  while((node = pop()) != -1) {
    printf("%d ", node);
  }
  printf("\n");
  return 0;
}
