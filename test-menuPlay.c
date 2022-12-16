#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void SetCMDSizeAndTitle(short width, short height, char *title);
void printLine(int iSize, int color1, int color2, int row);
void printBoard(int iSize);

#define white 0xDB
#define black 0xFF

int iBoardSize = 8;
int board[8][8] = {
        2,3,4,6,5,4,3,2,
        1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,
        2,3,4,6,5,4,3,2
};

int focus[8][8];

int main(void){
    SetCMDSizeAndTitle(120, 40, "Szachy");

    focus[0][1]=1;
    printBoard(iBoardSize);

    getch();
}

void printLine(int iSize, int color1, int color2, int row){

    int cell = 6;

    for (int subLine = 0; subLine < cell / 2; ++subLine) {
        for (int column = 0; column < iSize; ++column) {
            for (int j = 0; j < cell; ++j) {
                if (subLine == cell / 2 / 2 && j == cell / 2 && board[row][column]){
                    printf("%d", board[row][column]);
                }
                else if(column % 2 == 0){
                    if (board[row][column] && focus[row][column]){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 76);
                        printf("%c", color1);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
                    }else{
                        printf("%c", color1);
                    }
                } else{
                    if (board[row][column] && focus[row][column]){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 76);
                        printf("%c", color2);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
                    }else{
                        printf("%c", color2);
                    }
                }
            }
        }

        printf("\n");
    }

}

void printBoard(int iSize){
    for (int row = 0; row < iSize; ++row) {
        if(row % 2 == 0){
            printLine(iSize, white, black, row);
        } else{
            printLine(iSize, black, white, row);
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