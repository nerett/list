#ifndef LIST_LOGS_H_INCLUDED
#define LIST_LOGS_H_INCLUDED

#include "list.h"


const char LIST_LOGS_FILENAME[] = "list_log.html";
const int MAXIMUM_IMAGE_FILENAME_LENGTH = 40;
const int MAXIMUM_RENDER_BUFFER_FILENAME_LENGTH = 40;


enum lst_err_code
{
	OK = 0,
	USER_CALL = 1,
	FOPEN_ERROR = 2
};


#define lst_validate_dump( some_list, error_variable ) do {                                                  \
		lst_err_code list_error = OK;                                                                        \
		validate_list( some_list, &list_error );                                                       \
		list_dump( some_list, list_error, __FILE__, __PRETTY_FUNCTION__, __LINE__, error_variable );   \
} while(0)


void render_dump_image( List* some_list, char* image_filename );
void remake_log( lst_err_code* error_variable = NULL );
void list_dump( List* some_list, lst_err_code list_error, const char* error_filename, const char* error_function, int error_line, lst_err_code* error_variable = NULL );


#endif
