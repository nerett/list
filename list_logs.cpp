#include "list_logs.h"


//------------------------------------------MACRO------------------------------------------------------------------------
#define error_output( error_variable, possible_error_type ) do { \
    if( error_variable != NULL )                                 \
	{                                                            \
		*error_variable = possible_error_type;                   \
	}                                                            \
} while(0)


//------------------------------------------MACRO------------------------------------------------------------------------
#define void_check_errors( error_variable ) do {                       \
    if( error_variable != NULL )                                       \
  	{                                                                  \
  		if( *error_variable != OK )                                    \
		{                                                              \
			return;                                                    \
		}                                                              \
  	}                                                                  \
} while(0)


//------------------------------------------MACRO------------------------------------------------------------------------
#define int_check_errors( error_variable ) do {                      \
   if( error_variable != NULL )                                      \
   {                                                                 \
	   if( *error_variable != OK )                                   \
	   {                                                             \
		   return {};                                                \
	   }                                                             \
   }                                                                 \
} while(0)


//------------------------------------------FUNCTION------------------------------------------------------------------------
void remake_log( lst_err_code* error_variable )
{
	#ifndef NDEBUG


	FILE* logfile = fopen( LIST_LOGS_FILENAME, "w" );
	if( logfile == NULL )
	{
		error_output( error_variable, FOPEN_ERROR );
		return;
	}

	fputs( "<pre>", logfile );
	fclose( logfile );


	#endif
}


//------------------------------------------FUNCTION------------------------------------------------------------------------
void list_dump( List* some_list, lst_err_code list_error, const char* error_filename, const char* error_function, int error_line, lst_err_code* error_variable )
{
	#ifndef NDEBUG


	assert( some_list );


	FILE* logfile = fopen( LIST_LOGS_FILENAME, "a" );
	if( logfile == NULL )
	{
		error_output( error_variable, FOPEN_ERROR );
		return;
	}

	fprintf( logfile , "<font color=\"purple\">[LIST_DUMP]</font> " );
	if( list_error == OK )
	{
		fprintf( logfile , "<font color=\"green\">[OK] at function %s at %s:%d</font>\n", error_function, error_filename, error_line );
	}
	else
	{
		fprintf( logfile, "<font color=\"red  \">[ERROR] list_error_code = %d at function %s at %s:%d</font>\n", list_error, error_function, error_filename, error_line );
		//fprintf( logfile, "    struct List\n" );
		char image_filename[MAXIMUM_IMAGE_FILENAME_LENGTH] = {};
		sprintf( image_filename, "Rendered_images/lst_grph_dmp_%d.png", some_list->dump_counter );

		render_dump_image( some_list, image_filename );

printf( "image_filename=%s\n", image_filename );
		fprintf( logfile, "<img src=%s>", image_filename ); //image_filename

		//fprintf( logfile, "<img src=lst_grph_dmp_1.png>" );

		fprintf( logfile, "\n" );

		some_list->dump_counter++;
		//fprintf( logfile, "\n" );

		//fprintf( logfile, "<img src=Rendered_images/test.png>" );

		/*
		fprintf( logfile, "    {\n" );
		fprintf( logfile, "        max_capacity = %d\n", some_stack->max_capacity );
		fprintf( logfile, "        N_element = %d\n", some_stack->N_element );
		fprintf( logfile, "        *data = 0x%p\n", some_stack->data );
		fprintf( logfile, "        up_resize_coeff = %f\n", some_stack->up_resize_coeff );
		fprintf( logfile, "        down_resize_coeff = %f\n", some_stack->down_resize_coeff );
		fprintf( logfile, "        is_initialized = %d\n", some_stack->is_initialized );
		//fprintf( logfile, "    };\n" );
		*/

		/*
		if( ( some_stack->user_type_dump_function != NULL ) && some_stack->N_element > -1 )
		{
			char* user_type_dump_string = some_stack->user_type_dump_function( some_stack->data, some_stack->N_element );
			if( user_type_dump_string == NULL )
			{
				error_output( error_variable, INVALID__USER_TYPE_DUMP_STRING_PTR );
				return;
			}

			fprintf( logfile, "    data = { " );
			fprintf( logfile, "%s", user_type_dump_string );
			fprintf( logfile, "};\n" );

			free( user_type_dump_string );
		}
		*/
	}
	fclose( logfile );


	#endif
}



void render_dump_image( List* some_list, char* image_filename )
{
printf( "started image rendering...\n" );
	char render_buffer_filename[MAXIMUM_RENDER_BUFFER_FILENAME_LENGTH] = {};
printf( "image filename = %s\n", image_filename );
	sprintf( render_buffer_filename, "%s.temp", image_filename );
printf( "render buffer filename = %s\n", render_buffer_filename );

	FILE* render_buffer = fopen( render_buffer_filename, "w" ); //перенести это всё добро в оперативку
printf( "started image rendering part 2...\n" );
printf( "file ptr = %d\n", render_buffer );
	fprintf( render_buffer, "digraph G\n" );
	fprintf( render_buffer, "{\n" );
	fprintf( render_buffer, "\trankdir=LR;\n" );
	for( int i = 0; i < some_list->N_elements; i++ )
	{
		fprintf( render_buffer, "\tmemory%d [shape=record,label=\"№ %d | <data> %d | <next> %d | <prev> %d \" ];\n", i, i, some_list->data[i], some_list->next[i], some_list->prev[i] );
	}

	fprintf( render_buffer, "\t" );
	for( int i = 0; i < some_list->N_elements - 1; i++ )
	{
		fprintf( render_buffer, "memory%d->", i );
	}
	fprintf( render_buffer, "memory%d[color=\"white\"];\n", some_list->N_elements - 1 );
	//fprintf( render_buffer, "%d", some_list->data[some_list->N_elements] );


	//fprintf( render_buffer, "\t" );
	/*
	for( int i = 0; i < some_list->N_elements - 0; i++ )
	{
		fprintf( render_buffer, "%d->", some_list->data[i] );
	}
	fprintf( render_buffer, "%d", some_list->data[some_list->N_elements] );
	*/

printf( "started image rendering part 3...\n" );
	//fprintf( render_buffer, ";\n" );
	fprintf( render_buffer, "}\n" );


	fclose( render_buffer );
}
