#include <stdio.h>
#include <stdlib.h>
#include "List.h"

/**************/
/*   list.c   */
/**************/

//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
	if (pList == NULL)
		return False;	// no list to initialize

	pList->head.next = NULL;
	return True;
}

/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value)
{
	NODE* tmp;

	if (!pNode)
		return NULL;

	tmp = (NODE*)malloc(sizeof(NODE));	// new node

	if (tmp != NULL) {
		tmp->key = Value;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}

NODE* L_insert_Sorted(LIST* pList, DATA Value, int(*compare)(const void*, const void*))
{
	if (!pList)
		return NULL;
	NODE* pNode = &(pList->head);

	while ((pNode->next != NULL) && (compare(pNode->next->key, Value) < 0))
	{
		pNode = pNode->next;
	}

	return L_insert(pNode, Value);
}

int L_Get_Length(const LIST* pList)
{
	int len = 0;
	const NODE* pNode = &(pList->head);//added const
	while (pNode->next)
	{
		len++;
		pNode = pNode->next;
	}
	return len;
}

//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted 
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
int L_delete(NODE* pNode, void(*freeKey)(void*))
{
	NODE* tmp;
	if (!pNode)
		return 0;
	tmp = pNode->next;
	if (!tmp)
		return 0;
	pNode->next = tmp->next;
	if (freeKey)
		freeKey(tmp->key);
	free(tmp);
	return 1;
}


/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with 
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
const NODE* L_find(const NODE* pNode, DATA Value, int(*compare)(const void*, const void*))
{
	const NODE* tmp = pNode;

	while (tmp != NULL)
	{
		if (!compare(tmp->key, Value))
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}


////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList, void(*free)(void*))
{
	NODE* tmp;
	BOOL cont = True;
	if (!pList)
		return False;

	tmp = &(pList->head);
	while (cont)
		cont = L_delete(tmp, free);

	return True;
}


////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
int L_print(const LIST* pList, void(*print)(const void*))
{
	NODE* tmp;
	int		c = 0;

	if (!pList)
		return False;

	printf("\n");
	tmp = pList->head.next;
	while (tmp != NULL)
	{
		print(tmp->key);
		c++;
		tmp = tmp->next;
	}
	printf("\n");
	return c;
}
