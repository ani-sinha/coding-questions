#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
  struct node *next;
  int val;
} node;

typedef struct stack {
  struct node *top;
  int len;
} stack;

void push(stack **s, node *n) {
  if (!*s || !s)
    return;
  n->next = (*s)->top;
  (*s)->top = n;
  (*s)->len++;
}

node* pop(stack **s)
{
  node *n = (*s)->top;
  (*s)->top = n->next;
  (*s)->len--;
  return n;
}

void pushint(stack **s, int i) {
  node *n = malloc(sizeof(node));
  if (n) {
    n->val = i;
    n->next = NULL;
    push(s, n);
  }
}

int popint(stack **s) {
  node *n;
  int val = -1;
  if ((*s)->top)
  {
    n = pop(s);
    val = n->val;
    free(n);
  }
  return val;
}

int peek(stack *s) {
  return (s)->top->val;
}

bool stackempty(stack *s) {
  return (s)->top == NULL;
}

int main() {
  stack *s;
  //char *expr = "())((())";
  char *expr = "(((()))";
  int i, len, val;
  int max_len = INT_MIN;
  
  s = malloc (sizeof (stack));
  memset(s, 0, sizeof(stack));
  len = strlen(expr);

  for (i=0; i<len; i++) {
    if (expr[i] == '(') {
      pushint(&s, i);
    } else {
      val = popint(&s);
      if (val == -1) {
	pushint(&s, i);
      } else {
	max_len = max_len > (i-val)? max_len:(i-val); 
      }
    }
  }

  printf("%d\n", max_len+1);
  while(s->len)
    (void) popint(&s);
}

#if 0
public class Solution {

    public int longestValidParentheses(String s) {
        int maxans = 0;
        Stack<Integer> stack = new Stack<>();
        stack.push(-1);
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '(') {
                stack.push(i);
            } else {
                stack.pop();
                if (stack.empty()) {
                    stack.push(i);
                } else {
                    maxans = Math.max(maxans, i - stack.peek());
                }
            }
        }
        return maxans;
    }
}

#endif
