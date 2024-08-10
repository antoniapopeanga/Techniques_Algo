#include "heap.h"
#include <stdlib.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h=malloc(sizeof(*h));
  if (!h) {
    return NULL;
    }

  h->nmax=k;

  h->array=malloc(k*sizeof(void*));
  if (!h->array) {
    // Handle memory allocation failure
    free(h);  // Clean up previously allocated memory
    return NULL;
    }

  h->n=0;
  h->f=f;
  return h;
}

void heap_destroy(heap h) {
      if (h) {
        free(h->array);  // Free the array of elements
        free(h);         // Free the heap structure itself
    }

}

bool heap_empty(heap h) {
  return (h->n==0);
}


void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

bool heap_add(heap h, void *object) {
    if (h->n == h->nmax) // Check if heap is full
        return true;

    // Add the object at the end
    h->array[h->n + 1] = object;
    int idx = h->n + 1; // Index of the newly added object
    h->n++; // Increase the number of elements in the heap

    // Heapify Up
    if (h->n > 1) {
        void *aux;
        while (idx > 1 && h->f(h->array[idx], h->array[idx / 2]) < 0) {
            swap(&h->array[idx], &h->array[idx / 2]);
            idx = idx / 2; // Move up in the heap
        }
    }

    return false;
}
void *heap_top(heap h) {

  return h->array[1];
}

void *heap_pop(heap h) {
    if (h->n != 0) {
        void *obj = h->array[1];
        void *aux = h->array[1];
        h->array[1] = h->array[h->n];
        h->array[h->n] = aux;
        h->n--;

        int idx = 1;
        while (idx * 2 <= h->n) { // Check if left child exists
            int childIdx = idx * 2; // Index of the left child
            // If right child exists and is smaller than the left child
            if (childIdx + 1 <= h->n && h->f(h->array[childIdx + 1], h->array[childIdx]) < 0) {
                childIdx++; // Move to the right child
            }
            // If the current node is smaller than the smaller child, break
            if (h->f(h->array[childIdx], h->array[idx]) > 0) {
                break;
            }
            // Swap with the smaller child
            swap(&h->array[idx], &h->array[childIdx]);
            idx = childIdx; // Move down in the heap
        }
        return obj;
    }

    return NULL;
}