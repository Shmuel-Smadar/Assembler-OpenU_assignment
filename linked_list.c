#include "linked_list.h"

struct linked_list
{
	node head;
	node curr;
	node tail;
};

list createList()
{
	list ptr = calloc(1, sizeof(struct linked_list));
	ptr->head = NULL;
	ptr->curr = NULL;
	ptr->tail = NULL;
	return ptr;
}

void startGoingThroughList(list ls)
{
	ls->curr = ls->head;
}

void* getNextNodeData(list ls)
{
	node curr2;
	if(ls->curr == NULL)
		return NULL;
	curr2 = ls->curr;
	ls->curr = getNext(ls->curr);
	return getData(curr2);
}

void* getLast(list ls)
{
	if(ls->tail != NULL)
		return getData(ls->tail);
	return NULL;
}
int isEmpty(list ls)
{
	if(ls->head == NULL)
		return 1;
	return 0;
}
void insert(list ls, void *data)
{
	node ptr;
	ptr = createNode(data, ls->tail, NULL);
	if(ls->head != NULL)
	{
		setNext(ls->tail, ptr);
		ls->tail = ptr;
	}
	else
	{
		ls->head = ptr;
		ls->tail = ptr;
	}
}

void insertList(list ls, list to_insert)
{
	setNext(ls->tail, to_insert->head);
	if(to_insert->tail != NULL)
		ls->tail = to_insert->tail;
	to_insert->tail = NULL;
	to_insert->head = NULL;
	freeNode(to_insert->tail);
	freeNode(to_insert->head);
}

void listForEach(list ls, void(*func)(void*))
{
	node ptr = ls->head;
	while(ptr)
	{
		func(getData(ptr));
		ptr = getNext(ptr);
	}
}

void listForEachWithValue(list ls,int num, void(*func)(void*, int num))
{
	node ptr = ls->head;
	while(ptr)
	{
		func(getData(ptr), num);
		ptr = getNext(ptr);
	}
}

void* listSearch(list ls, void* data, int(*compare)(void*, void*))
{
	node ptr = ls->head;
	while(ptr) 
	{
		if (compare(data, getData(ptr))) 
			return getData(ptr);
		ptr = getNext(ptr);
	}
	return NULL;
}

void removeLastNode(list ls, void(*func)(void*))
{
	node ptr;
	if(ls->tail == ls->head)
	{
		func(getData(ls->head));
		freeNode(ls->tail);
		ls->head = NULL;
		ls->tail = NULL;
		return;
	}
	ptr = ls->tail;
	ls->tail = getPrev(ls->tail);
	func(getData(ptr));
	freeNode(ptr);
	setNext(ls->tail, NULL);
}

void freeList(list ls, void(*func)(void*))
{
	node ptr = ls->head;
	while(ptr != NULL)
	{
		ptr = getNext(ptr);
		if(getData(ls->head) != NULL)
			func(getData(ls->head));
		freeNode(ls->head);
		ls->head = ptr;
	}
	free(ls);
}

