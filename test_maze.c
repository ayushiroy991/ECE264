#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
   if (argc < 2) 
   {
       return EXIT_FAILURE;
   }


   if (strcmp("-t", argv[1]) == 0){
   char* t1;
   char* t2;
   char* t3;
   char* t4;

   int step_count =0; 

		   char* maze_file = argv[2];
		   char* directions_file = argv[3];
		   char* visited_file = argv[4];

		Coord source = {
		   	.row = strtol(argv[5], &t1, 10),
			.col = strtol(argv[6], &t2, 10)
			};
			
		Coord destination = {
			.row = strtol(argv[7], &t3, 10),
			.col = strtol(argv[8], &t4, 10)
			};

		if (strlen(t1) != 0 || strlen(t2) != 0 || strlen(t3) !=0 || strlen(t4)!= 0){
			return EXIT_FAILURE;
		}

		step_count = simulate_movement(maze_file, directions_file, visited_file, source, destination);
		printf("%d\n", step_count);

	}
  
	else if (strcmp("-t", argv[1]) == 0) {
   char* t1;
   char* t2;
   char* t3;
   char* t4;

   int step_count =0; 

      if (argc != 5) { 
         return EXIT_FAILURE; 
      }
     
		//char* maze_file = argv[2];
		//char* directions_file = argv[3];

		Coord source= {
			.row = strtol(argv[4], &t1, 10),
			.col = strtol(argv[5], &t2, 10)
		};

		Coord destination = {
			.row = strtol(argv[6], &t3, 10),
			.col = strtol(argv[7], &t4, 10)
		};

		if (strlen(t1) !=0 || strlen(t2)!=0 || strlen(t3)!=0 || strlen(t4)!=0){
			return EXIT_FAILURE;
		}

	  step_count = dfs_shortest_path_directions(argv[2], argv[3], source, destination);
      printf("%d\n", step_count); 
   } else {
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
