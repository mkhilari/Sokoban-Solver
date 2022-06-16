#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "node.h"
#include "priority_queue.h"

void solve(char const *path, bool show_solution);

void get_simple_deadlock_zone(sokoban_t *init_data, int** deadzone);
bool is_simple_deadlock(sokoban_t *init_data, state_t *state, int** deadzone);

#endif
