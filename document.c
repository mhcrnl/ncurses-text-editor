#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <wchar.h>
#include "document.h"
#include "string.h"

DOCUMENT* doc_create() {
	DOCUMENT* doc = (DOCUMENT*) malloc(sizeof(DOCUMENT));
	doc->payload = 0;
	doc->next = NULL;
	doc->current = doc;
	return doc;
}

void doc_clear(DOCUMENT* doc) {
	int i=0;
	int size = doc_size(doc);
	
	for(i=0; i<size; i++) {
		doc_delete(doc, 0);
	}
}

void doc_insert(DOCUMENT* doc, int index, STRING* payload) {
	DOCUMENT* head = doc;
	int i = 0;
	
	DOCUMENT* new_doc = (DOCUMENT*) malloc(sizeof(DOCUMENT));
	new_doc->payload = payload;
	
	if(index >= 0) {
		while(head != NULL) {
			if(i == index) {
				new_doc->previous = head;
				
				DOCUMENT* d = head->next;

				new_doc->next = d;
				head->next = new_doc;

				if(new_doc->next != NULL) {
					new_doc->next->previous = new_doc;
				}

				return;
			}

			head = head->next;
			
			i++;
		}
	}
}

void doc_add(DOCUMENT* doc, STRING* payload) {
	doc->current->next = (DOCUMENT*) malloc(sizeof(DOCUMENT));
	doc->current->next->payload = payload;
	doc->current = doc->current->next;
	doc->current->next = NULL;
}

void doc_add_ptr(DOCUMENT* doc, const char* ptr) {
	STRING* str = str_create();
	str_set(str, ptr);
	doc_add(doc, str);
}

void doc_add_ptr_w(DOCUMENT* doc, const wchar_t* ptr) {
	STRING* str = str_create();
	str_set_w(str, ptr);
	doc_add(doc, str);
}

STRING* doc_top(DOCUMENT* doc) {
	return doc->current->payload;
}

int doc_search(DOCUMENT* doc, STRING* value) {
	DOCUMENT* head = doc->next;
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

STRING* doc_get(DOCUMENT* doc, int index) {
	DOCUMENT* head = doc->next;
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
	return NULL;
}

int doc_delete(DOCUMENT* doc, int index) {
	if(index >= doc_size(doc) || index < 0) {
		return -1;
	}

	DOCUMENT* head = doc->next;
	DOCUMENT* tail = doc;

	int i=0;
	for(i=0; i<index; i++) {
		tail = head;
		head = head->next;
	}

	tail->next = head->next;
	doc = tail;
}

int doc_size(DOCUMENT* doc) {
	DOCUMENT* head = doc->next;
	int s = 0;

	while(head != NULL) {
		head = head->next;
		s++;
	}

	return s;
}

void doc_free(DOCUMENT* doc) {
	int i = 0;
	int size = doc_size(doc);
	
	for(i = 0; i < size; i++) {
		doc_delete(doc, 0);
	}
	
	free(doc);
	doc = NULL;
}
