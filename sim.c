/**
 * Assignment: life
 * Section: (A, B, C)
 * Class: UCSD CSE30-wi20
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 * 
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
  // TODO:
  int aliveNeighbors = 0;
  int i;
  belem *tempStart = srcStart;

  //check neighbors
  //start 1 and -1 to account for borders
  for (i = 1; i < cols-1; i++)
  {	
	//north
	if (*(tempStart-cols) == 1)
	{
		aliveNeighbors++;
	}
	
	//south
	if (*(tempStart+cols) == 1)
	{
		aliveNeighbors++;
	}

	//east
	if (*(tempStart+1) == 1)
	{
		aliveNeighbors++;
	}

	//west
	if (*(tempStart-1) == 1)
	{
		aliveNeighbors++;
	}

	//northwest
	if (*(tempStart-cols-1) == 1)
	{
		aliveNeighbors++;
	}

	//northeast
	if (*(tempStart-cols+1) == 1)
	{
		aliveNeighbors++;
	}

	//southwest
	if (*(tempStart+cols-1) == 1)
	{
		aliveNeighbors++;
	}

	//southeast
	if (*(tempStart+cols+1) == 1)
	{
		aliveNeighbors++;
	}

  	//alive case
  	if (*tempStart == 1)
  	{
	  	if (aliveNeighbors == 0 || aliveNeighbors == 1 || aliveNeighbors >= 4)
	  	{
		  	*dest = 0;
	  	}

	  	if (aliveNeighbors == 2 || aliveNeighbors == 3)
	  	{
		  	*dest = 1;
	  	}

  	}

  	//dead case
  	if (*tempStart == 0)
  	{
	  	if (aliveNeighbors == 3)
	  	{
		  	*dest = 1;
	  	}
	  	else
	  	{
		  	*dest = 0;
	  	}
  	}

  	//reset to check next cell
  	aliveNeighbors = 0;
  	dest++;
  	tempStart++;
  }
   
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
  // TODO:
  int i;
  int row;
  //for each gen/step
  for (i = 0; i < steps; i++)
  {
	  //initalize doRow params for first row of board (first alive cell)
	  belem *nextBufferRow = (self->nextBuffer)+(self->numCols)+1;
	  belem *rowStart = (self->currentBuffer)+(self->numCols)+1;
	  belem *rowEnd = (self->currentBuffer)+(2*((self->numCols)-1));
	  int boardCols = self->numCols; 
	  
	  //for each row in board
	  //no bottom or top row so start at 1 and -1
	  for (row = 1; row < (self->numRows)-1; row++)
	  {
		  //process each row by checking neighbors and set to nextBuffer
		  doRow(nextBufferRow, rowStart, rowEnd, boardCols);

		  //set next dest, rowstart and rowEnd
		  nextBufferRow = nextBufferRow + boardCols;
		  rowStart = rowStart + boardCols;
		  rowEnd = rowStart + boardCols;
	  }

	  swapBuffers(self);
	  self->gen = (self->gen)+1;

  }
  

}




