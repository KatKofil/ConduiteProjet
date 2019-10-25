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
 * \file board.h
 * \brief Définitions des fonctions manipulant le type \ref board_t
 */

#ifndef BOARD_H
#define BOARD_H

/**
   \struct cell_t
   \brief Représente l'état d'une cellule
*/
typedef struct {
	int active : 1; /*!< Est-ce que cette cellule a été dévoilée? */
	int flagged : 1; /*!< Est-ce qu'un drapeau est sur la cellule?*/
	int bombe : 1;	/*!< Est-ce qu'une bombe est sur la cellule?*/
	int n : 5; /*!< Combien de bombes sont dans le voisinage de cette cellule?*/
} cell_t;

/**
   \union point_t
   \brief Représente un point 2D
 */
typedef union {
	struct {
		int x; /*!< Coordonné X */
		int y; /*!< Coordonné Y */
	};
	struct {
		int w; /*!< Largeur */
		int h; /*!< Hauteur */
	};
} point_t;

/**
   \union dim_t
   \brief Représente un point ou des dimensions 2D
 */
typedef point_t dim_t;

/**
   \struct board_t
   \brief Représente l'état d'un tableau de jeu
*/
typedef struct {
	cell_t *board; /*!< Pointeur vers l'état des cellules */
	point_t cursor; /*!< Position du curseur */
	int defeat;	/*!< Indicateur de défaite */
	int activated; /*!< Indicateur du nombre de cases activatiées */
	int flagged; /*!< Indicateur du nombre de cases flagged */
	dim_t dims; /*!< Dimension du tableau */
	int	nbombe; /*!< Nombre de bombes */
} board_t;

/// \brief Initialise une nouvelle partie avec les paramètres donnés
board_t *new_state(int height, int width, int nbombe);

/// \brief Déplace le curseur selon la direction donnée
void	manip_cursor(board_t *board, char move);

/// \brief Flagge la cellule du cursor
void	flag(board_t *board);

/// \brief Active la cellule du cursor
void	active(board_t *board);

/// \brief Défini si la partie est terminée
int		endgame(board_t *self);

/// \brief Gère l'affichage de l'état
void affichage(board_t *self);

/// \brief Affiche la carte révélée
void reveal(board_t *self);

/// \brief Libère la mémoire du board
void free_board(board_t *board);

#endif /* BOARD_H */