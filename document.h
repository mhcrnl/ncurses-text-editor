#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include <wchar.h>
#include "string.h"

typedef struct _DOCUMENT {
	STRING* payload;
	struct _DOCUMENT* current;
	struct _DOCUMENT* next;
	struct _DOCUMENT* previous;
}DOCUMENT;

DOCUMENT* doc_create();
void doc_clear(DOCUMENT* doc);
void doc_insert(DOCUMENT* doc, int index, STRING* payload);
void doc_add(DOCUMENT* doc, STRING* payload);
STRING* doc_top(DOCUMENT* doc);
int doc_search(DOCUMENT* doc, STRING* value);
STRING* doc_get(DOCUMENT* doc, int index);
int doc_delete(DOCUMENT* doc, int index);
int doc_size(DOCUMENT* doc);
void doc_free(DOCUMENT* doc);
void doc_add_ptr(DOCUMENT* doc, const char* ptr);
void doc_add_ptr_w(DOCUMENT* doc, const wchar_t* ptr);

#endif
