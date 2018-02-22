/*******************************************************************************
 * c_utils.c created by Rémi B. on 24/01/2018                                  *
 *                                                                             *
 * Helper library to perform often needed functionalities                      *
 * ****************************************************************************/

#include "c_utils.h"

int ** createMatrix(int iHeight, int iWidth) {
    int ** iMatrix;
    int * iCurrentVector;
    int iIndexI, iIndexJ;
    iMatrix = (int **) malloc(iHeight * sizeof(int *));

    for (iIndexI = 0 ; iIndexI < iHeight ; iIndexI++) {
        iCurrentVector = (int *) malloc(iWidth * sizeof(int));

        for (iIndexJ = 0 ; iIndexJ < iWidth ; iIndexJ++) {
            *(iCurrentVector+iIndexJ) = iIndexI * iIndexJ;
            printf("%03d ", *(iCurrentVector+iIndexJ));
        }
        *(iMatrix+iIndexI) = iCurrentVector;
        printf("\n");
    }

    printf("\n\n");

    return iMatrix;
}

void displayMatrix(int ** iMatrix, int iHeight, int iWidth) {
    int iIndexI, iIndexJ;
    int * iCurrentVector;

    for (iIndexI = 0; iIndexI < iHeight ; iIndexI++) {
        iCurrentVector = *(iMatrix+iIndexI);
        for (iIndexJ = 0; iIndexJ < iWidth; iIndexJ++) {
            printf("%03d ", *(iCurrentVector+iIndexJ));
        }
        printf("\n");
    }
}

void displayCharMatrix(char ** iMatrix, int iHeight, int iWidth) {
    int iIndexI, iIndexJ;
    char * iCurrentVector;

    for (iIndexI = 0; iIndexI < iHeight ; iIndexI++) {
        iCurrentVector = *(iMatrix+iIndexI);
        for (iIndexJ = 0; iIndexJ < iWidth; iIndexJ++) {
            printf("%03d ", *(iCurrentVector+iIndexJ));
        }
        printf("\n");
    }
}

void XORSwap(int * intA, int * intB) {
    *intA ^= *intB;
    *intB ^= *intA;
    *intA ^= *intB;
}

int drawRandInt(int iBoundA, int iBoundB){
    if (iBoundB < iBoundA) swapInt(&iBoundA, &iBoundB);
    return drawRandIntHighLow(iBoundA, iBoundB);
}

int drawRandIntHighLow(int iMinBound, int iMaxBound){
    return ((rand() % (iMaxBound - iMinBound + 1) + iMinBound));
}

void swapInt(int * intA, int * intB){
    int iTmp;
    iTmp = *intA;
    *intA = *intB;
    *intB = iTmp;
}

void swapChar(char * a, char * b){
    char cTmp = *a;
    *a = *b;
    *b = cTmp;
}

void stripChar(char * strOrigin, char cRef) {
    int iOffset;
    iOffset = 0;

    while (*(strOrigin) != '\0') { // pass through string
        // If current char is the char to strip, augment offset
        if (*strOrigin == cRef) {
            iOffset += 1;
        } else if (iOffset != 0) { // else copy to current pos - offset
            *(strOrigin-iOffset) = *strOrigin;
        }
        strOrigin += 1;
    }
    // Endstring char copy
    *(strOrigin-iOffset) = '\0';
}

