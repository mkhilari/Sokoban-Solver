/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Check zone
** ----------
** Adpated by Nir 2021
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"

sokoban_t check_zone_reset(sokoban_t sokoban)
{
	sokoban = reset_zone(sokoban.player_y+1, sokoban.player_x, sokoban);
	sokoban = reset_zone(sokoban.player_y-1, sokoban.player_x, sokoban);
	sokoban = reset_zone(sokoban.player_y, sokoban.player_x+1, sokoban);
	sokoban = reset_zone(sokoban.player_y, sokoban.player_x-1, sokoban);

	return (sokoban);
}

sokoban_t reset_zone(int y, int x, sokoban_t sokoban)
{
	if ( is_goal_cell(y, x, sokoban )  && sokoban.map[y][x] == ' ') {
		sokoban.map[y][x] = '.';
		return(sokoban);
	}
	return (sokoban);
}

