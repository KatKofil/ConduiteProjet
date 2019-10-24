#ifndef BOARD_H
#define BOARD_H

typedef struct {
	int active : 1;
	int flagged : 1;
	int n : 6;
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
	int	nbombe;
} board_t;

#endif /* BOARD_H */