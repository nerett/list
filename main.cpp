#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "list_logs.h"

int main()
{
	remake_log();
	
	List todo_list;
	ListCtor( &todo_list );

	//printf("%d\n", todo_list.data );
	//printf("%d\n", todo_list.next );


//---------------------------------------------------------------------
	int prev = lst_insert( &todo_list, 2, 0 );

	printf( "\ndata:\n" );
	for( int i = 0; i < todo_list.N_elements + 10; i++ )
	{
		printf( "%d ", todo_list.data[i] );
	}
	printf( "\nnext:\n" );
	for( int i = 0; i < todo_list.N_elements + 10; i++ )
	{
		printf( "%d ", todo_list.next[i] );
	}
	printf( "\n" );

	//---------------------------------------------------------------------
		prev = lst_insert( &todo_list, 3, prev );

		printf( "\ndata:\n" );
		for( int i = 0; i < todo_list.N_elements + 10; i++ )
		{
			printf( "%d ", todo_list.data[i] );
		}
		printf( "\nnext:\n" );
		for( int i = 0; i < todo_list.N_elements + 10; i++ )
		{
			printf( "%d ", todo_list.next[i] );
		}
		printf( "\n" );

		//---------------------------------------------------------------------
			prev = lst_insert( &todo_list, 4, prev );

			printf( "\ndata:\n" );
			for( int i = 0; i < todo_list.N_elements + 10; i++ )
			{
				printf( "%d ", todo_list.data[i] );
			}
			printf( "\nnext:\n" );
			for( int i = 0; i < todo_list.N_elements + 10; i++ )
			{
				printf( "%d ", todo_list.next[i] );
			}
			printf( "\n" );


			//---------------------------------------------------------------------
				prev = lst_insert( &todo_list, 5, prev );

				printf( "\ndata:\n" );
				for( int i = 0; i < todo_list.N_elements + 10; i++ )
				{
					printf( "%d ", todo_list.data[i] );
				}
				printf( "\nnext:\n" );
				for( int i = 0; i < todo_list.N_elements + 10; i++ )
				{
					printf( "%d ", todo_list.next[i] );
				}
				printf( "\n" );


	list_element_t value = lst_pop( &todo_list, 2 );
	printf("value = %d\n", value );

	//---------------------------------------------------------------------
		prev = lst_insert( &todo_list, 999, prev );

		printf( "\ndata:\n" );
		for( int i = 0; i < todo_list.N_elements + 10; i++ )
		{
			printf( "%d ", todo_list.data[i] );
		}
		printf( "\nnext:\n" );
		for( int i = 0; i < todo_list.N_elements + 10; i++ )
		{
			printf( "%d ", todo_list.next[i] );
		}
		printf( "\n" );

	//--------------------------------------------------------
	list_dump( &todo_list, USER_CALL, __FILE__, __PRETTY_FUNCTION__, __LINE__ );

	int test_slow_find = slow_slow_slow_find_physical_pos( &todo_list, 2 );
	printf( "physical pos of 4 = %d\n", test_slow_find );



	ListDtor( &todo_list );
	return 0;
}
