# Deadlock and Optimizations

## Simple Deadlock Detection 

1. For each goal sqaure, pull a box starting at the goal square in all directions. 

2. Mark squares that the block cannot be pulled to and sqaures that are walled off as a simple deadzone square. 

3. While solving, if a block is pushed to a simple deadzone sqaure, deadlock is reached, as the state cannot lead to a win. 

In `ai.c`, 
`void get_simple_deadlock_zone(sokoban_t *init_data, int** deadzone);` 

`bool is_simple_deadlock(sokoban_t *init_data, state_t *state, int** deadzone);` 


## Data Structures 
Used array of pointers to each created map and node structure for easier memory frees. 