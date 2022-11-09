//gra szachy

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define white 0xDB
#define black 0xFF

bool quitApp = false;

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

void arrowHere(int realPosition, int arrowPosition){
    if (realPosition == arrowPosition){
        printf(" <--");
    } else{
        printf("    ");
    }
}

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

void menuPlay(){
    printf("1 option - PLAY");
}

void menuOptions(){
    int keyPressed = 0;
    while (keyPressed != 13){
    	system("cls");
    	printf("2 option - OPTIONS");
        keyPressed = getch();
    }
}

void menuQuit(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    
    int position = 1;
    int keyPressed = 0;

#define menuQuitMAX 2
#define menuQuitMIN 1

    while (keyPressed != 13){
        system("cls");
        printAtPosition((csbi.dwSize.X - 25) / 2, csbi.dwSize.Y / 2, (char *[]) {
                " _______________________ ",
                "|                       |",
                "|     Are you sure?     |",
                "|_______________________|"}, 4, false, 0, 0);

        keyPressed = getch();
    }
    quitApp = true;
}

void menu(){
    int position = 1;
    int keyPressed = 0;

#define MAX 3
#define MIN 1

    //https://www.kammerl.de/ascii/AsciiSignature.php <--- tej stronki użyłem do wygenerowania napisu
    char *chessHeader[] = {
            "  ..|'''.| '||'  '||' '||''''|   .|'''.|   .|'''.| \n",
            ".|'     '   ||    ||   ||  .     ||..  '   ||..  ' \n",
            "||          ||''''||   ||''|      ''|||.    ''|||. \n",
            "'|.      .  ||    ||   ||       .     '|| .     '||\n",
            " ''|....'  .||.  .||. .||.....| |'....|'  |'....|' \n"
    };
    //-----------------------------------------------------------------------------------------------
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    /*if(ret)
    {
        printf("Console Buffer Width: %d\n", csbi.dwSize.X);
        printf("Console Buffer Height: %d\n", csbi.dwSize.Y);

        for (int i = 0; i < csbi.dwSize.X; ++i) {
            printf(".");
        }
    }*/

    while (keyPressed != 13) {
        system("cls");

        printAtPosition((csbi.dwSize.X - 51) / 2, csbi.dwSize.Y / 3, chessHeader, 5, false, 0, 0);
        printAtPosition((csbi.dwSize.X - 25) / 2, csbi.dwSize.Y / 2 + 2, (char *[]) {
                " _____ __    _____ __ __ ",
                "|  _  |  |  |  _  |  |  |",
                "|   __|  |__|     |_   _|",
                "|__|  |_____|__|__| |_|  "}, 4, true, 1, position);
        printAtPosition((csbi.dwSize.X - 39) / 2, csbi.dwSize.Y / 2 + 7, (char *[]) {
                " _____ _____ _____ _ _____ _____ _____ ",
                "|     |  _  |_   _|_|     |   | |   __|",
                "|  |  |   __| | | | |  |  | | | |__   |",
                "|_____|__|    |_| |_|_____|_|___|_____|"}, 4, true, 2, position);
        printAtPosition((csbi.dwSize.X - 21) / 2, csbi.dwSize.Y / 2 + 12, (char *[]) {
                " _____ _____ _ _____ ",
                "|     |  |  |_|_   _|",
                "|  |  |  |  | | | |  ",
                "|__  _|_____|_| |_|  ",
                "   |__|              "}, 5, true, 3, position);

        keyPressed = getch();

        if (keyPressed == 80 && position != MAX) {
            position++;
        } else if (keyPressed == 72 && position != MIN) {
            position--;
        } else {
            position = position;
        }
    }

    system("cls");

    switch (position) {
        case 1:
            menuPlay();
            break;
        case 2:
            menuOptions();
            break;
        case 3:
            menuQuit();
            break;
        default:
            break;
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
    //robi duże okno takiej wielkości jaki mamy monitor
    /*HWND hWnd;
    SetConsoleTitle("Gra Szachy");
    hWnd = FindWindow(NULL, "Gra Szachy");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
    SMALL_RECT DisplayArea = {0, 0, 0, 0};

    SetConsoleScreenBufferSize(hOut, NewSBSize);

    DisplayArea.Right = NewSBSize.X - 1;
    DisplayArea.Bottom = NewSBSize.Y - 1;

    SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

    ShowWindow(hWnd, SW_MAXIMIZE);*/



    SetCMDSizeAndTitle(120, 40, "Szachy");

    int iSize = 8;

    //-----------------------------------------------------------------------------------------------
    while(quitApp != true){
    	menu();
    	//printBoard(iSize);
	}

    //printf("%c", getch());//getch() <--- wczytuje klawisz bez akceptacji enterem

    return 0;
}
