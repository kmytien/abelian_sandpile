#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORLD_LENGTH 23
#define WORLD_WIDTH 23

void initTable();
void printTable();
void update(int row, int cols,int  height);
void run(int row, int col, int fps);
void usleep(int fps);

int table[WORLD_LENGTH][WORLD_WIDTH];


//main function
//argc is number of parameters, argv[] is parameter array
int main(int argc, char* argv[]) {
    // default fps is
    int fps = 30;
    int j = 1, i, k;
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
    for (i = j; i <= argc; i+=3) { //i+=3??????????

        row = atoi(argv[i]);
        col = atoi(argv[i + 1]);
        height = atoi(argv[i + 2]);

        update(row, col, height);
    }


    // run simulation forever
    run(11, 11, fps);

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
    int i = row;
    int j = col;

    table[i][j] = height;

    // BASE CASE: if -1 or a sink, stays at height = -1
    if(table[i][j] < 0)
        table[i][j] = -1;

    // BASE CASE: if < 8 then add 1 to the heap and move on
    if(table[i][j] < 8)
        table[i][j]++;

    // else if its >= 8 then topple heap by
    else {
        table[i][j] = 1;

        if(i + 1 < 23)
            update(i + 1, j, table[i+1][j]++); //bottom box

        if(i - 1 >= 0)
            update(i-1, j, table[i-1][j]++); //top box

        if(j + 1 < 23)
            update(i, j + 1, table[i][j++]++); //right box

        if(j - 1 >= 0)
            update(i, j - 1, table[i][j-1]++); //left box

        if(i - 1 >= 0 && j - 1 >= 0)
            update(i - 1, j - 1, table[i-1][j-1]++); //top left

        if(i - 1 >= 0 && j + 1 < 23)
            update(i - 1, j + 1, table[i - 1][j+1]++); //top right

        if(i + 1 < 23 && j - 1 >= 0)
            update(i + 1, j - 1, table[i+1][j-1]++); //bottom left

        if(i + 1 < 23 && j + 1 < 23)
            update(i + 1, j + 1, table[i + 1][j + 1]++); //bottom right
    }
}

// infinite loop of update
void run(int row, int col, int fps) {
    while(true) {
      // updates row 11 col 11 and height 0 
      update(row, col, 0);
        printTable();

        // usleep pauses program for a sec
        usleep(1000000 / fps);
    }
}
