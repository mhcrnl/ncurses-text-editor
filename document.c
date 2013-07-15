#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <wchar.h>
#include "document.h"
#include "string.h"

DOCUMENT* doc_create() {
	DOCUMENT* list = (DOCUMENT*) malloc(sizeof(DOCUMENT));
	list->payload = 0;
	list->next = NULL;
	list->current = list;
	return list;
}

void doc_add(DOCUMENT* list, STRING* payload) {
	list->current->next = (DOCUMENT*) malloc(sizeof(DOCUMENT));
	list->current->next->payload = payload;
	list->current = list->current->next;
	list->current->next = NULL;
}

STRING* doc_top(DOCUMENT* list) {
	return list->current->payload;
}

int doc_search(DOCUMENT* list, STRING* value) {
	DOCUMENT* head = list->next;
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

STRING* doc_get(DOCUMENT* list, int index) {
	DOCUMENT* head = list->next;
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

void doc_delete(DOCUMENT* list, int index) {
	if(index >= size(list) || index < 0) {
		return -1;
	}

	DOCUMENT* head = list->next;
	DOCUMENT* tail = list;

	int i=0;
	for(i=0; i<index; i++) {
		tail = head;
		head = head->next;
	}

	tail->next = head->next;
	list = tail;
}

int doc_size(DOCUMENT* list) {
	DOCUMENT* head = list->next;
	int s = 0;

	while(head != NULL) {
		head = head->next;
		s++;
	}

	return s;
}

void doc_free(DOCUMENT* list) {
	int i = 0;
	int size = str_size(list);
	
	for(i = 0; i < size; i++) {
		str_delete(list, 0);
	}
	
	free(list);
	list = NULL;
}

int main() {

	return 0;
}
