#pragma once
#include "Def.h"
/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/

/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

NODE* L_insert_Sorted(LIST* pList, DATA Value, int(*compare)(const void*, const void*));

int L_Get_Length(const LIST* pList);

int L_delete(NODE* pNode, void(*freeKey)(void*));					// erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*));		// return a pointer to the node 

BOOL L_free(LIST* pList, void(*free)(void*));					// free list memory

int L_print(const LIST* pList, void(*print)(const void*));					// print the list content


