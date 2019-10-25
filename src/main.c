#include <termios.h>
#include <board.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

struct termios termios_o;

void cleanup() {
	tcsetattr(0, 0, &termios_o);
}

char getkey() {
	int a;
	a = getchar();

	if (a == -1) {
		perror("getchar");
		exit(1);
	}
	if (a == 3)
		exit(1);	
	if(a == 0x1b) {
		a = getchar();
		if(a == 0x5b){
			a = getchar();
			if(a == 'C'){
				return 'd';
			}
			if(a == 'A'){
				return 'z';
			}
			if(a == 'B'){
				return 's';
			}
			if(a == 'D'){
				return 'q';
			}
		}

	}
	return a;
}
	
int main(int ac, char **av) {
	struct termios termios_m; 
	struct winsize w;
	int nbombs = 10;

	if (ac == 2)
		nbombs = atoi(av[1]);

	setvbuf(stdout, 0, _IOFBF, 0);
	atexit(cleanup);

	tcgetattr(0, &termios_o); //etat du terminal
	cfmakeraw(&termios_m);
	tcsetattr(0, 0, &termios_m); // modifie l'etat terminal 

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	board_t *state = new_state(w.ws_col / 2, w.ws_row - 2, nbombs);

	while(endgame(state) == 0){
		affichage(state);

		char key = getkey();
		if (key == ' ')
			active(state);
		if (key == 'f')
			flag(state);
		if (key =='z' || key =='d' || key =='s' || key =='q')
			manip_cursor(state, key);
	}

	reveal(state);
	free_board(state);
	return 0;
}