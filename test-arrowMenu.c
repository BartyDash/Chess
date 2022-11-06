//test menu

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

void arrowHere(int realPosition, int arrowPosition){
    if (realPosition == arrowPosition){
        printf("---->>");
    } else{
        printf("      ");
    }
}

void menu() {
    int position = 1;
    int keyPressed = 0;

#define MAX 4
#define MIN 1

    while (keyPressed != 13) {

        system("cls");

        arrowHere(1, position);
        printf("1 option\n");
        arrowHere(2, position);
        printf("2 option\n");
        arrowHere(3, position);
        printf("3 option\n");
        arrowHere(4, position);
        printf("4 option\n");

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
            printf("1 option - menu");
            break;
        case 2:
            printf("2 option - menu");
            break;
        case 3:
            printf("3 option - menu");
            break;
        case 4:
            printf("4 option - menu");
            break;
        default:
            break;
    }
}

int main(void){

    menu();

    printf("%c", getch());

    return 0;
}