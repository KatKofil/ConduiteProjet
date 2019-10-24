#include <board.h>

board_t *new_state(int height, int width, int nbombe){
    board_t *board;

    board = (board_t *)malloc(sizeof(board_t *));
    board->dims.w = width;
    board->dims.h = height;
    board->nbombe = nbombe;
    board->cursor.x = board->dims.w / 2;
    board->cursor.y = board->dims.h / 2;    
    board->board = (cell_t *)malloc(sizeof(cell_t) * board->dims.w * board->dims.h);
    return board;
}