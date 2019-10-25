#include <stdio.h>
#include <stdlib.h>
#include <board.h>

// Une ligne qui contient le nombre de mines présentes
// le nombre de flags placés
// au milieu de la ligne le smiley windows 95 
// afficher tout le jeu (2 boucles for)
// case non active = case x, si flag = drapeau genre p, si active = affiche contenu (0= espace, sinon chiffre)

#define CLEAR "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define MAG "\033[35m"
#define CYAN "\033[36m"

const char *digits[] = {
	"  ",
	BLUE "１" CLEAR,
	GREEN "２" CLEAR,
	RED "３" CLEAR,
	MAG "４" CLEAR,
	"５",
	"６",
	"７",
	"８"};

void affichage(board_t *self) {
	typedef cell_t line[self->dims.w];
	typedef line board[self->dims.h];

	printf("\033[2J");
	fflush(stdout);

	printf("%*s\r\n", self->dims.w + 3, "🤔");
	//
	board *b = (void*)self->board;

	const char *target = " ";
	for (int y = 0; y < self->dims.h; ++y) {
		for (int x = 0; x < self->dims.w; ++x) {
			cell_t c = (*b)[y][x];
			int r = !!(c.active);
			r += !!(c.flagged) * 2;
			if (c.bombe)
				target = (const char *[]) {"＃", 0, "🏳 " }[r];
			else {
				target = (const char *[]) { "＃", digits[c.n], "🏳 " }[r];
			}
			if (self->cursor.x == x &&
				self->cursor.y == y)
				printf("\033[7m%s\033[0m", target);
			else
				printf("%s", target);
		}
		puts("\r");
	}
	fflush(stdout);
}

void reveal(board_t *self) {
	typedef cell_t line[self->dims.w];
	typedef line board[self->dims.h];

	printf("\033[2J");
	fflush(stdout);
	const char *smileys[] = {"😵", "🤔", "😎"};
	int res = endgame(self);
	printf("%*s\r\n", self->dims.w + 3, smileys[1 + res]);
	board *b = (void*)self->board;

	const char *target = " ";
	for (int y = 0; y < self->dims.h; ++y) {
		for (int x = 0; x < self->dims.w; ++x) {
			cell_t c = (*b)[y][x];
			int r = !!(c.active);
			r += !!(c.flagged) * 2;
			if (c.bombe) {
				target = (const char *[]) {"💣", "\033[41m💣" CLEAR, "🏳 " }[r];
			} else {
				target = (const char *[]) { "＃", digits[c.n], "❌" }[r];
			}
			if (self->cursor.x == x &&
				self->cursor.y == y)
				printf("\033[7m%s\033[0m", target);
			else
				printf("%s", target);
		}
		puts("\r");
	}
	fflush(stdout);
}