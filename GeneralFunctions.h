#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR_LEN 255

char*	 getStrExactName(const char* msg);
char*	 getDynStr(char* str);
char*	 myGets(char* buffer, int size);
void	 generalArrayFunction(void* pArr, int num_of_element, size_t size_of_element, void f(void* element));





