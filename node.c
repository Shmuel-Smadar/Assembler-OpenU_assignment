#include "node.h"

struct node
{
	void* data;
	struct node* next;
	struct node* prev;
};

node createNode(void* data, node prev, node next)
{
	node ptr = calloc(1, sizeof(struct node));
	ptr->next = next;
	ptr->prev = prev;
	ptr->data = data;
	
	return ptr;
}

node getNext(node ptr)
{
	return ptr->next;
}

node getPrev(node ptr)
{
	return ptr->prev;
}

void setNext(node ptr, node next)
{
	ptr->next = next;
}

void setPrev(node ptr, node prev)
{
	ptr->prev = prev;
}

void freeNode(node ptr)
{
	free(ptr);
}

void* getData(node ptr)
{
	return ptr->data;
}

