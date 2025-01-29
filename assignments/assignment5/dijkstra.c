/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Jamie Liu
 * Email: liujam@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"
#include <limits.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0


struct node{
	int id; 
	int cost;
	struct node* prev;
};

/*
This function reads the nodes and edges from the file and inserts them into an 
adjacency matrix (or the matrix provided)
 *
 * Params:
 *   n_nodes - num nodes
 *   n_edges - num edges
 *   matrix - static array to be filled from the file
 *
 * Return:
 *   returns nothing, just reads the file
 */

void readGraph(int n_nodes, int n_edges, int matrix[n_nodes][n_nodes], FILE *file){
	//declare source, destination node, and weights
	int source;
	int destination;
	int cost;

	for(int i=0; i<n_edges; i++){
		fscanf(file, "%d %d %d", &source, &destination, &cost);
		//place current source and destination to num in files
		matrix[source][destination] = cost;
	}
}

int main(int argc, char const *argv[]) {
	/*
	 * Open file and read the first two int: num of nodes, num of edges
	 */
	int n_nodes, n_edges;
	FILE* file = fopen(DATA_FILE, "r");
	fscanf(file, " %d %d ", &n_nodes, &n_edges);
	
	/*
	 * Write your code here to find the
	 * least-cost paths from node 0 to all other nodes in the graph.  Make sure
	 * to print out the least-cost paths you find at the end.
	 *
	 * FIXME: 
 	 */
//declare matrix, populate with 0
	int matrix[n_nodes][n_nodes];
	for(int i=0; i<n_nodes; i++){
		for(int j=0; j<n_nodes; j++){
			matrix[i][j] = 0;
		}
	}
	
	//read in
	readGraph(n_nodes, n_edges, matrix, file);

	fclose(file);

//create priority queue
	struct pq* queue = pq_create();

//create a set for costs and previous nodes to keep track
	int cost[n_nodes];
	int prev[n_nodes];

	for(int i=0; i<n_nodes; i++){
		cost[i] = INT_MAX;
		prev[i] = -1;
	}

	cost[START_NODE] = 0;
	pq_insert(queue, (void*)(long)(START_NODE), 0);

	while(pq_isempty(queue) == 0){
		// current acts as total cost of path to n
		int curr = (long int)pq_first(queue);
		pq_remove_first(queue);

		for(int i=0; i<n_nodes; i++){
			if(matrix[curr][i] !=0){
				int total_cost = cost[curr] + matrix[curr][i];
				if(total_cost< cost[i]){
					cost[i] = total_cost;
					prev[i] = curr;

					pq_insert(queue, (void*)(long)i, total_cost);
				}
			}
		}
	}

//print paths in array
	printf("Least cost paths from node: %d\n", START_NODE);
	for(int i=0; i<n_nodes; i++){
		if( i != START_NODE){
			printf("To node %d: ", i);
			printf("Cost: %d, Previous node: %d\n", cost[i], prev[i]);
		}
	}

	pq_free(queue);

	// 	// vertices[i]->cost = INT_MAX;
	// 	// vertices[i]->prev = NULL;
	// }

	// struct pq* queue = pq_create();
	// pq_insert(queue, START_NODE, 0);

	// while(pq_isempty(queue) != 0){
	// 	struct node* c = (pq_first_priority(queue));

	// 	struct node* N = pq_remove_first(queue); 
	// 	N->prev = pq_remove_first(queue);

		
	// }

	 
  return 0;
}