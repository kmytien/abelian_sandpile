# makefile for assignment0 -- sandpile, makes and cleans binaries
327_assignment0: 327_assignment0.c
	  	gcc 327_assignment0.c -o 327_assignment0 -lm
clean:
	rm -f 327_assignment0
