/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Functions used to check if the game is loosed
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"

void loose_check(sokoban_t sokoban)
{
	if( sokoban.map[sokoban.player_y+1][sokoban.player_x] == '$')
			storage_loose_check(sokoban.player_y+1, sokoban.player_x, sokoban);
	if( sokoban.map[sokoban.player_y-1][sokoban.player_x] == '$')
			storage_loose_check(sokoban.player_y-1, sokoban.player_x, sokoban);
	if( sokoban.map[sokoban.player_y][sokoban.player_x+1] == '$')
			storage_loose_check(sokoban.player_y, sokoban.player_x+1, sokoban);
	if( sokoban.map[sokoban.player_y][sokoban.player_x-1] == '$')
			storage_loose_check(sokoban.player_y, sokoban.player_x-1, sokoban);

}

void storage_loose_check(int y, int x, sokoban_t sokoban)
{
	if (sokoban.map[y][x] == '$') {
		if (((sokoban.map[y][x+1] == '#' && sokoban.map[y+1][x] == '#') ||
		(sokoban.map[y+1][x] == '#' && sokoban.map[y][x-1] == '#') ||
		(sokoban.map[y][x-1] == '#' && sokoban.map[y-1][x] == '#') ||
		(sokoban.map[y-1][x] == '#' && sokoban.map[y][x+1] == '#')) &&
		!is_goal_cell(y, x, sokoban ) ) {
			endwin();
			exit (1);
		}
	}
}

