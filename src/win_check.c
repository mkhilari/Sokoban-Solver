/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Function that check if the game is won
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"

void win_check(sokoban_t sokoban)
{
	for (int i = 0; i < sokoban.lines; i++) {
		for (int j = 0; sokoban.map_save[i][j] != '\0'; j++) {
			if (sokoban.map[i][j] == '$')
				return ;
		}
	}

	endwin();
	exit (0);
	
}