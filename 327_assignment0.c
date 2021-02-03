#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define WORLD_LENGTH 23
#define WORLD_WIDTH 23

void initTable();
void printTable();
void update(int row, int col);
void run(int row, int col, int fps);

int table[WORLD_LENGTH][WORLD_WIDTH];


//main function
//argc is number of parameters, argv[] is parameter array
int main(int argc, char* argv[]) {
    int fps = 30, j = 1, i;
    int row, col, height;

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
    for (i = j; i <= argc; i += 3) { //i+=3??????????

        row = atoi(argv[i]);
        col = atoi(argv[i + 1]);
        height = atoi(argv[i + 2]);
    }


    run(11, 11, fps);


    //run simulation forever
    //run(11, 11, 1);

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
    printf("\n");
}

//update the grid/run the game
void update(int row, int col) {
    int i = row, j = col;
    table[row][col]++; //= height;

    // BASE CASE: if -1 or a sink, stays at height = -1
    if (table[i][j] < 0)
        table[i][j] = -1;

    // BASE CASE: if < 8 then add 1 to the heap and move on
    if (table[row][col] < 8) {
       return;
    }

    // else if its >= 8 then topple heap by
    else if (table[row][col] > 8) {
        table[i][j] = 1;

        if(i + 1 < 23) {
            //update(i + 1, j); //bottom box
            table[i + 1][j]++;

            if (table[i + 1][j] > 8)
                update(i + 1, j);

            //i++;
            //update(i, j);
        }
        if(i - 1 >= 0) {
            //update(i - 1, j); //top box
            table[i - 1][j]++;

            if (table[i - 1][j] > 8)
                update(i - 1, j);
            //i--;
            //update(i, j);
        }
        if(j + 1 < 23) {
            //update(i, j + 1); //right box
            table[i][j + 1]++;

            if (table[i][j + 1] > 8)
                update(i, j + 1);
            //j++;
            //update(i, j);
        }
        if(j - 1 >= 0) {
            //update(i, j - 1); //left box
            table[i][j - 1]++;

            if (table[i][j - 1] > 8)
                update(i, j - 1);
            //j--;
            //update(i, j);
        }
        if(i - 1 >= 0 && j - 1 >= 0) {
            //update(i - 1, j - 1); //top left
            table[i - 1][j - 1]++;

            if (table[i - 1][j - 1] > 8)
                update(i - 1, j - 1);
            //i--;
            //j--;
            //update(i, j);
        }
        if(i - 1 >= 0 && j + 1 < 23) {
            //update(i - 1, j + 1); //top right
            table[i - 1][j + 1]++;

            if (table[i - 1][j + 1] > 8)
                update(i - 1, j + 1);
            //i--;
            //j++;
            //update(i, j);
        }
        if(i + 1 < 23 && j - 1 >= 0) {
            //update(i + 1, j - 1); //bottom left
            table[i + 1][j - 1]++;

            if (table[i + 1][j - 1] > 8)
                update(i + 1, j - 1);
            //i++;
            //j--;
            //update(i, j);
        }
        if(i + 1 < 23 && j + 1 < 23) {
            //update(i + 1, j + 1); //bottom right
            table[i + 1][j + 1]++;

            if (table[i + 1][j + 1] > 8)
                update(i + 1, j + 1);
            //i++;
            //j++;
            //update(i, j);
        }

    }
}

// infinite loop of update
// row col and heigh are 11 11 and 1 respectively
void run(int row, int col, int fps) {
    while(true) {
        printTable();
        update(row, col);

        usleep(1000000 / fps);
    }
}
