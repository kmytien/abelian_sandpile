# makefile for assignment0 -- sandpile, makes and cleans binaries
sandpile: 327_assignment0.c
	  gcc 327_assignment0.c -o sandpile
clean:
	rm -f sandpile