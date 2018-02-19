# Space invaders on a Not Nintendo Switch. 
By Ayub Atif and Wajd Tohme as part of KTH IS1200.

Project abstract:
https://docs.google.com/document/d/1TF4ntXGd8Ek8SFzuzT3Ju0wxF4fn5X0Q7KfAnj81Rpo/edit

This is an empty project template.
Just add your own code to the existing C or assembly files.
Any added C or assembly files will automatically be built,
no need to edit the Makefile.

main.c:
	Contains the entry point main()
	
switch.h
	Sole header file, which includes all shared functions

graphics.c
	Contains the code to lightup pixel and send/rec SPI
	
Point.c
	Contains the behaviour of a point in a (128,32) system

init.c
	Contains init for various components
	
vectors.S:
	Contains the interrupt handler and the exception handler

stubs.c:
	Contains stubs for functions run during micro controller
	initialization
