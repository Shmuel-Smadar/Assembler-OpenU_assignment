/*
* File Name: linked_list.h
* contains method that are responsible for creating and managing generic doubly linked list
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list *list;


/*creates and allocates memory for the linked list */
list createList();

/*insert data into the list */
void insert(list ls, void *data);

/*insert the second list into the first one, from head to tail */
void insertList(list ls, list toInsert);


/*search in the generic list with the given comprasion function (user should make sure the method fits the data type that is stored) */
void* listSearch(list ls, void* data, int(*compare)(void*, void*));

/*run the function on every node in the list */
void listForEach(list ls, void(*func)(void*));

/*run the function on every node in the list */
void listForEachWithValue(list ls,int num, void(*func)(void*, int num));

/*initialize the curr node to point to the head */
void startGoingThroughList(list ls);

/*every call to this function returns the data that curr is pointing on and moves it forward,
 until it reaches the end and returns NULL */
void* getNextNodeData(list ls);

/*get the last data that has been stored (from the tail) */
void* getLast(list ls);

/* free the memory that has been allocated for the last node of the list,
 gets a function that is used to free the data stored inside */
void removeLastNode(list ls, void(*func)(void*));

/*check if the list is empty */
int isEmpty(list ls);

/*free the memory that has been allocated for the list
and use the given function to free thememory for the data store in it*/
void freeList(list ls, void(*func)(void*));

#endif
