#include <board.h>
#include <stdlib.h>
#include <time.h>

int place_bomb(board_t *board, point_t pos){
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

void    active_helper(board_t *self, point_t pos) {
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

int		endgame(board_t *self) {
	if (self->defeat)
		return -1;
	if (self->dims.w * self->dims.h - self->activated == self->nbombe)
		return 1;
	return 0;
}
