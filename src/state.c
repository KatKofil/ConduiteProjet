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
 * \file state.c
 * \brief Fonctions manipulant le state du board
 */

#include <board.h>
#include <stdlib.h>
#include <time.h>

/*! \brief Place bombe on the board
 *  \param board is a pointer \ref board_t
 *  \param pos is a struct \ref point_t
 *  \return if a bombe is placed
 * 
 *  Use position to place bombe and update number of close bombe
 *  for neighboors
 */
static int place_bomb(board_t *board, point_t pos){
    typedef cell_t line[board->dims.w];
    typedef line boardarr[board->dims.h];
    boardarr *arr = (void*)board->board;
    if ((*arr)[pos.y][pos.x].bombe == 0){
        (*arr)[pos.y][pos.x].bombe = 1;
    
        const point_t neighboors[] = {
            {{pos.x - 1, pos.y - 1}}, {{pos.x, pos.y - 1}}, {{pos.x + 1, pos.y - 1}},
            {{pos.x - 1, pos.y}}                          , {{pos.x + 1, pos.y}},
            {{pos.x - 1, pos.y + 1}}, {{pos.x, pos.y + 1}}, {{pos.x + 1, pos.y + 1}},
        };
        
        for (int i = 0; i < 8; ++i) {
            point_t n = neighboors[i];
            if (n.y < 0 || n.x < 0)
                continue;
            if (n.y >= board->dims.h || n.x >= board->dims.w)
                continue;
		    (*arr)[n.y][n.x].n++;
        }
        return 1;
    }
    return 0;
}

/*! \brief Init the board

 *  \param width is the width of the board
 *  \param height is the height of the board
 *  \param nbombe is the number of bombe to place
 *  \return the board initialised
 *  
 *  Take input param to init the board and call place_bombe. 
 */
board_t *new_state(int width, int height, int nbombe){
    board_t *board;
    point_t pos; 

    srand(time(0));

    board = calloc(1, sizeof(board_t));
    board->dims.w = width > 0 ? width : 15;
    board->dims.h = height > 0 ? height : 15;
    board->nbombe = nbombe;
    board->cursor.x = board->dims.w / 2;
    board->cursor.y = board->dims.h / 2;    
    board->board = (cell_t *)calloc(sizeof(cell_t) , board->dims.w * board->dims.h);
    while (nbombe > 0){
        pos.x = rand() % board->dims.x;
        pos.y = rand() % board->dims.y;
        nbombe -= place_bomb(board, pos);
    }
    return board;
}

/*! \brief Change cursor state

 *  \param board is the state of board
 *  \param move is the move to apply to board.cursor 
 */
void    manip_cursor(board_t *board, char move){
    switch (move) {
    case 'z':
        board->cursor.y -= 1;
        break;
    case 's':
        board->cursor.y += 1;
        break;
    case 'd':
        board->cursor.x += 1;
        break;
    case 'q':
        board->cursor.x -= 1;
        break;
    default:
        break;
    }
    if (board->cursor.y < 0)
        board->cursor.y = 0;
    if (board->cursor.y >= board->dims.h)
        board->cursor.y = board->dims.h - 1;
    if (board->cursor.x < 0)
        board->cursor.x = 0;
    if (board->cursor.x >= board->dims.w)
        board->cursor.x = board->dims.w - 1;
}

/*! \brief Change cell's flag state

 *  \param board is the state of board
 */
void    flag(board_t *board) {
    typedef cell_t line[board->dims.w];
    typedef line boardarr[board->dims.h];
    boardarr *arr = (void*)board->board;
	if ((*arr)[board->cursor.y][board->cursor.x].flagged)
		board->flagged--;
	else
		board->flagged++;
    (*arr)[board->cursor.y][board->cursor.x].flagged ^= 1;
}


static void  active_helper(board_t *self, point_t pos) {
    typedef cell_t line[self->dims.w];
    typedef line boardarr[self->dims.h];
    boardarr *arr = (void*)self->board;

    if ((*arr)[pos.y][pos.x].flagged)
        return;
    if ((*arr)[pos.y][pos.x].active)
        return;
    (*arr)[pos.y][pos.x].active = 1;
	self->activated++;

    if((*arr)[pos.y][pos.x].n)
        return;
    
    const point_t neighboors[] = {
        {{pos.x - 1, pos.y - 1}}, {{pos.x, pos.y - 1}}, {{pos.x + 1, pos.y - 1}},
        {{pos.x - 1, pos.y}}                       , {{pos.x + 1, pos.y}},
        {{pos.x - 1, pos.y + 1}}, {{pos.x, pos.y + 1}}, {{pos.x + 1, pos.y + 1}},
    };

    for (int i = 0; i < 8; ++i) {
        point_t n = neighboors[i];
        if (n.y < 0 || n.x < 0)
            continue;
        if (n.y >= self->dims.h || n.x >= self->dims.w)
            continue;
		active_helper(self, n);
    }
}


/*! \brief Change active cell's state

 *  \param self is the state of board
 */
void    active(board_t *self) {
    typedef cell_t line[self->dims.w];
    typedef line boardarr[self->dims.h];
    boardarr *arr = (void*)self->board;

	point_t pos = self->cursor;
    if ((*arr)[pos.y][pos.x].bombe) {
		(*arr)[pos.y][pos.x].active = 1;
		self->defeat = 1;
        return;
	}
    active_helper(self, self->cursor);    
}


/*! \brief Change cursor state

 *  \param self is the state of board 
 */
int		endgame(board_t *self) {
	if (self->defeat)
		return -1;
	if (self->dims.w * self->dims.h - self->activated == self->nbombe)
		return 1;
	return 0;
}



/*! \brief free the board
 *  \param board is the state of board 
 */
void    free_board(board_t *board){
    free(board->board);
    free(board);
}