/*
** EPITECH PROJECT, 2017
** PSU_my_sokoban_2017
** File description:
** Function that manage the game
** ----------
** Adapted by Nir Lipo, 2021
*/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/libmy.h"
#include "../include/sokoban.h"

/*********
* MACROS *
*********/
#include <string.h>
#define TERMINAL_TYPE (strcmp(getenv("TERM"), "xterm") == 0 ? "rxvt" : \
  getenv("TERM"))
SCREEN *mainScreen = NULL;
WINDOW *mainWindow = NULL;


int play(char const *path)
{
	/**
	 * Load Map
	*/
	sokoban_t sokoban = make_map(path, sokoban);
	
	/**
	 * Count number of boxes and Storage locations
	*/
	map_check(sokoban);

	/**
	 * Locate player x,y position
	*/
	sokoban = find_player(sokoban);
	
	sokoban.base_path = path;

	mainScreen = newterm(TERMINAL_TYPE, stdout, stdin);
	set_term(mainScreen);
	int cols = 1;
	for(int i = 0; i < sokoban.lines; i++){
		if(strlen(sokoban.map[i]) > (size_t) cols){
			cols = strlen(sokoban.map[i]);
		}
	}
	mainWindow = newwin(sokoban.lines, cols, 0, 0);

	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	clear();
	
	while (1) {
		// Do explicit refresh of window so no corruption occurs
		touchwin(mainWindow);
		wnoutrefresh(mainWindow);
		doupdate();
		for (int i = 0; i < sokoban.lines; i++)
			mvprintw(i, 0, sokoban.map[i]);
		move(sokoban.player_y, sokoban.player_x);
		sokoban = game_management(sokoban);
	}
}

sokoban_t game_management(sokoban_t sokoban)
{
	int key_pressed = 0;

	key_pressed = getch();
	sokoban = key_check(sokoban, key_pressed);
	sokoban = check_zone_reset(sokoban);
	loose_check(sokoban);
	win_check(sokoban);
	return (sokoban);
}
