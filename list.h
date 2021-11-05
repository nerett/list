#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


typedef int list_element_t;

const int START_LIST_CAPACITY = 256; //0 is unused
const int INT_POISON = 0xAB0BA;
const int NO_ELEMENTS = 0;
const int LST_BACK = -1;
const int FREE_POSITION = -1;

struct List
{
	list_element_t* data = NULL;
	int* next = NULL;

	int N_elements = 0;
	int capacity = 0;

	int head = 0; //положение первого элемента
	int tail = 0; //положение последнего элемента

	bool is_initialized = false;
};

void ListCtor( List* some_list );
void ListDtor( List* some_list );

int lst_insert( List* some_list, list_element_t value, int place = LST_BACK );
list_element_t lst_pop( List* some_list, int place = LST_BACK );

int find_first_free_place( List* some_list );
int find_prev( List* some_list, int place );


#endif
