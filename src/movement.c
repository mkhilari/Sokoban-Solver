/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Function that make the player move
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"


sokoban_t move_box_left(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y][sokoban.player_x-2] == '$' || sokoban.map[sokoban.player_y][sokoban.player_x-2] == '*') {
		return (sokoban);
	} else if (sokoban.map[sokoban.player_y][sokoban.player_x-2] == '#') {
		return (sokoban);
	} else {
		sokoban.map[sokoban.player_y][sokoban.player_x-1] = '@';
		
		if(sokoban.map[sokoban.player_y][sokoban.player_x-2] == '.')
			sokoban.map[sokoban.player_y][sokoban.player_x-2] = '*';
		else
			sokoban.map[sokoban.player_y][sokoban.player_x-2] = '$';

		sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
		sokoban.player_x--;
	}
	return (sokoban);
}

sokoban_t move_box_right(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y][sokoban.player_x+2] == '$' || sokoban.map[sokoban.player_y][sokoban.player_x+2] == '*') {
		return (sokoban);
	} else if (sokoban.map[sokoban.player_y][sokoban.player_x+2] == '#') {
		return (sokoban);
	} else {
		sokoban.map[sokoban.player_y][sokoban.player_x+1] = '@';

		if(sokoban.map[sokoban.player_y][sokoban.player_x+2] == '.')
			sokoban.map[sokoban.player_y][sokoban.player_x+2] = '*';
		else
			sokoban.map[sokoban.player_y][sokoban.player_x+2] = '$';

		sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
		sokoban.player_x++;
	}
	return (sokoban);
}

sokoban_t move_box_up(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y-2][sokoban.player_x] == '$' || sokoban.map[sokoban.player_y-2][sokoban.player_x] == '*') {
		return (sokoban);
	} else if (sokoban.map[sokoban.player_y-2][sokoban.player_x] == '#') {
		return (sokoban);
	} else {
		sokoban.map[sokoban.player_y-1][sokoban.player_x] = '@';

		if(sokoban.map[sokoban.player_y-2][sokoban.player_x] == '.')
			sokoban.map[sokoban.player_y-2][sokoban.player_x] = '*';
		else
			sokoban.map[sokoban.player_y-2][sokoban.player_x] = '$';

		sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
		sokoban.player_y--;
	}
	return (sokoban);
}

sokoban_t move_box_down(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y+2][sokoban.player_x] == '$' || sokoban.map[sokoban.player_y+2][sokoban.player_x] == '*') {
		return (sokoban);
	} else if (sokoban.map[sokoban.player_y+2][sokoban.player_x] == '#') {
		return (sokoban);
	} else {
		sokoban.map[sokoban.player_y+1][sokoban.player_x] = '@';
		
		if(sokoban.map[sokoban.player_y+2][sokoban.player_x] == '.')
			sokoban.map[sokoban.player_y+2][sokoban.player_x] = '*';
		else
			sokoban.map[sokoban.player_y+2][sokoban.player_x] = '$';
			

		sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
		sokoban.player_y++;
	}
	return (sokoban);
}


sokoban_t move_left(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y][sokoban.player_x-1] != '#') {
		if (sokoban.map[sokoban.player_y][sokoban.player_x-1] == '$' || sokoban.map[sokoban.player_y][sokoban.player_x-1] == '*') {
			sokoban = move_box_left(sokoban);
		} else {
			sokoban.map[sokoban.player_y][sokoban.player_x-1] = '@';
			sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
			sokoban.player_x--;
		}
	}
	return (sokoban);
}

sokoban_t move_right(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y][sokoban.player_x+1] != '#') {
		if (sokoban.map[sokoban.player_y][sokoban.player_x+1] == '$' || sokoban.map[sokoban.player_y][sokoban.player_x+1] == '*') {
			sokoban = move_box_right(sokoban);
		} else {
			sokoban.map[sokoban.player_y][sokoban.player_x+1] = '@';
			sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
			sokoban.player_x++;
		}
	}
	return (sokoban);
}

sokoban_t move_up(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y-1][sokoban.player_x] != '#') {
		if (sokoban.map[sokoban.player_y-1][sokoban.player_x] == '$' || sokoban.map[sokoban.player_y-1][sokoban.player_x] == '*') {
			sokoban = move_box_up(sokoban);
		} else {
			sokoban.map[sokoban.player_y-1][sokoban.player_x] = '@';
			sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
			sokoban.player_y--;
		}
	}
	return (sokoban);
}

sokoban_t move_down(sokoban_t sokoban)
{
	if (sokoban.map[sokoban.player_y+1][sokoban.player_x] != '#') {
		if (sokoban.map[sokoban.player_y+1][sokoban.player_x] == '$' || sokoban.map[sokoban.player_y+1][sokoban.player_x] == '*') {
			sokoban = move_box_down(sokoban);
		} else {
			sokoban.map[sokoban.player_y+1][sokoban.player_x] = '@';
			sokoban.map[sokoban.player_y][sokoban.player_x] = ' ';
			sokoban.player_y++;
		}
	}
	return (sokoban);
}
