/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Function used to check if a map is valid or not
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"

void map_check(sokoban_t sokoban)
{

	int player = 0;

	for (int i = 0; i < sokoban.lines; i++) {
		for (int j = 0; sokoban.map_save[i][j] != '\0'; j++) {

			check_tile(i, j, sokoban);
			player += count_player(i, j, sokoban);
		}
	}
	
}

int check_tile(int y, int x, sokoban_t sokoban)
{
	if (sokoban.map_save[y][x] != '@' && sokoban.map_save[y][x] != '$'
	&& sokoban.map_save[y][x] != '#' && sokoban.map_save[y][x] != ' '
	&& sokoban.map_save[y][x] != '\n' && sokoban.map_save[y][x] != '.' 
	&& sokoban.map_save[y][x] != '+' && sokoban.map_save[y][x] != '*')
	{
		write(2, "Unknown read character in map\n", 26);
		exit(84);
	}
	return (0);
}

int count_case_number(int y, int x, sokoban_t sokoban)
{
	int i = 0;

	if (sokoban.map_save[y][x] == '$') {
		i++;
	}
	return (i);
}

int count_player(int y, int x, sokoban_t sokoban)
{
	int i = 0;

	if (sokoban.map_save[y][x] == '@') {
		i++;
	}
	return (i);
}
