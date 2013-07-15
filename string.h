#ifndef __STRING_H
#define __STRING_H

#include <wchar.h>

typedef struct _STRING {
	wint_t payload;
	struct _STRING* current;
	struct _STRING* next;
}STRING;

STRING* str_create();
void str_clear(STRING* str);
void str_set(STRING* str, const char* c);
void str_set_w(STRING* str, const wchar_t* c);
void str_add(STRING* str, wint_t payload);
wint_t str_top(STRING* str);
int str_search(STRING* str, wint_t value);
wint_t str_get(STRING* str, int index);
void str_delete(STRING* str, int index);
int str_size(STRING* str);
char* str_to_pointer(STRING* str);
wchar_t* str_to_pointer_w(STRING* str);
int str_equal(STRING* str1, STRING* str2);
void str_free(STRING* str);

#endif
