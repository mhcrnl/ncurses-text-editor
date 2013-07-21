/**
 * string.c
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

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <wchar.h>

STRING* str_create() {
	STRING* str = (STRING*) malloc(sizeof(STRING));
	str->payload = '\0';
	str->next = NULL;
	str->previous = NULL;
	str->current = str;
	return str;
}

void str_clear(STRING* str) {
	int i=0;
	int size = str_size(str);
	
	for(i=0; i<size; i++) {
		str_delete(str, 0);
	}
}

STRING* str_substr(STRING* str, int start, int end) {
	STRING* sub = str_create();
	
	int i=0;
	for(i=start; i<(end<str_size(str)?end:str_size(str)); i++) {
		str_add(sub, str_get(str, i));
	}
	
	return sub;
}

void str_concat(STRING* str1, STRING* str2) {
	int i=0;
	for(i=0; i<str_size(str2); i++) {
		str_add(str1, str_get(str2, i));
	}
}

void str_insert(STRING* str, int index, wchar_t payload) {
	STRING* head = str;
	int i = 0;
	
	STRING* new_str = (STRING*) malloc(sizeof(STRING));
	new_str->payload = payload;
	
	if(index >= 0) {
		while(head != NULL) {
			if(i == index) {
				new_str->previous = head;
				
				STRING* s = head->next;

				new_str->next = s;
				head->next = new_str;

				if(new_str->next != NULL) {
					new_str->next->previous = new_str;
				}

				return;
			}

			head = head->next;
			
			i++;
		}
	}
}

void str_add(STRING* str, wchar_t payload) {
	str->current->next = (STRING*) malloc(sizeof(STRING));
	str->current->next->payload = payload;
	str->current->next->previous = str->current;
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

wchar_t str_top(STRING* str) {
	return str->current->payload;
}

int str_search(STRING* str, wchar_t value) {
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

wchar_t str_get(STRING* str, int index) {
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

int str_delete(STRING* str, int index) {
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
	free(head);
	head = NULL;
	
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
	wchar_t* ptr = malloc(sizeof(wchar_t) * str_size(str) + 1);
	
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
