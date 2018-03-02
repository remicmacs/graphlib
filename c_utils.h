/*******************************************************************************
 * c_utils.h created by Rémi B. on 24/01/2018
 *
 * Header file for c_utils.c
 * ****************************************************************************/
#define _GNU_SOURCE

#include <stdlib.h> // for rand()
#include <stdio.h>
#include <time.h> // for rand() seeding with time(NULL)
#include <string.h>
#include <fcntl.h> // for file control macros and utils
#include <limits.h> // for type max and min

typedef enum bool_ {false, true} bool;

/*
 * function to create an integer matrix of iHeight * iWidth and initializing
 * each element to iHeight * iWidth
 */
int ** createMatrix(int iHeight, int iWidth);

/*
 * function to display a matrix of integers
 */
void displayMatrix(int ** iMatrix, int iHeight, int iWidth);


/**
 * function to display a matrix of integers
 */
void displayCharMatrix(char ** iMatrix, int iHeight, int iWidth);

/**
 * swap function with no temp variable allocation
 */
void XORSwap(int * intA, int * intB);

/**
 * function drawRandInt
 * -----------------------------------------------------------------------------
 *  Wrapper function for drawRandIntHighLow
 *      Check whether first parameter is the lowest. If not, swap the parameters
 *      then call drawRandIntHighLow
 */
int drawRandInt(int iBoundA, int iBoundB);

/**
 * function drawRandIntHighLow
 * -----------------------------------------------------------------------------
 *  Function to draw a random integer between iMinBound and iMaxBound
 *
 *  A random int between INT_MIN et INT_MAX is drawn by rand(). Then it is
 *  fitted inside the range of [iMinBound and iMaxBound] doing :
 *      drawnInt % ()
 *  
 *  PLEASE NOTE THAT THIS FUNCTION USES rand(). Thus rand() must be seeded first
 *  thing in the main function of the program using this funcion
 *
 *  Inputs :
 *      Inputs are given in a specific order
 *      iMinBound { int } minimum bound to be drawn
 *      iMaxBound { int } maximum bound to be drawn
 *
 *  Output : { int } the drawn random integer
 *
 */
int drawRandIntHighLow(int iMinBound, int iMaxBound);

/**
 * procedure swapInt
 * -----------------------------------------------------------------------------
 *  Procedure to swap two ints
 */
void swapInt(int * intA, int * intB);

void swapChar(char * a, char * b);

/**
 * procedure stripChar
 * -----------------------------------------------------------------------------
 *  Procedure to strip char cRef from string strOrigin
 */
void stripChar(char * strOrigin, char cRef);
