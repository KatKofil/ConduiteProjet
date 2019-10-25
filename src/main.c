
#include<termios.h>

char getkey(){
	int a;
	a = getchar();

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
	else{
		return a;
	}

}

int main(int ac, char **av){
	struct termios termios_o, termios_m; 
	puts(av[1]);

	termios_m = tcgetattr(0, &termios_o); //etat du terminal
	cfmakeraw(&termios_m);
	tcsetattr(0, 0, &termios_m); // modifie l'etat terminal 

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	board_t *state = new_state(w.ws_row, w.ws_col, atoi(av[1]));

	while(end(state) == 0){
		affichage(state);

		char key = getkey();
		if (key == ' ')
			action(state);
		if (key == 'f')
			flag(state);
		if (key =='z' || key =='d' || key =='s' || key =='q')
			mouvement(state, key);
	}

	reveal(state);
	tcsetattr(0, 0, &termios_o);



	return 0;
}