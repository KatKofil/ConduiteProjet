/*
    This file is part of MineSweeper.

    MineSweeper is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MineSweeper is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MineSweeper.  If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * \file affichage.c
 * \brief Fonctions manipulant l'affichage du jeu
 */

#include <stdio.h>
#include <stdlib.h>
#include <board.h>

#define CLEAR "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define MAG "\033[35m"
#define CYAN "\033[36m"

/**
   \const digits
   \brief Les chiffres possibles et leur couleur
*/

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

/*! \brief Dessine la zone de jeu
 *  \param self est un pointeur \ref board_t
 * 
 *  Affiche l'état du tableau
 */
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

/*! \brief Révèle l'entièreté du plateau
 *  \param self est un pointeur \ref board_t
 */
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
