#include "string.h"
#include "document.h"
#include <malloc.h>
#include <ncurses.h>

DOCUMENT* document;
STRING* current_line;
wchar_t current_letter;

int cursor_x;
int cursor_y;

void editor_init() {
	document = doc_create();
	current_line = str_create();
	doc_add_ptr_w(document, L"Test2123");
	doc_add_ptr_w(document, L"Test");
	doc_add_ptr_w(document, L"Test2");
	current_letter = 0;
	cursor_x = 0;
	cursor_y = 0;
}

void editor_loop(int input) {
	if(input == KEY_UP) {
		if(cursor_y > 0) {
			cursor_y--;
			if(cursor_x >= str_size(doc_get(document, cursor_y))) {
				cursor_x = str_size(doc_get(document, cursor_y));
			}
		}
	}
	else if(input == KEY_DOWN) {
		if(cursor_y < doc_size(document)-1) {
			cursor_y++;
			if(cursor_x >= str_size(doc_get(document, cursor_y))) {
				cursor_x = str_size(doc_get(document, cursor_y));
			}
		}
	}
	else if(input == KEY_LEFT) {
		if(cursor_x > 0) {
			cursor_x--;
		}
	}
	else if(input == KEY_RIGHT) {
		if(cursor_x < str_size(doc_get(document, cursor_y))) {
			cursor_x++;
		}
	}
	else if(input == KEY_ENTER || input == '\n') {
		STRING* s = str_create();
		str_set(s, "");
		cursor_x = 0;
		doc_insert(document, cursor_y, s);
		cursor_y++;
	}
	else if(input == KEY_DC) {
		str_delete(doc_get(document, cursor_y), cursor_x);
	}
	else if(input == 127) {
		if(cursor_x > 0) {
			cursor_x--;
			str_delete(doc_get(document, cursor_y), cursor_x);
		}
		else if(cursor_y > 0) {
			cursor_x = str_size(doc_get(document, cursor_y-1));
			str_concat(doc_get(document, cursor_y-1), 
				doc_get(document, cursor_y));
			doc_delete(document, cursor_y);
			cursor_y--;
		}
	}
	else if(input == '\t') {
		str_insert(doc_get(document, cursor_y), cursor_x, ' ');
		str_insert(doc_get(document, cursor_y), cursor_x, ' ');
		str_insert(doc_get(document, cursor_y), cursor_x, ' ');
		str_insert(doc_get(document, cursor_y), cursor_x, ' ');
	}
	else if(input >= ' ') {
		str_insert(doc_get(document, cursor_y), cursor_x, input);
		cursor_x++;
	}
	
	current_line = doc_get(document, cursor_y);
	current_letter = str_get(current_line, cursor_x);
	
	color_set(1, 0);
	
	int i=0;
	for(i=0; i<doc_size(document); i++) {
		wchar_t* c = str_to_pointer_w(doc_get(document, i));
		mvprintw(i, 0, "%ls", c);
		free(c);
	}
	
	color_set(2, 0);
	if(cursor_x < str_size(current_line)) {
		mvaddch(cursor_y, cursor_x, current_letter);
	}
	else {
		mvaddch(cursor_y, cursor_x, ' ');
	}
}

void editor_close() {
	doc_free(document);
	str_free(current_line);
}
