/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Main function for the my_sokoban
*/

#include <unistd.h>
#include "../include/libmy.h"

int helper(void)
{
	my_putstr("USAGE\n");
	my_putstr("	./sokoban <-s> map <play_solution>\n\n");
	my_putstr("DESCRIPTION\n");
	my_putstr(" Arguments within <> are optional\n");
	my_putstr("    -s                 calls the AI solver\n");
	my_putstr("    play_solution      animates the solution found by the AI solver\n");
	return (0);
}
