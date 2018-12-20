# Space invaders on a Not Nintendo Switch. 

Any C or assembly files will automatically be built,
no need to edit the Makefile.

main.c:
	Contains the entry point main()
	
switch.h
	Sole header file, which includes all shared functions

graphics.c
	Contains the code to lightup pixel and send/rec SPI
	
Point.c
	Contains the behaviour of a point in a (128,32) system
	
assets.c
	Contains drawing functions for each asset

init.c
	Contains init for various components
	
vectors.S:
	Contains the interrupt handler and the exception handler

stubs.c:
	Contains stubs for functions run during micro controller
	initialization
