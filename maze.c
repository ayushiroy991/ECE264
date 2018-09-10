#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"

static bool is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}

void _free_maze(Maze* maze){
	if (maze->maze_array[0] != NULL){
		for(int i=0; i<maze->n_row; i++){
			free(maze->maze_array[i]);
		}
	}
	if(maze->maze_array != NULL){
		free(maze->maze_array);
	}
	free(maze);
}

Maze* _malloc_maze(int num_rows, int num_cols){
	Maze *new_maze = malloc(sizeof(*new_maze));

	if(new_maze == NULL){
		return NULL;
	}

	new_maze->n_row = num_rows;
	new_maze->n_col = num_cols;

	new_maze->maze_array = (char**)malloc(num_rows*sizeof(new_maze->maze_array[0]));

	if(new_maze->maze_array == NULL){
		_free_maze(new_maze);
		return NULL;
	}

	for(int i=0; i<num_rows; i++){
		new_maze->maze_array[i] = (char *)malloc(num_cols*sizeof(new_maze->maze_array[0][0]));
	}

	if(new_maze->maze_array[0] == NULL){
		_free_maze(new_maze);
		return NULL;
	}

	return new_maze;
}


Maze* _read_maze(FILE* fp){
	int n_rows = 0;
	int n_cols = 0;
	//int char = 0;
//	int i = 0;

	fseek(fp, 0, SEEK_SET);

	while (fgetc(fp) != '\n'){
		n_cols = n_cols+1;
	}

	fseek(fp, 0, SEEK_SET);

	while (fgetc(fp) != EOF){
		if (fgetc(fp) == '\n'){
			n_rows = n_rows + 1;
		}
	}

	//printf("%d", n_rows);
	//printf("%d", n_cols);

	//struct Maze *maze;
	Maze* maze = _malloc_maze(n_rows, n_cols+1);

	maze->n_row = n_rows;
	maze->n_col = n_cols;

	//fopen(*fp, "r");

/*	if (fp == NULL){
		free(fp);
		return maze;
	}**/
	
	fseek(fp, 0, SEEK_SET);

	//char c = fgetc(fp);
	char c;
	int i = 0;
	int j = 0; 
	while (i<n_rows){
		//fputc(char, fp);
		//maze->cells[i] = ;
		while (j<=n_cols){
			c = fgetc(fp);
			if (c != '\n' && c != EOF){
				maze->maze_array[i][j] = c;
				//rintf("%c", c);maze->cells[i][j] = c;
				//rintf("%c", c);
				//c = fgetc(fp);
			}
			j++;
		}
	//	maze->cells[i][n_cols] = '\n';
		//c = fgetc(fp);
		//fseek(fp, 0, SEEK_CUR);
		i++;
		j=0;
	}	

	return maze;

	
}

bool _write_maze(const char* filename, const Maze* maze){
	FILE* w_file = fopen(filename, "w");

	if (w_file == NULL){
		return false;
	}
	
	int i =0;
	int j =0;

	while (i< maze->n_row){
		while (j < maze->n_col){
		//	fprintf(w_file, "%c", maze->cells[i][j]);
			fputc(maze->maze_array[i][j], w_file);
			j++;
		}
		fputc('\n', w_file);
		i++;
		j=0;
	}

	fclose(w_file);
	return true;

}

/* given a maze, current row (curr),                                     */
/* current column (curc), destination row (drow), destination col (dcol) */
/* current distance from source, determine the where to explore from the */
/* current location                                                      */
/* a recursive function: from the current location, try 'N', 'S', 'E',   */
/* 'W' locations one at a time if the attempt is successful, write the   */
/* direction in the file                                                 */

static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc,
                            int count, FILE *dfptr)
{
   // you may uncomment this and use the output here to trace the function
   // with sample5.pdf
   // printf("(%d, %d), %d\n", curr, curc, count);
   maze->maze_array[curr][curc] = VISITED;
   if ((curr == endr) && (curc == endc)) { // reach the destination 
      int i;
      for (i = 0; i < count; i++) { // create enough space in file
         fputc(VISITED, dfptr);
      }
      return count;
   }

   int found;
   if (is_path(maze, curr-1, curc)) {
      found = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('N', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr+1, curc)) {
      found = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('S', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr, curc+1)) {
      found = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('E', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (is_path(maze, curr, curc-1)) {
      found = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('W', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   return -1;
}

/* this is a function implemented by the instructor to illustrate           */
/* how to use a recursive function to go from the left-most top entrance to */
/* the right-most bottom exit of a maze.  The function will print the       */
/* directions taken to reach the bottom exit, without visiting a location   */
/* twice.  Note that the recursion may visit a location a few times         */
/* Given three filenames, first one is a given maze, the second one is to   */
/* be written with the directions, the third is the explored maze           */
/* If the maze file does not exist, the function immediately return -1 and  */
/* do nothing else                                                          */
/* the directions are in the form of a series of characters                 */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).            */
/* There should be just a single line, without a terminating newline        */
/* character. In other words, to the vi editor, it is an incomplete file    */
/* you are to assume that you start from the top-most, left-most entry      */
/* of the maze.  Therefore, the first direction is always 'S'               */
/* similarly, the last direction is always 'S'                              */
/* the returned value should be the number of steps taken to reach          */
/* the right-most bottom exit.  It is typically not the shortest distance   */
/* Note that the maze can be generated by amaze, or some combinations of    */
/* the maze expansion functions that you have written in PE08               */
/* you may assume that the maze file, if it exists, is in the correct format*/

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file)
{
   FILE *mfptr = fopen(maze_file, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   /* read the maze from mfptr */

   Maze *maze = _read_maze(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
   
   /* find the starting location, the top-most, left-most opening */
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->n_col; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }

   /* find the ending location, the bottom-most, right most opening */
   int endr, endc;
   endr = maze->n_row-1;
   for (endc = maze->n_col-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->n_col) {
      _free_maze(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      _free_maze(maze);
      return -1;
   }

   FILE *dfptr = fopen(directions_file, "w");
   if (dfptr == NULL) {
      _free_maze(maze);
      return -1;
   }
   int steps = _pathfinder_helper(maze, startr, startc, endr, endc, 0, dfptr);
   _write_maze(visited_file, maze);
   fclose(dfptr);
   _free_maze(maze);
   return steps;
}

/**
void _bfs(Maze *maze, char *directions_file, Coord source, Coord destination){
	int count; 
	
	bool visited[maze->n_row][maze->n_col];
	memset(visited, false, sizeof(visited));	
	visited[source->row][source->col] = true;

	Coord curr;

	int dest = 0;

	curr->row = destination->row;
	curr->col = destination->col;

	while (curr != source){
		
	}


}**/

void _shortest_path_helper(Maze *maze, Coord source, Coord destination, int row){
	if (row == 0){
		maze->maze_array[source.row][source.col] = 0;
		row++;
	}

	int i=0;
	int j=0;

	while (i< maze->n_row){
		while (j< maze->n_col){
			if (is_path(maze, i, j)){
				if(i-1 >= 0){
					if(maze->maze_array[i-1][j] == row-1){
						maze->maze_array[i][j] = row; 
					}
				}
				if (i+1 <maze->n_row){
					if(maze->maze_array[i+1][j] == row-1){
						maze->maze_array[i][j] = row; 
					}
				}
				if (j-1 >= 0){
					if(maze->maze_array[i][j-1] == row-1){
						maze->maze_array[i][j] = row;
					}
				}
				if (j+1 < maze->n_col){
					if(maze->maze_array[i][j+1] == row-1){
						maze->maze_array[i][j] = row;
					}
				}
			}
			j++;
		}
		j = 0;
			if (i == maze->n_row -1 && is_path(maze, destination.row, destination.col)){
				i = 0;
				row ++;
			}
			i++;
	}


}

int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
{

	FILE *mfptr = fopen(maze_file, "r");
    if (mfptr == NULL) {
       return -1;
    }
   
//	Coord source;
//	Coord destination; 

   // read the maze from mfptr 

    Maze *maze = _read_maze(mfptr);
    fclose(mfptr);
    if (maze == NULL) {
       return -1;
    }

	// find the starting location, the top-most, left-most opening 
    int startr, startc;
    startr = 0;
    for (startc = 0; startc < maze->n_col; startc++) {
       if (maze->maze_array[startr][startc] == PATH) {
          source.row = startr;
		  source.col = startc;
       }
    }

    // find the ending location, the bottom-most, right most opening 
     int endr, endc;
    endr = maze->n_row-1;
    for (endc = maze->n_col-1; endc >= 0; endc--) {
       if (maze->maze_array[endr][endc] == PATH) {
          destination.row =endr;
		  destination.col = endc;
       }
    } 

    // no starting location, deallocate and return 
    if (startc == maze->n_col) {
       _free_maze(maze);
       return -1;
    }
    // no ending location, deallocate and return 
    if (endc == -1) {
       _free_maze(maze);
       return -1;
    }
	
/**	bool VISITED[maze->n_row][maze->n_col];
	memset(VISITED, false, sizeof(VISITED));	
	visited[source->row][source->col] = true;**/

	Coord curr;

//	int dest = 0;

	curr.row = maze->n_row-1;
	curr.col = maze->n_col-1;

	_shortest_path_helper(maze, source, destination, 0);

	int final = maze->maze_array[curr.row][curr.col];

	FILE *dfptr = fopen(directions_file, "w");
    if (dfptr == NULL) {
       _free_maze(maze);
       return -1;
    }

	int i = 0;
	while (i<final){
		fputc(VISITED, dfptr);
		i++;
	}

	char direction = ' ';

	int j=1;
	while (j <= final){
		if (curr.row +1 <= destination.row && maze->maze_array[curr.row+1][curr.col] == final-j){
			curr.row += 1;
			direction = 'N';
		}
		else if(maze->maze_array[curr.row][curr.col+1] == final - j){
			curr.col +=1;
			direction = 'W';
		}
		else if(maze->maze_array[curr.row][curr.col-1] == final - j){
			curr.col -= 1;
			direction = 'E';
		}
		else if(curr.row-1 >= 0 && maze->maze_array[curr.row-1][curr.col] == final-j){
			curr.row -= 1;
			direction = 'S';
		}
		fseek(dfptr, -1, SEEK_CUR);
		fputc(direction, dfptr);
		fseek(dfptr, -1, SEEK_CUR);
		j++;
	}

//	fclose(fp);
	fclose(dfptr);
	
	
    return final;
}


int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
{
	char direction = PATH;
	int row = source.row;
	int col = source.col;
	int count = 0;

	FILE *fp;
	fp = fopen(maze_file, "r");

/**	if(maze_file == NULL){
		return -1;
	}**/

	
//	FILE *fp;
//	fp = fopen(maze_file, "r");

	if(fp == NULL){
		return -1;
	}
	
	Maze *maze = _read_maze(fp);

	fclose(fp);

	if(maze == NULL){
		return -1;
	}

	if(source.row != 0 || source.col > maze->n_col || source.col < 0 || destination.row != maze->n_row-1	|| destination.col > maze->n_col || destination.col <0){
		_free_maze(maze);
		return -1;
	}

	fp = fopen(directions_file, "r+");

	if(fp == NULL){
		_free_maze(maze);
		return -1;
	}

	fseek(fp, 0, SEEK_CUR);
	
	while(!feof(fp)){
		if (row>=0 && row< maze->n_row && col>=0 && col<maze->n_col){
			if(is_path(maze, row, col)){
				count++;
				maze->maze_array[row][col] = VISITED;
			}
			else {
				fclose(fp);
				_free_maze(maze);
				return -1;
			}	

			direction = fgetc(fp);

			if(direction == 'N'){
				row -= 1;
			}
			else if (direction == 'S'){
				row += 1;
			}
			else if (direction == 'E'){
				col += 1;
			}
			else if (direction == 'W'){
				col -= 1;
			}
		}
		else{
			fclose(fp);
			_free_maze(maze);
			return -1;
		}
	}

	fclose(fp);

	if (!(destination.row == row && destination.col == col)){
		_free_maze(maze);
		return -1;
	}
	return -1;
}

