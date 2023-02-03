#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define white 0xDB
#define black 0xFF

enum {
    KEY_ESC     = 27,
    KEY_ENTER   = 13,
    ARROW_UP    = 72,
    ARROW_DOWN  = 80,
    ARROW_LEFT  = 75,
    ARROW_RIGHT = 77
};

struct player{
    bool isWhite;
};

void SetCMDSizeAndTitle(short width, short height, char *title);
void printAtPosition(int x, int y, char **textToDraw, int sizeArray, bool isMenu, int realPosition, int arrowPosition);
void printCurrentPlayer(struct player currentPlayer, CONSOLE_SCREEN_BUFFER_INFO csbi);

int main(void){
    struct player currentPlayer = {true};

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

    //ustawienie wielkosci konsoli i jej nazwy
    SetCMDSizeAndTitle(120, 40, "Szachy");

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);

    //nazwa aktualnego gracza
    printCurrentPlayer(currentPlayer, csbi);
    //wyświetlanie planszy i pionków + aktualne wybrane pole


    getch();
    return 0;
}

void printLine(int iSize, int color1, int color2, int row){

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

void printCurrentPlayer(struct player currentPlayer, CONSOLE_SCREEN_BUFFER_INFO csbi){
    if (currentPlayer.isWhite){
        printAtPosition((csbi.dwSize.X - 25) / 2, csbi.dwSize.Y / 6, (char *[]) {
                " _______________________ ",
                "|                       |",
                "|        PLAYER 1       |",
                "|_______________________|"}, 4, false, 0, 0);
    }
    else{
        printAtPosition((csbi.dwSize.X - 25) / 2, csbi.dwSize.Y / 6, (char *[]) {
                " _______________________ ",
                "|                       |",
                "|        PLAYER 2       |",
                "|_______________________|"}, 4, false, 0, 0);
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

//drukowanie w danej pozycji
void printAtPosition(int x, int y, char **textToDraw, int sizeArray, bool isMenu, int realPosition, int arrowPosition){//<--- tutaj chcę przekazać tablicę
    COORD coord = {(short)x, (short)y};

    for (int i = 0; i < sizeArray; ++i) {
        coord.X = (short)x;
        coord.Y = (short)(y - sizeArray / 2 + i);
        if (isMenu) {
            if (realPosition == arrowPosition) {
                printf("\033[0;31m");
                if (i == sizeArray / 2) {
                    coord.X -= 4;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf("--> %s <--", textToDraw[i]);
                }else{
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                    printf("%s", textToDraw[i]);
                }
                printf("\033[0;37m");
            }else{
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                printf("%s", textToDraw[i]);
            }
        }else{
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            printf("%s", textToDraw[i]);
        }
    }
}