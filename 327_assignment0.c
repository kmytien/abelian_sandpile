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
void moreThan8(int row, int col);

int table[WORLD_LENGTH][WORLD_WIDTH];


//main function
//argc is number of parameters, argv[] is parameter array
int main(int argc, char* argv[]) {
    int fps = 30, j = 1, i;
    int row = 11, col = 11, height = 1;

    initTable();

    //looking at fps
    if (argc > 1) {

        //looking at command line, if the first parameter is '--fps' then fps would be the 		number after
        if (strcmp("--fps", argv[1]) == 0) {
            fps = atoi(argv[2]);

            //j is j parameter in command line after ./sandpile
            //if no '--fps', then j = 1
            j = 3;
        }
    }

    //accept and pass on an unlimited number of parameters x & y
    //it is i+=3 because we're updating the net three numbers below
    for (i = j; i < argc; i += 3) {
        row = atoi(argv[i]);
        col = atoi(argv[i + 1]);
        height = atoi(argv[i + 2]);

        //accounting if user added sink
        if (height <= -1)
            table[row][col] = -1;
    }

    //making sure grains are placed correctly
    if (height == -1)
    	run(atoi(argv[j]), atoi(argv[j + 1]), fps);
    	
    else 
    	run(row, col, fps);
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

//print the grid
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

    //BASE CASE: if -1 or a sink, stays at height = -1
    if (table[row][col] != -1)
        table[row][col]++;

    //BASE CASE: if < 8 then add 1 to the heap and move on
    if (table[row][col] < 8 && table[row][col] != -1)
        return;

    //else if its >= 8 then topple sandpile
    else if (table[row][col] > 8){
        table[i][j] = 1;

        if(i + 1 < 23 && table[i + 1][j] != -1) {
            //bottom box
            table[i + 1][j]++;
            moreThan8(i + 1, j);
        }

        if(i - 1 >= 0 && table[i - 1][j] != -1) {
            //top box
            table[i - 1][j]++;
            moreThan8(i - 1, j);
        }

        if(j + 1 < 23 && table[i][j + 1] != -1) {
            //right box
            table[i][j + 1]++;
            moreThan8(i, j + 1);
        }

        if(j - 1 >= 0 && table[i][j - 1] != -1) {
            //left box
            table[i][j - 1]++;
            moreThan8(i, j - 1);
        }

        if(i - 1 >= 0 && j - 1 >= 0 && table[i - 1][j - 1] != -1) {
            //top left
            table[i - 1][j - 1]++;
            moreThan8(i - 1, j - 1);
        }

        if(i - 1 >= 0 && j + 1 < 23 && table[i - 1][j + 1] != -1) {
            //top right
            table[i - 1][j + 1]++;
            moreThan8(i - 1, j + 1);

        }

        if(i + 1 < 23 && j - 1 >= 0 && table[i + 1][j - 1] != -1) {
            //bottom left
            table[i + 1][j - 1]++;
            moreThan8(i + 1, j - 1);
        }

        if(i + 1 < 23 && j + 1 < 23 && table[i + 1][j + 1] != -1) {
            //bottom right
            table[i + 1][j + 1]++;
            moreThan8(i + 1, j + 1);
        }
    }
}

//helper function calling recursion (this just makes it look nicer and less crowded)
void moreThan8(int i, int j) {
    if (table[i][j] > 8)
        update(i, j);
}

//infinite loop of update
//row col and height are 11 11 and 1 respectively
void run(int row, int col, int fps) {
    while(true) {
        printTable();
        update(row, col);

        usleep(1000000 / fps);
    }
}
