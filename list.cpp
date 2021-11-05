#include "list.h"


void ListCtor( List* some_list )
{
	if( some_list->is_initialized == true )
	{
		return;
	}

	some_list->N_elements = 0;
	some_list->capacity = START_LIST_CAPACITY;

	some_list->head = 0;
	some_list->tail = 0;

	some_list->next = ( int* )calloc( some_list->N_elements, sizeof( int ) );
	some_list->data = ( list_element_t* )calloc( some_list->N_elements, sizeof( list_element_t ) );

	for( int i = 1; i < some_list->capacity; i++ )
	{
		some_list->next[i] = -1;
	}

	some_list->is_initialized = true;
}



void ListDtor( List* some_list )
{
	if( some_list->is_initialized == false )
	{
		return;
	}

	some_list->is_initialized = false;

	free( some_list->data );
	free( some_list->next );

	some_list->N_elements = NO_ELEMENTS;
	some_list->capacity = NO_ELEMENTS;
	some_list->head = 0;
	some_list->tail = 0;

	some_list->data = NULL;
	some_list->next = NULL;
}



int lst_insert( List* some_list, list_element_t value, int place )
{
	if( place == LST_BACK )
	{
		printf( "fuck you, leatherman!\n" );
		abort();
		//some calculations
	}

	int free_place = find_first_free_place( some_list );
	if( free_place == 0 )
	{
		return {};
	}

	some_list->data[free_place] = value; //записываем значение

	some_list->next[free_place] = some_list->next[place]; //новый элемент ссылается на следующий
	some_list->next[place] = free_place; //предшествующий элемент ссылается на новый элемент

	some_list->N_elements++;

	if( some_list->next[free_place] == 0 )
	{
		some_list->head == 1;
	}
	if( some_list->tail < free_place )
	{
		some_list->tail = free_place;
	}

	return free_place;
}



int find_first_free_place( List* some_list )
{
	int counter = 0;
	for( counter; counter < some_list->capacity - 1; counter++ )
	{
		if( some_list->next[counter] == -1 )
		{
			break;
		}
	}

	return counter;
}
