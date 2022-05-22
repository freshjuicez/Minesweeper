#include <stdio.h> // minesweeper.c ; A rudimentary Minesweeper Game.

#include <stdlib.h>

#include <time.h>

#include <stdbool.h>

int n, m, mines, i, j;
void transformBoard(int array[][m], int, int, int, int, int);
bool validpos(int, int);
void generator();

bool validpos(int row, int col) {
  return (row >= 0) && (row < n) &&
    (col >= 0) && (col < m);
}
bool areAllRevealed(char (*gameBoard)[m], int a, int b){
  bool yesorno = 1;
    for(int l = a - 1; l < a + 2; l++){
      for(int r = b - 1; r < b + 2; r++){
        if (validpos(l, r) == 1){
        if (gameBoard[l][r] == '*'){
          yesorno = 0;
        }
        }
      }
    }
    return yesorno;
}
void zeroDetector(char (*gameBoard)[m], int transformedBoard[][m], int m, int a, int b){
    if(areAllRevealed(gameBoard, a, b) == 1){
      return;
    }
    else{
      for(int i = a - 1; i < a + 2; i++){
        for(int k = b - 1; k < b + 2; k++){
          if (validpos(i, k) == 1){
             if ((transformedBoard[i][k] == 0) && (areAllRevealed(gameBoard, i, k) == 0) && gameBoard[i][k] == '*'){
              gameBoard[i][k] = '-';
              zeroDetector(gameBoard, transformedBoard, m, i, k);
              }
            if (gameBoard[i][k] == '*'){
            gameBoard[i][k] = '-';
          }
        }
      }
    }
 }
}

   



int isMine(int a, int b, int transformedBoard[n][m]) {
  if (transformedBoard[a][b] == -1) {
    return 0;
  } else {
    return 1;
  }
}
int main(void) {
  srand(time(NULL));
  generator();

  return 0;
}

void generator(void) {
  char newgame;
  printf("Welcome to Minesweeper! \n");
  srand(time(NULL));
  int z, i, k, a, b, j;
  printf("Please enter desired amount of rows\n");
  scanf("%d", &n);
  printf("Please enter desired amount of columns \n");
  scanf("%d", &m);
  printf("Please enter desired amount of mines between 0 and the total squares, %d\n", n*m);
  scanf("%d", &z);
  int arr[m][n];
  i = 0;
  mines = z;
  // creates a mine with z mines, n rows, and m columns
  while (i < z) {
    a = rand() % n;
    b = rand() % m;
    if (arr[a][b] != -1) {
      arr[a][b] = -1;
      i++;
    } else {
      continue;
    }
  }

  printf("Please give a guess in (row, column) format. \n");
  printf("row: ");
  scanf("%d", &a);
  printf("\n");
  printf("Column: ");
  scanf("%d", &b);
  transformBoard(arr, a, b, m, n, mines);
  
}
//plays the game
void transformBoard(int array[][m], int a, int b, int row, int column, int mines) {
  int m, n, i, k, q, r, z, j, h;
  a = a - 1;
  b = b - 1;
  n = row;
  m = column;
  int openSquares;
  int transformedBoard[n][m];
  char gameBoard[n][m];
  for (q = 0; q < row; q++) {
    for (r = 0; r < column; r++) {
      if (array[q][r] == -1) {
        z = 0;
        transformedBoard[q][r] = -1;
        continue;
      } else {

        z = 0; // reset mine count to zero.
        if (validpos((q - 1), (r - 1)) == 1) {
          if (array[q - 1][r - 1] == -1) {
            z++;
          }
        }

        if (validpos((q - 1), r) == 1) {
          if (array[q - 1][r] == -1) {
            z++;
          }
        }
        if (validpos(q - 1, r + 1) == 1) {
          if (array[q - 1][r + 1] == -1) {
            z++;
          }
        }
        if (validpos(q, r - 1) == 1) {
          if (array[q][r - 1] == -1) {
            z++;
          }
        }
        if (validpos(q, r + 1) == 1) {
          if (array[q][r + 1] == -1) {
            z++;
          }
        }
        if (validpos(q + 1, r - 1) == 1) {
          if (array[q + 1][r - 1] == -1) {
            z++;
          }
        }
        if (validpos(q + 1, r) == 1) {
          if (array[q + 1][r] == -1) {
            z++;
          }
        }
        if (validpos(q + 1, r + 1) == 1) {
          if (array[q + 1][r + 1] == -1) {
            z++;
          }
        }

        transformedBoard[q][r] = z;
      }

    }
  }
  // generates gameboard
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      gameBoard[i][j] = '*';
    }
  }
  b = 0;
  while (isMine(a, b, transformedBoard) == 1) {
    openSquares = (n * m) - mines;
    printf("Initial open squares: %d \n", openSquares);
    if (transformedBoard[a][b] == 0) {
      zeroDetector(gameBoard, transformedBoard, m, a, b);
    } 
    else if(validpos(a, b)) {
            if (gameBoard[a][b] != '-') {
              gameBoard[a][b] = '-';
            }
          }

    printf("Your board after guessing is: \n");

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (gameBoard[i][j] == '-') {
          printf(" %d ", transformedBoard[i][j]);
        } else {
          printf(" * ");
        }
      }
      printf("\n");
    }


    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        if (gameBoard[i][j] != '*'){
          openSquares--;
        }
      }
    }

    if (openSquares == 0) {
      printf("Congratulations, you have won! \n");
      // prints out board, asks for new prompts to run again.
      printf("Your completed board was: \n");
      for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
          printf("%d, ", transformedBoard[i][j]);
        }
        printf("\n");
      }
    printf("Would you like to continue? \n 1 for yes, 0 for no");
    bool continues = scanf("%d");
      if(continues){
        getchar;
        generator();
      }
      else{
        exit(1);
      }

    }

    printf("There are %d open options \n", openSquares);
    printf("Please give a new guess in row, column format \n");
    scanf("%d",&a);
    printf("Please enter a number above in the range of 0 and n  \n");
    scanf("%d", &b);
    isMine(a, b, transformedBoard);
    while (gameBoard[a - 1][b - 1] == '-') {
      printf("Please give a NEW guess in row, column format \n");
      scanf("%d", & a);
      scanf("%d", & b);
    }
    a--;
    b--;
  }
  if (transformedBoard[a][b] == -1) {
    printf("Oh no! Thats a bomb! Nice try! \n");
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
        printf("%d, ", transformedBoard[i][j]);
      }
      printf("\n");
    }
  printf("Would you like to continue? \n 1 for yes\n");
    bool continues;
     scanf("%d", &continues);
      if(continues == 1){
        generator();
      }
      else{
        return;
      }
  }
  return;
}
