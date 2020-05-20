/**
 * Assignment: life
 * Section: (A, B, C)
 * Class: UCSD CSE30-wi20
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){
  // TODO:

  boards_t *gameBoard = malloc(sizeof(boards_t));

  FILE *fp; //file to a pointer stream

  //open file for reading and assigning the file stream to fp
  if ((fp = fopen(initFileName, "r")) == NULL)
  {
	  //if fail return null
	  return NULL;
  }

  //get first two lines to store to numRows and numCols
  int row;
  int col;

  fscanf(fp, "%d", &row);
  fscanf(fp, "%d", &col);

  gameBoard->numRows = row;
  gameBoard->numCols = col;

  //create bufferA and bufferB
  int boardSize = (gameBoard->numRows)*(gameBoard->numCols);
  gameBoard->bufferA = malloc(sizeof(belem)*boardSize);
  gameBoard->bufferB = malloc(sizeof(belem)*boardSize);

  //set currentBuffer and nextBuffer
  gameBoard->currentBuffer = gameBoard->bufferA;
  gameBoard->nextBuffer = gameBoard->bufferB;

  //clear both current and next board buffers
  clearBoards(gameBoard);

  //read rows and cols with alive cells
  //keep border zero'ed out
  while (fscanf(fp, "%d %d", &row, &col) > 0)
  {
	  int cellPos = getIndex(gameBoard, row, col);
	 
	  
	  if (row == 0 || row == (gameBoard->numRows-1) || col == 0 || col == (gameBoard->numCols-1))
	  {
		  gameBoard-> currentBuffer[cellPos] = 0;
	  }
	  else
	  {
	  
	  
		  gameBoard->currentBuffer[cellPos] = 1;
	  }
  }

  //diff
  gameBoard->gen = 0;

  fclose(fp);

  return gameBoard;

}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
  // TODO:

  boards_t *bPtr = *bptrPtr;
  free(bPtr->bufferA);
  free(bPtr->bufferB);
  free(bPtr);
  //correct type?
  *bptrPtr = NULL;
  
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
  // TODO:

  int i;

  for (i = 0; i < (self->numCols)*(self->numRows); i++)
  {
	self->currentBuffer[i] = 0;
	self->nextBuffer[i] = 0;
  }

  }
  

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
  // TODO:
  
  belem *tempBuffer = self->currentBuffer;
  self->currentBuffer = self->nextBuffer;
  self->nextBuffer = tempBuffer;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
  // TODO:

  int index = row*(self->numCols)+col;

  return index;

}
  
