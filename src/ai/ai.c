#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "priority_queue.h"

/**
 * Retrieve solution and return a string containing the squence of moves
*/
char* save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	char *solution_string = malloc(sizeof(char) * solution_node->depth+1);
	solution_string[n->depth] = '\0';
	while (n->parent != NULL)
	{

		switch (n->move) {
		case up:
			if (n->parent->state.map[n->state.player_y][n->state.player_x] == '$')
				solution_string[n->depth-1] = 'U';
			else
				solution_string[n->depth-1] = 'u';
			break;

		case down:  
			if (n->parent->state.map[n->state.player_y][n->state.player_x] == '$')
				solution_string[n->depth-1] = 'D';
			else     
				solution_string[n->depth-1] = 'd';
			break;

		case left:  
			if (n->parent->state.map[n->state.player_y][n->state.player_x] == '$')
				solution_string[n->depth-1] = 'L';
			else    
				solution_string[n->depth-1] = 'l';
			break;

		case right: 
			if (n->parent->state.map[n->state.player_y][n->state.player_x] == '$')
				solution_string[n->depth-1] = 'R';
			else       
				solution_string[n->depth-1] = 'r';
			break;

		}

		n = n->parent;
	}
	return solution_string;
}

/**
 * Copy a src into a dst state
*/
void copy_state(sokoban_t* init_data, state_t* dst, state_t* src){

	dst->map = malloc(sizeof(char *) * init_data->lines);
	for ( int i = 0; i < init_data->lines; ++i ){
		int width = strlen(src->map[i]) + 1;
		dst->map[i] = malloc(width);    
		memcpy(dst->map[i], src->map[i], width);
	}

	dst->player_x = src->player_x;

	dst->player_y = src->player_y;

}

/**
 * Create the initial node
*/
node_t* create_init_node( sokoban_t* init_data ){

	node_t * new_n = (node_t *) malloc(sizeof(node_t));

	new_n->parent = NULL;	
	new_n->priority = 0;
	new_n->depth = 0;
	new_n->num_childs = 0;
	new_n->move = -1;
	new_n->state.map = malloc(sizeof(char *) * init_data->lines);

	for (int i = 0; i < init_data->lines; ++i)
	{
		int width = strlen(init_data->map[i]) + 1;
		new_n->state.map[i] = malloc(width);    
		memcpy(new_n->state.map[i], init_data->map[i], width);
	}

	new_n->state.player_x = init_data->player_x;

	new_n->state.player_y = init_data->player_y;
	return new_n;
}

/**
 * Create the a node from a parent node
*/
node_t* create_node( sokoban_t* init_data, node_t* parent ){

	node_t * new_n = (node_t *) malloc(sizeof(node_t));

	new_n->parent = parent;
	new_n->depth = parent->depth + 1;

	copy_state(init_data, &(new_n->state), &(parent->state));

	return new_n;
	
}

/**
 * Apply an action to node n, create a new node resulting from 
 * executing the action, and return if the player moved
*/
bool applyAction(sokoban_t* init_data, node_t* n, node_t** new_node, move_t action ){

	bool player_moved = false;

    *new_node = create_node( init_data, n );
    (*new_node)->move = action;
	(*new_node)->priority =  -(*new_node)->depth;

    player_moved = execute_move_t( init_data, &((*new_node)->state), action );	

	return player_moved;

}

/**
 * Book keeping variable and function to free memory once the solver finishes
*/
node_t** expanded_nodes_table;
unsigned expanded_nodes_table_size = 10000000; //10M
void update_explore_table(node_t* n, unsigned expanded_nodes ){
    if( expanded_nodes > expanded_nodes_table_size - 1){
	expanded_nodes_table_size *= 2;
	expanded_nodes_table = realloc( expanded_nodes_table, sizeof(node_t*) * expanded_nodes_table_size );
	
    }
    
    expanded_nodes_table[ expanded_nodes ] = n;

}

void free_memory(unsigned expanded_nodes ){
	for( unsigned i = 0; i < expanded_nodes; i++){
		free(expanded_nodes_table[ i ]);
    }
	free(expanded_nodes_table);
}

/**
 * Given a 2D map, returns a 1D map
*/
void flatten_map( sokoban_t* init_data, char **dst_map, char **src_map){

	int current_i = 0;
	for (int i = 0; i < init_data->lines; ++i)
	{
		int width = strlen(src_map[i]);
		for ( int j = 0; j < width; j++ ){
			(*dst_map)[current_i]  = src_map[i][j];
			current_i++;
		}
	}
}

/**
 * Find a solution by exploring all possible paths
 */
void find_solution(sokoban_t* init_data, bool show_solution)
{
	// Keep track of solving time
	clock_t start = clock();
	
	// Solution String containing the sequence of moves
	char* solution = NULL;

	HashTable hashTable;
	struct heap pq;

	// Statistics
	unsigned generated_nodes = 0;
	unsigned expanded_nodes = 0;
	unsigned duplicated_nodes = 0;
	// int max_depth = 0;
	unsigned solution_size = 0;

	// Choose initial capacity of PRIME NUMBER 
	// Specify the size of the keys and values you want to store once 
	// The Hash Table only accept a 1D key and value.
	ht_setup( &hashTable, sizeof(int8_t) * init_data->num_chars_map, sizeof(int8_t) * init_data->num_chars_map, 16769023);

	

	// Data structure to create a 1D representation of the map
	// Needed to interact with the hash table
	char* flat_map = calloc( init_data->num_chars_map, sizeof(char));

	// Initialize heap
	heap_init(&pq);

	// Initialize expanded nodes table. 
	// This table will be used to free your memory once a solution is found
	expanded_nodes_table = (node_t**) malloc( sizeof(node_t*) * expanded_nodes_table_size ); 


	// Add the initial node
	node_t* n = create_init_node( init_data );
	
	// Use the max heap API provided in priority_queue.h
	heap_push(&pq, n);
	
	/** 
	 * FILL IN THE GRAPH ALGORITHM 
	 * */

	// Get created maps 
	char*** maps = (char***) 
	malloc(sizeof(char**) * expanded_nodes_table_size);
	int numMaps = 0;

	// Get created nodes 
	node_t** nodes = (node_t**) 
	malloc(sizeof( node_t*) * expanded_nodes_table_size);
	int numNodes = 0;

	// Add initial map 
	maps[numMaps] = n->state.map;
	numMaps += 1;

	// Add initial node 
	nodes[numNodes] = n;
	numNodes += 1;

	// Get deadzone 
	int** deadzone = (int**) 
	malloc(sizeof(int*) * init_data->lines);

	int lineLength = count_columns(*init_data, 0);

	for (int i = 0; i < init_data->lines; i++) {

		// Create deadzone line 
		deadzone[i] = (int*) 
		malloc(sizeof(int) * lineLength);
	}

	get_simple_deadlock_zone(init_data, deadzone);
	
	// Get if priority queue empty 
	while (pq.count > 0) {

		// Get current node 
		n = heap_delete(&pq);

		// Add node to expanded 
		expanded_nodes_table[expanded_nodes] = n;
		expanded_nodes += 1;

		if (winning_condition(init_data, &(n->state))) {

			// Save win node 
			solution = save_solution(n);
			solution_size = n->depth;

			break;
		}

		for (int moveNum = 0; moveNum < SIZE; moveNum++) {

			// Get move 
			move_t move;

			if (moveNum == 0) {
				move = left;
			}

			if (moveNum == 1) {
				move = right;
			}

			if (moveNum == 2) {
				move = up;
			}

			if (moveNum == 3) {
				move = down;
			}

			// Apply move to new node 
			node_t* next;

			int playerMoved = applyAction(init_data, n, &next, move);
			generated_nodes += 1;

			// Add new map 
			maps[numMaps] = next->state.map;
			numMaps += 1;

			// Add new node 
			nodes[numNodes] = next;
			numNodes += 1;

			if (!playerMoved 
			|| simple_corner_deadlock(init_data, &(next->state))
			|| is_simple_deadlock(init_data, &(next->state), deadzone)) {

				// Dead end state 
				// free(next);

				continue;
			}

			// Get flatMap 
			flatten_map(init_data, &flat_map, next->state.map);

			if (ht_contains(&hashTable, flat_map)) {

				// flatMap already seen 
				duplicated_nodes += 1;
				// free(next);

				continue;
			}

			// Add flatMap to seen 
			ht_insert(&hashTable, flat_map, flat_map);

			// Add next to priority queue 
			heap_push(&pq, next);
		}
	}

	// Free heap 
	free(pq.heaparr);

	// Free maps 
	for (int i = 0; i < numMaps; i++) {

		// Free map 
		for (int j = 0; j < init_data->lines; j++) {

			// Free map line 
			free(maps[i][j]);
		}

		free(maps[i]);
		// printf("maps[%d] freed\n", i);
	}

	free(maps);

	// Free nodes 
	for (int i = 0; i < numNodes; i++) {

		// Free node 
		free(nodes[i]);
	}

	free(nodes);

	free(expanded_nodes_table);

	// Free deadzone 
	for (int i = 0; i < init_data->lines; i++) {

		// Free deadzone line 
		free(deadzone[i]);
	}

	free(deadzone);


	//----------------------------
	
	// Free Memory of HashTable, Explored and flatmap
	ht_clear(&hashTable);
	ht_destroy(&hashTable);
	// free_memory(expanded_nodes);
	free(flat_map);
	//----------------------------

	// Stop clock
	clock_t end = clock();
	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	// Show Soltion	
	if( show_solution && solution != NULL ) play_solution( *init_data, solution);

	endwin();

	if( solution != NULL ){
		printf("\nSOLUTION:                               \n");
		printf( "%s\n\n", solution);
		FILE *fptr = fopen("solution.txt", "w");
		if (fptr == NULL)
		{
			printf("Could not open file");
			return ;
		}
		fprintf(fptr,"%s\n", solution);
		fclose(fptr);
		
		free(solution);
	}


	printf("STATS: \n");
	printf("\tExpanded nodes: %'d\n\tGenerated nodes: %'d\n\tDuplicated nodes: %'d\n", expanded_nodes, generated_nodes, duplicated_nodes);
	printf("\tSolution Length: %d\n", solution_size);
	printf("\tExpanded/seconds: %d\n", (int)(expanded_nodes/cpu_time_used) );
	printf("\tTime (seconds): %f\n", cpu_time_used );
	
	
}

void solve(char const *path, bool show_solution)
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

	find_solution(&sokoban, show_solution);


	// Free initial sokoban 
	for (int i = 0; i < sokoban.lines; i++) {

		// Free map line 
		free(sokoban.map[i]);
		free(sokoban.map_save[i]);
	}

	if (sokoban.map != NULL) {

		free(sokoban.map);
		sokoban.map = NULL;
		// printf("sokoban->map freed\n");
	}

	if (sokoban.map_save != NULL) {

		free(sokoban.map_save);
		sokoban.map_save = NULL;
		// printf("sokoban->map_save freed\n");
	}

	if (sokoban.buffer != NULL) {

		free(sokoban.buffer);
		sokoban.buffer = NULL;
		// printf("sokoban->buffer freed\n");
	}

}

void get_simple_deadlock_zone(sokoban_t *init_data, int** deadzone) {

	// Get lineLength 
	int lineLength = count_columns(*init_data, 0);

	// printf("lineLength = %d\n", lineLength);

	// Mark goals 
	for (int i = 0; i < init_data->lines; i++) {

		for (int j = 0; j < lineLength; j++) {

			if (init_data->map[i][j] == '.' 
			|| init_data->map[i][j] == '+' 
			|| init_data->map[i][j] == '*') {

				// Goal at map[i][j] 
				deadzone[i][j] = 1;
			} else {

				deadzone[i][j] = 0;
			}
		}
	}

	// Expand deadzone 
	int newDeadSquares = 1;

	while (newDeadSquares > 0) {

		newDeadSquares = 0;

		// Get pull locations 
		for (int i = 0; i < init_data->lines; i++) {

			for (int j = 0; j < lineLength; j++) {

				if (deadzone[i][j] == 0) {
					
					// Currently dead square 
					continue;
				}

				// Pull left 
				if (j - 1 >= 0 
				&& init_data->map[i][j - 1] != '#') {

					// Can pull left 
					if (deadzone[i][j - 1] == 0) {

						deadzone[i][j - 1] = 1;
						newDeadSquares += 1;
					}
				}

				// Pull right 
				if (j + 1 < lineLength 
				&& init_data->map[i][j + 1] != '#') {

					// Can pull right 
					if (deadzone[i][j + 1] == 0) {

						deadzone[i][j + 1] = 1;
						newDeadSquares += 1;
					}
				}

				// Pull up 
				if (i - 1 >= 0 
				&& init_data->map[i - 1][j] != '#') {

					// Can pull up 
					if (deadzone[i - 1][j] == 0) {

						deadzone[i - 1][j] = 1;
						newDeadSquares += 1;
					}
				}

				// Pull down 
				if (i + 1 < lineLength 
				&& init_data->map[i + 1][j] != '#') {

					// Can pull down 
					if (deadzone[i + 1][j] == 0) {
						deadzone[i + 1][j] = 1;
						newDeadSquares += 1;
					}
				}
			}
		}

		// printf("newDeadSquares = %d\n", newDeadSquares);
	}

	// Print deadzone 
	for (int i = 0; i < init_data->lines; i++) {

		for (int j = 0; j < lineLength; j++) {

			// printf("%d ", deadzone[i][j]);
		}

		// printf("\n");
	}
}

bool is_simple_deadlock(sokoban_t *init_data, state_t *state, int** deadzone) {

	// return false;

	// Get lineLength 
	int lineLength = count_columns(*init_data, 0);

	// Check deadzone for crates 
	for (int i = 0; i < init_data->lines; i++) {

		for (int j = 0; j < lineLength; j++) {

			if (deadzone[i][j] == 0 
			& state->map[i][j] == '$') {

				// Box in deadzone 
				return true;
			}
		}
	}

	return false;
}


