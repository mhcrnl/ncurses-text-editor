#ifndef __DOCUMENT_H
#define __DOCUMENT_H

#include <wchar.h>
#include "string.h"

typedef struct _DOCUMENT {
	STRING* payload;
	DOCUMENT* current;
	DOCUMENT* next;
}DOCUMENT;

DOCUMENT* doc_create();
void doc_add(DOCUMENT* doc, STRING* payload);
STRING* doc_top(DOCUMENT* doc);
int doc_search(DOCUMENT* doc, STRING* value);
STRING* doc_get(DOCUMENT* doc, int index);
void doc_delete(DOCUMENT* doc, int index);
int doc_size(DOCUMENT* doc);
void doc_free(DOCUMENT* doc);

#endif
