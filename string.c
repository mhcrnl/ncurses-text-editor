/**
 * string.c
 * 
 * Includes methods to create, modify, compare or 
 *  
 * 
 */ 

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <wchar.h>

STRING* str_create() {
	STRING* str = (STRING*) malloc(sizeof(STRING));
	str->payload = 0;
	str->next = NULL;
	str->current = str;
	return str;
}

void str_clear(STRING* str) {
	for(i = 0; i < size; i++) {
		str_delete(str, 0);
	}
}

void str_add(STRING* str, wint_t payload) {
	str->current->next = (STRING*) malloc(sizeof(STRING));
	str->current->next->payload = payload;
	str->current = str->current->next;
	str->current->next = NULL;
}

void str_set(STRING* str, const char* c) {
	int i=0; 
	while(c[i] != '\0') {
		str_add(str, c[i]);
		i++;
	}
}

void str_set_w(STRING* str, const wchar_t* c) {
	int i=0; 
	while(c[i] != '\0') {
		str_add(str, c[i]);
		i++;
	}
}

wint_t str_top(STRING* str) {
	return str->current->payload;
}

int str_search(STRING* str, wint_t value) {
	STRING* head = str->next;
	int i = 0;

	while(head != NULL) {
		if(head->payload == value) {
			return i;
		}
		head = head->next;
		i++;
	}
	return -1;
}

wint_t str_get(STRING* str, int index) {
	STRING* head = str->next;
	int i = 0;

	if(index >= 0) {
		while(head != NULL) {
			if(i == index) {
				return head->payload;
			}

			head = head->next;
			i++;
		}
	}
	return 0;
}

void str_delete(STRING* str, int index) {
	if(index >= str_size(str) || index < 0) {
		return -1;
	}

	STRING* head = str->next;
	STRING* tail = str;

	int i=0;
	for(i=0; i<index; i++) {
		tail = head;
		head = head->next;
	}

	tail->next = head->next;
	str = tail;
}

int str_size(STRING* str) {
	STRING* head = str->next;
	int s = 0;

	while(head != NULL) {
		head = head->next;
		s++;
	}

	return s;
}

/**
 * 
 * Remember to free the space allocated for the char* later!
 * 
*/
char* str_to_pointer(STRING* str) {
	char* ptr = malloc(sizeof(char) * str_size(str) + 1);
	
	int i = 0;
	for(i = 0; i < str_size(str); i++) {
		ptr[i] = str_get(str, i);
	}
	ptr[i] = '\0';
	
	return ptr;
}

wchar_t* str_to_pointer_w(STRING* str) {
	wchar_t* ptr = malloc(sizeof(wint_t) * str_size(str) + 1);
	
	int i = 0;
	for(i = 0; i < str_size(str); i++) {
		ptr[i] = str_get(str, i);
	}
	ptr[i] = '\0';
	
	return ptr;
}

int str_equal(STRING* str1, STRING* str2) {
	int size1 = str_size(str1);
	int size2 = str_size(str2);
	
	if(size1 != size2) {
		return 0;
	}
	
	int i=0;
	for(i=0; i<size1; i++) {
		if(str_get(str1, i) != str_get(str2, i)) {
			return 0;
		}
	}
	
	return 1;
}

void str_free(STRING* str) {
	int i = 0;
	int size = str_size(str);
	
	str_clear(str);
	
	free(str);
	str = NULL;
}
