#include <stdio.h>
#include <stdlib.h>

#define WORLD_LENGTH 23
#define WORLD_WIDTH 23

int table[WORLD_LENGTH][WORLD_WIDTH];


//main function
//argc is number of parameters, argv[] is parameter array
int main(int argc, char* argv[]) {
    int fps = 0, i, j = 1;
    //we need to use atoi
    //we are scanning argv[]
    initTable();

    //looking at fps
    if (argc > 1) {
		    //could also be !strcmp("--fps", argv[1])
        //looking at command line, if the first parameter is '--fps' then fps would be the number after
    		if (strcmp("--fps", argv[1]) == 0)
    			fps = atoi(argv[2]);

          //j is j parameter in command line after ./sandpile
          //if no '--fps', then j = 1
          j = 3;
		}

    // accept and pass on an unlimited number of parameters y x h
    //it is i+=3 because we're updating the net three numbers below
    for (i = j; i =< argc; i+=3) { //i+=3??????????

        row = atoi(argv[i]);
        col = atoi(argv[i + 1]);
        height = atoi(argv[i + 2]);

        update(row, col, height);
    }

    // run simulation forever
    run();

}

//initialize the grid with zeros
void initTable() {
    int l, w;

    for (l = 0; l < WORLD_LENGTH; l++) {
  			for (w = 0; w < WORLD_WIDTH; w++) {
  			     table[l][w] = 0;
  			}
		}
}

//print the grid - DONE
void printTable() {
    int i, j;
    for (i = 0; i < WORLD_LENGTH; i++) {
        for (j = 0; j < WORLD_WIDTH; j++) {
            if (table[i][j] == -1)
                printf("#");
            else
                printf("%d", table[i][j]);
        }
        printf("\n");
    }
}

//update the grid/run the game
void update(int row, int col, int height) {
    int num = table[row][col];
    int[][] nextSandpile = new int[row][col];


      for(int i = 0; i < 23; i++) {
    			for(int j = 0; j < 23; j++) {

              //if -1 or a sink, stays at height = -1
              if(table[i][j] < 0)
                nextSandpile[i][j] = -1;

              // if < 9 then everything in table gets put in nextSandpile
              if(num < 9)
                nextSandpile[i][j] = table[i][j];

      			  if(num >= 9) {
                nextSandpile[i][j] += (num - 9);

            			if(i + 1 < 23)
            						nextSandpile[i+1][j]++;

            			if(i - 1 >= 0)
            						nextSandpile[i-1][j]++;

            			if(j + 1 < 23)
            						nextSandpile[i][j+1]++;

            			if(j - 1 >= 0)
            						nextSandpile[i][j-1]++;
      				}
    		 }
    }

    table = nextSandpile;
    printTable(nextSandpile);
}

//infinite loop of update
void run() {
    while(true) {
        update();
    }
}
