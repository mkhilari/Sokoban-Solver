#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <signal.h>
#include "../../include/sokoban.h"

#define SIZE 4 
#define _XOPEN_SOURCE 500 

/**
 * Data structure containing the information about the game state 
 * representing the state of the game.
 */
struct state_s {
    char **map;
	int player_x;
	int player_y;
};

typedef struct state_s state_t;


/**
* Move type
*/
typedef enum moves {
	left = 0,
	right = 1,
	up = 2,
	down = 3
} move_t;




/**
 * Helper functions
 */
bool execute_move_t(sokoban_t *init_data, state_t *state, move_t move);
bool simple_corner_deadlock(sokoban_t *init_data, state_t *state);
bool winning_condition(sokoban_t *init_data, state_t *state);
void play_solution( sokoban_t init_data, char* solution );
void print_map(sokoban_t *init_data, state_t *state);

#endif

