#include<stdio.h>
#include<ncurses.h>

int main(){
	int maxrows, maxcols;

	initscr();
	cbreak();
	noecho();

	clear();
	
	maxrows = LINES-1;
	maxcols = COLS-1;

	for(int i = 0;i<maxcols;i++){
		mvaddch(maxrows,i,'~');
	}
	
	char key = getch();
	endwin();
	
	printf("%c\n",key);

	return 0;
}
