#include <curses.h>
#include "utils.h"



/**************************************
* Box movement given a state state  *
***************************************/

bool is_goal_loc(int y, int x, sokoban_t* init_data)
{
	return (init_data->map_save[y][x] == '.') || (init_data->map_save[y][x] == '+') || (init_data->map_save[y][x] == '*');
}


bool push_box_left(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y][state->player_x-2] == '$' || state->map[state->player_y][state->player_x-2] == '*') {
		return false;
	} else if (state->map[state->player_y][state->player_x-2] == '#') {
		return false;
	} else {
		state->map[state->player_y][state->player_x-1] = '@';
		if(state->map[state->player_y][state->player_x-2] == '.')
			state->map[state->player_y][state->player_x-2] = '*';
		else
			state->map[state->player_y][state->player_x-2] = '$';
		
		state->map[state->player_y][state->player_x] = ' ';
        if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        }
		state->player_x--;
	}
	return true;
}

bool push_box_right(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y][state->player_x+2] == '$' || state->map[state->player_y][state->player_x+2] == '*') {
		return false;
	} else if (state->map[state->player_y][state->player_x+2] == '#') {
		return false;
	} else {
		state->map[state->player_y][state->player_x+1] = '@';
		if(state->map[state->player_y][state->player_x+2] == '.')
			state->map[state->player_y][state->player_x+2] = '*';
		else
			state->map[state->player_y][state->player_x+2] = '$';
		state->map[state->player_y][state->player_x] = ' ';
         if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        }
		state->player_x++;
	}
	return true;
}

bool push_box_up(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y-2][state->player_x] == '$' || state->map[state->player_y-2][state->player_x] == '*') {
		return false;
	} else if (state->map[state->player_y-2][state->player_x] == '#') {
		return false;
	} else {
		state->map[state->player_y-1][state->player_x] = '@';

		if(state->map[state->player_y-2][state->player_x] == '.')
			state->map[state->player_y-2][state->player_x] = '*';
		else
			state->map[state->player_y-2][state->player_x] = '$';

		state->map[state->player_y][state->player_x] = ' ';
         if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        }
		state->player_y--;
	}
	return true;
}

bool push_box_down(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y+2][state->player_x] == '$' || state->map[state->player_y+2][state->player_x] == '*') {
		return false;
	} else if (state->map[state->player_y+2][state->player_x] == '#') {
		return false;
	} else {
		
		state->map[state->player_y+1][state->player_x] = '@';
		
		if(state->map[state->player_y+2][state->player_x] == '.')
			state->map[state->player_y+2][state->player_x] = '*';
		else
			state->map[state->player_y+2][state->player_x] = '$';
			
		state->map[state->player_y][state->player_x] = ' ';
        if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        }
		state->player_y++;
	}
	return true;
}



/**************************************
* Player Moves given a state state  *
***************************************/

bool move_left_player(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y][state->player_x-1] != '#') {
		if (state->map[state->player_y][state->player_x-1] == '$' || state->map[state->player_y][state->player_x-1] == '*') {
			return push_box_left(init_data, state);
		} else {
			state->map[state->player_y][state->player_x-1] = '@';
			state->map[state->player_y][state->player_x] = ' ';
            if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        	}
			state->player_x--;
            return true;
		}
	}
    return false;
}

bool move_right_player(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y][state->player_x+1] != '#') {
		if (state->map[state->player_y][state->player_x+1] == '$' || state->map[state->player_y][state->player_x+1] == '*') {
			return push_box_right(init_data, state);
		} else {
			state->map[state->player_y][state->player_x+1] = '@';
			state->map[state->player_y][state->player_x] = ' ';
            if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        	}
			state->player_x++;
            return true;
		}
	}
    return false;
}

bool move_up_player(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y-1][state->player_x] != '#') {
		if (state->map[state->player_y-1][state->player_x] == '$' || state->map[state->player_y-1][state->player_x] == '*') {
			return push_box_up(init_data, state);
		} else {
			state->map[state->player_y-1][state->player_x] = '@';
			state->map[state->player_y][state->player_x] = ' ';
            if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        	}
			state->player_y--;
            return true;
		}
	}   
    return false;
}

bool move_down_player(sokoban_t* init_data,state_t* state)
{
	if (state->map[state->player_y+1][state->player_x] != '#') {
		if (state->map[state->player_y+1][state->player_x] == '$' || state->map[state->player_y+1][state->player_x] == '*') {
			return push_box_down(init_data, state);
		} else {
			state->map[state->player_y+1][state->player_x] = '@';
			state->map[state->player_y][state->player_x] = ' ';
            if (is_goal_loc( state->player_y, state->player_x, init_data) && state->map[state->player_y][state->player_x] == ' ') {
	        	state->map[state->player_y][state->player_x] = '.';
        	}
			state->player_y++;
            return true;
		}
	}
    return false;
}


bool execute_move_t(sokoban_t* init_data, state_t* state, move_t move) {

    bool player_moved = false;

    //Determine which button is pushed
    switch (move) {
    case up:      
        player_moved = move_up_player(init_data, state);
        break;

    case down:       
        player_moved = move_down_player(init_data, state);
        break;

    case left:      
        player_moved = move_left_player(init_data, state);
        break;

    case right:        
        player_moved = move_right_player(init_data, state);
        break;

    }

	return player_moved;

	
}

/*****************************************************************************
* Function:    simple_corner_deadlock                                        *
* Parameters:  sokoban_t* init_data, state_t* state                          *
* Returns:     bool                                                          *
* Description: Check if box has been pusehd into a loc in a corner wall      *
*              and loc != destination                                        *
*****************************************************************************/


bool corner_check(int x, int y, sokoban_t* init_data, state_t* state){
    // Check if corner
    if (((state->map[y][x+1] == '#' && state->map[y+1][x] == '#') ||
        (state->map[y+1][x] == '#' && state->map[y][x-1] == '#') ||
        (state->map[y][x-1] == '#' && state->map[y-1][x] == '#') ||
        (state->map[y-1][x] == '#' && state->map[y][x+1] == '#')) &&
        !is_goal_loc( state->player_y, state->player_x, init_data) ) {
            return true;
    }
    return false;
}

bool simple_corner_deadlock(sokoban_t* init_data, state_t* state)
{
    bool deadlock = false;
    int x = state->player_x;
    int y = state->player_y;

    if (state->map[state->player_y + 1][state->player_x] == '$'){
        y = state->player_y + 1;
        deadlock = corner_check(x, y, init_data, state);
    }
    if( state->map[state->player_y-1][state->player_x] == '$'){
        y = state->player_y - 1;
        deadlock = corner_check(x, y, init_data, state);
    }
	if( state->map[state->player_y][state->player_x+1] == '$'){
		x = state->player_x + 1;
        deadlock = corner_check(x, y, init_data, state);
    }
	if( state->map[state->player_y][state->player_x-1] == '$'){
		x = state->player_x - 1;
        deadlock = corner_check(x, y, init_data, state);
    }

    return deadlock;
}


/*****************************************************************************
* Function:    winning_condition                                             *
* Parameters:  sokoban_t* init_data, state_t* state                          *
* Returns:     bool                                                          *
* Description: Check if all boxes are in a destination                       *
*****************************************************************************/


bool winning_condition(sokoban_t* init_data, state_t* state)
{
	
    for (int y = 0; y < init_data->lines; y++) {
            for (int x = 0; init_data->map_save[y][x] != '\0'; x++) {
                if (state->map[y][x] == '$')
                    return false;
            }
    }

    return true;

}

/*********
* MACROS *
*********/
#include <string.h>
#define TERMINAL_TYPE (strcmp(getenv("TERM"), "xterm") == 0 ? "rxvt" : \
  getenv("TERM"))

void play_solution( sokoban_t init_data, char* solution ){

	SCREEN *mainScreen = newterm(TERMINAL_TYPE, stdout, stdin);
	set_term(mainScreen);
	int cols = 1;
	for(int i = 0; i < init_data.lines; i++){
		if(strlen(init_data.map[i]) > (size_t) cols){
			cols = strlen(init_data.map[i]);
		}
	}
	WINDOW *mainWindow = newwin(init_data.lines, cols, 0, 0);

	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();
	
	for (long unsigned int i = 0; i <= strlen(solution); i++) { 
		touchwin(mainWindow);
		wnoutrefresh(mainWindow);
		doupdate();
		refresh();
		for (int i = 0; i < init_data.lines; i++)
			mvprintw(i, 0, init_data.map[i]);
		move(init_data.player_y, init_data.player_x);

		int key_pressed = 0;

		if( solution[i] == 'u' || solution[i] == 'U')
			key_pressed = KEY_UP;
		else if( solution[i] == 'd' || solution[i] == 'D')
			key_pressed = KEY_DOWN;	
		else if( solution[i] == 'l' || solution[i] == 'L')
			key_pressed = KEY_LEFT;	
		else if( solution[i] == 'r' || solution[i] == 'R')
			key_pressed = KEY_RIGHT;	
		init_data = key_check(init_data, key_pressed);
		init_data = check_zone_reset(init_data);
		usleep(500000);
	}
	touchwin(mainWindow);
	wnoutrefresh(mainWindow);
	doupdate();
	refresh();
	usleep(1500000);
}

void print_map(sokoban_t* init_data, state_t* state ){
	initscr();
	cbreak();
	noecho();
	clear();
	for (int i = 0; i < init_data->lines; i++){
		mvprintw(i, 0, state->map[i]);
		move(state->player_y, state->player_x);
	}
	refresh();
}
