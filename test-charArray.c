#include <stdio.h>

void printArray(char **array, int size){
    printf("%llu", sizeof(array));
    for (int i = 0; i < size; ++i) {
        printf("%s\n", array[i]);
    }
}

void foo(char **array, int size){
    for (int i = 0; i < size; ++i) {
        printf("%s\n", array[i]);
    }
}

int main()
{
    const char *array1[] = {"hello", "world", "its", "me"}; // use const because we're pointing to literals

    int array_size = sizeof(array1)/sizeof(array1[0]);

    printf("%s %s %s %s\n", array1[0], array1[1], array1[2], array1[3]);
    printf("%d\n", array_size);
    //printArray((char **) array1, array_size);//działa!!!

    //printArray((char *[]){"hello", "world", "its", "me"}, 4);
    foo((char *[]){"hello", "world", "its", "me"}, 4);
}