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
	}
	fclose( logfile );


	#endif
}



void render_dump_image( List* some_list, char* image_filename )
{
	char render_buffer_filename[MAXIMUM_RENDER_BUFFER_FILENAME_LENGTH] = {};
	sprintf( render_buffer_filename, "%s.temp", image_filename );

	FILE* render_buffer = fopen( render_buffer_filename, "w" ); //перенести это всё добро в оперативку

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

	for( int i = 0; i < some_list->N_elements - 1; i++ )
	{
		fprintf( render_buffer, "\tmemory%d: <next> -> memory%d[color=\"green\"];", i, some_list->next[i] );
		fprintf( render_buffer, "\tmemory%d: <prev> -> memory%d[color=\"blue\"];", i, some_list->prev[i] );
	}

	fprintf( render_buffer, "\n}\n" );

	char render_command[MAXIMUM_RENDER_COMMAND_LENGTH] = {};
printf("render command = %s\n", render_command );
	sprintf( render_command, "dot %s -T png -o %s", render_buffer_filename, image_filename );
printf("render command = %s\n", render_command );
	system( render_command );


	fclose( render_buffer );
}
