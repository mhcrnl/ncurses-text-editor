#include "editor.h"
#include <ncurses.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

void quit() {
	endwin();
	editor_close();
}

void setup_colors() {
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	
	initscr();
	noecho();
	cbreak();
    keypad(stdscr, TRUE);
    meta(stdscr, TRUE);
	atexit(quit);
	curs_set(0);
	setup_colors();
	
	editor_init();
	
	wint_t c = 0;
	editor_loop(c);
	while(c != 27) {
		//c = getch();
		get_wch(&c);
		
		clear();
		
		editor_loop(c);
		
		refresh();
	}
	
	return 0;
}
