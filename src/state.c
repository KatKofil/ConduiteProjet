#include <board.h>

board_t *new_state(int height, int width, int nbombe){
    board_t *board;

    board = (board_t *)malloc(sizeof(board_t *));
    board->dims.w = width;
    board->dims.h = height;
    board->nbombe = nbombe;
    board->cursor.x = board->dims.w / 2;
    board->cursor.y = board->dims.h / 2;    
    board->board = (cell_t *)calloc(sizeof(cell_t) , board->dims.w * board->dims.h);
    return board;
}

void    manip_cursor(board_t *board, char move){
    switch (move)
    {
    case 'w':
        board->cursor.y += 1;
        break;
    case 's':
        board->cursor.y -= 1;
        break;
    case 'a':
        board->cursor.x -= 1;
        break;
    case 'd':
        board->cursor.x += 1;
        break;

    default:
        break;
    }
    if (board->cursor.y < 0){
        board->cursor.y = 0;
    }
    if (board->cursor.y > board->dims.h){
        board->cursor.y = board->dims.h;
    }
    if (board->cursor.x < 0){
        board->cursor.x = 0;
    }
    if (board->cursor.x > board->dims.w){
        board->cursor.x = board->dims.w;
    }
}

void    flag(board_t *board){
    typedef cell_t line[board->dims.w];
    typedef line boardarr[board->dims.h];
    boardarr *arr = (void*)board->board;
    if ((*arr)[board->cursor.y][board->cursor.x].flagged == 1){
        (*arr)[board->cursor.y][board->cursor.x].flagged = 0;
        return;
    }
    (*arr)[board->cursor.y][board->cursor.x].flagged = 1;
}

void    active(board_t *board){
    typedef cell_t line[board->dims.w];
    typedef line boardarr[board->dims.h];
    boardarr *arr = (void*)board->board;
    (*arr)[board->cursor.y][board->cursor.x].active = 1;
}