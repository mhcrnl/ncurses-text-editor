/**
 * string.h
 * 
 * Includes methods to create, modify, compare or concaternate
 * STRING objects. A STRING is a linked list type that contains
 * wide characters (wchar_t).
 * Remember to only use pointers of this type. Since you'll have to
 * allocate space for this list type, you have to initialize a STRING*
 * by calling the STRING* str_create() function.
 * Once you don't need the STRING* object anymore, remember to call
 * the void str_free(STRING*) procedure to free the allocated space.
 * 
 */ 

#ifndef __STRING_H
#define __STRING_H

#include <wchar.h>

typedef struct _STRING {
	wint_t payload;
	struct _STRING* current;
	struct _STRING* next;
	struct _STRING* previous;
}STRING;

STRING* str_create();
STRING* str_substr(STRING* str, int start, int end);
void str_concat(STRING* str1, STRING* str2);
void str_insert(STRING* str, int index, wchar_t payload);
void str_clear(STRING* str);
void str_set(STRING* str, const char* c);
void str_add(STRING* str, wchar_t payload);
wchar_t str_top(STRING* str);
int str_search(STRING* str, wchar_t value);
wchar_t str_get(STRING* str, int index);
int str_delete(STRING* str, int index);
int str_size(STRING* str);
char* str_to_pointer(STRING* str);
int str_equal(STRING* str1, STRING* str2);
void str_free(STRING* str);

wchar_t* str_to_pointer_w(STRING* str);
void str_set_w(STRING* str, const wchar_t* c);

#endif
