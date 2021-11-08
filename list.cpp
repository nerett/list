#include "list.h"


//------------------------------------------FUNCTION------------------------------------------------------------------------
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

	some_list->next = ( int* )calloc( some_list->capacity, sizeof( int ) );
	some_list->prev = ( int* )calloc( some_list->capacity, sizeof( int ) );
	some_list->data = ( list_element_t* )calloc( some_list->capacity, sizeof( list_element_t ) );

	for( int i = 1; i < some_list->capacity; i++ )
	{
		some_list->next[i] = FREE_POSITION;
		some_list->prev[i] = FREE_POSITION;
	}

	some_list->is_initialized = true;

	#ifndef NDEBUG
		some_list->dump_counter = 0;
	#endif
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
void ListDtor( List* some_list )
{
	if( some_list->is_initialized == false )
	{
		return;
	}

	some_list->is_initialized = false;

	free( some_list->data );
	free( some_list->next );
	free( some_list->prev );

	some_list->N_elements = NO_ELEMENTS;
	some_list->capacity = NO_ELEMENTS;
	some_list->head = 0;
	some_list->tail = 0;

	some_list->data = NULL;
	some_list->next = NULL;
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
int lst_insert( List* some_list, list_element_t value, int place )
{
	if( place == LST_TAIL )
	{
		printf( "fuck you, leatherman!\n" ); //!TODO =tail
		abort();
		//some calculations
	}
	//сделать прверку после интерпретации

	int free_place = find_first_free_place( some_list );
	if( free_place == 0 )
	{
		return {};
	}

	if( some_list->prev[place] == 0 ) //возможно, стоит перенести (надо рассмотреть крайние случаи)
	{
		some_list->head == place;
	}

	some_list->data[free_place] = value; //записываем значение

	some_list->next[free_place] = some_list->next[place]; //новый элемент ссылается на следующий
	some_list->prev[free_place] = place; //новый элемент ссылается на предыдущий
	some_list->next[place] = free_place; //предшествующий элемент ссылается на новый элемент
	some_list->prev[some_list->next[free_place]] = free_place; //следующий элемент ссылается на новый

	some_list->N_elements++;

	if( some_list->next[free_place] == 0 )
	{
		some_list->tail = free_place;
	}
	if( some_list->prev[free_place] == 0 ) //возможно, стоит перенести (надо рассмотреть крайние случаи)
	{
		some_list->head == free_place;
	}

	return free_place;
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
list_element_t lst_pop( List* some_list, int place )
{
	if( place == LST_TAIL )
	{
		printf( "fuck you, leatherman!\n" ); //!TODO =tail
		abort();
		//some calculations
	}

	//int prev = find_prev( some_list, place );

	some_list->next[some_list->prev[place]] = some_list->next[place]; //предыдущий ссылается на следующий (без удаляемого)
	some_list->prev[some_list->next[place]] = some_list->prev[place]; //следующий ссылается на предыдущий;

	list_element_t value = some_list->data[place];

	some_list->data[place] = INT_POISON;
	some_list->next[place] = FREE_POSITION; //позиция элемента освобождена
	some_list->prev[place] = FREE_POSITION;

	return value;
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
int find_first_free_place( List* some_list )
{
	int counter = 0;
	for( counter = 1; counter < some_list->capacity - 1; counter++ )
	{
		if( some_list->prev[counter] == -1 )
		{
			break;
		}
	}

	printf("first free place = %d\n", counter );
	return counter;
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
int find_prev( List* some_list, int place )
{
	int prev = 0;
	for( prev = 1; prev < some_list->capacity - 1; prev++ )
	{
		if( some_list->next[prev] == place )
		{
			break;
		}
	}

	return prev;
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
int slow_slow_slow_find_physical_pos( List* some_list, int logical_pos )
{
	int current = some_list->head;
	for( int i = 0; i < logical_pos - 1; i++ )
	{
		current = some_list->next[current];
	}

	return current;
}
