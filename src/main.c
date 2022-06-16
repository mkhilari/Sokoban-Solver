/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Main function for the my_sokoban
*/

#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"
#include "ai/ai.h"

int main(int argc, char const **argv)
{
	if (argc < 2 || argc > 4)
		return (84);
	if (argv[1][0] == '-' && argv[1][1] == 'h')
		return(helper());
	else if (argv[1][0] == '-' && argv[1][1] == 's'){
		bool show_solution = false;
		if (argc > 3 && strcmp(argv[3], "play_solution") == 0)
			show_solution = true;
		solve(argv[2], show_solution);
		return 0;
	}
	else if (argv[1][0] != '-')
		return(play(argv[1]));

	return (84);
}
