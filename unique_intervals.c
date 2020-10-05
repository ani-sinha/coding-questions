#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct interval {
  int start;
  int end;
  struct interval *next;
};

struct interval intervals[10];
int sz_intervals;
struct interval* unique_intervals;

void swap(struct interval* a, struct interval* b) {
  int low, high;
  low = a->start;
  high = a->end;
  a->start = b->start;
  a->end = b->end;
  b->start = low;
  b->end = high;
}

int cmp(struct interval a, struct interval b)
{
  return a.start < b.start;
}

int partition (struct interval* a, int low, int high)
{
  int pivotloc = low;
  struct interval pivot = a[low];
  int i;
  for (i = low +1; i <= high; i++) {
    if (cmp(a[i], pivot)) {
      swap(&a[++pivotloc], &a[i]);
    }
  }
  swap(&a[pivotloc], &a[low]);
  return pivotloc;
}

void sort(struct interval* intvs, int low, int high) {
  // sort intervals based on interval.start
  int pivot;
  if (low < high) {
    pivot = partition(intvs, low, high);
    sort(intvs, low, pivot-1);
    sort(intvs, pivot+1, high);
  }
}  

void list_add(struct interval** head, struct interval a) {
  struct interval *new = malloc(sizeof(struct interval));
  assert(new);
  new->start = a.start;
  new->end = a.end;
  new->next = NULL;
  
  new->next = *head;
  *head = new;
}

int min(int a, int b) {
  return a< b? a:b;
}

int max(int a, int b) {
  return a> b? a:b;
}

struct interval* find_unique_intervals (void ) {
  struct interval merged_tup;
  int i = 0;

  if (sz_intervals == 0)
    return NULL;
  if (sz_intervals == 1)
    return &intervals[0];

  // sort itervals based on start time
  sort(intervals, 0, sz_intervals-1);

  merged_tup = intervals[1];

  while(1) {
    // take care of non overlapping intervals
    while(intervals[i].end < merged_tup.start) {
      list_add(&unique_intervals, intervals[i]);
      i++;
      if (i == sz_intervals -1 ) {
	list_add(&unique_intervals, intervals[i]);
	break;
      }
      merged_tup = intervals[i+1];
    }
    
    // deal with overlapping intervals
    merged_tup = intervals[i];
    i++;
    while(intervals[i].start < merged_tup.end) {
      merged_tup.start = min(intervals[i].start, merged_tup.start);
      merged_tup.end = max(intervals[i].end, merged_tup.end); // extending
      // the intervals to include overlap. 
      
      i++;
      if (i == sz_intervals) { // if we have already taken care of all intervals
	list_add(&unique_intervals, merged_tup);
	break;
      }
    }
    list_add(&unique_intervals, merged_tup);
    if (i == sz_intervals-1) { // is it the last non-overlapping interval?
      list_add(&unique_intervals, intervals[i]);
      break;
    }
    // more than one remaining intervals to process. do again
    merged_tup = intervals[i+1];
  } /* while loop */
  
  return unique_intervals;
}

int main(int argc, char **argv) {
  return 0;
}
