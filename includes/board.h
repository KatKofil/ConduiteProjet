#ifndef BOARD_H
#define BOARD_H

typedef struct {
	int active : 1;
	int flagged : 1;
	int bombe : 1;
	int n : 5;
} __attribute__((packed)) cell_t;

typedef union {
	struct {
		int x, y;
	};
	struct {
		int w, h;
	};
} point_t;

typedef point_t dim_t;

typedef struct {
	cell_t *board;
	point_t cursor;
	dim_t dims;
	int defeat;
	int	nbombe;
} board_t;


board_t *new_state(int height, int width, int nbombe);
void	manip_cursor(board_t *board, char move);
#endif /* BOARD_H */