/*
* File Name: node.h
* contains method that are responsible for creating and managing nodes
* for a Doubly Linked List
*/
#ifndef NODE_H
#define NODE_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node;

/* creates a node with the given data and the previous and next nodes (can be null) */
node createNode(void* data, node prev, node next);

/* changes the next node being pointed to */
void setNext(node ptr, node next);

/*changes the previous node being pointed to */
void setPrev(node ptr, node prev);

/* returns the next node being pointed to */
node getNext(node ptr);

/* returns the previous node being pointed to */
node getPrev(node ptr);

/* free the memory that has been allocated for the node*/
void freeNode(node ptr);

/* returns the data stored by the given node */ 
void* getData(node ptr);

#endif
