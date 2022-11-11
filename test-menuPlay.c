#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define white 0xDB
#define black 0xFF

int iBoardSize = 8;

void printLine(int iSize, int color1, int color2){

    int cell = 6;

    for (int subLine = 0; subLine < cell / 2; ++subLine) {
        for (int i = 0; i < iSize; ++i) {
            for (int j = 0; j < cell; ++j) {
                if(i%2 == 0){
                    printf("%c", color1);
                } else{
                    printf("%c", color2);
                }
            }
        }

        printf("\n");
    }

}

void printBoard(int iSize){
    for (int i = 0; i < iSize; ++i) {
        if(i%2 == 0){
            printLine(iSize, white, black);
        } else{
            printLine(iSize, black, white);
        }
    }
}

void SetCMDSizeAndTitle(short width, short height, char *title) {
    COORD coord = { width, height };
    SMALL_RECT rect;

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = (short)(height - 1);
    rect.Right = (short)(width - 1);

    SetConsoleTitle(TEXT(title));

    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(void){
    SetCMDSizeAndTitle(120, 40, "Szachy");

    printBoard(iBoardSize);
    printf("U+265F");
    puts("■");
    puts("♟");
    getch();
}