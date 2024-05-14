#pragma once
/**************************************************************************/
/* def.h                                                                  */
/* This file contains GENERAL definitions used in several data structures */
/**************************************************************************/

// a value not supposed in stack and queue
#define		EMPTY	0x7FFFFFFF

typedef unsigned char BYTE;

// new types
typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
typedef struct node
{
	DATA			key;
	struct node* next;
}NODE;


