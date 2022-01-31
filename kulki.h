#ifndef KULKI_H_INCLUDED
#define KULKI_H_INCLUDED

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <stdbool.h>
#include <string.h>
#define N 9

typedef struct kolejka
{
    int front, rear, size;
    int capacity;
    int* array;
}queue;

void chooseBall(GtkWidget* widget);
int isFull(queue* Q);
int isEmpty(queue* Q);
queue* createQueue(int capacity);
void enqueue(queue* Q, int item);
int dequeue(queue* Q);
bool isPath(int tab[N][N], int start, int dest);
int colorNum();
GtkWidget* putColor(int los);
int randCell();
void addBalls();
void deleteCorrectRow(int a, int b);
void newGame();
void nextBalls();
void putNextBalls();
GtkWidget* putColorM(int los);
char* intToString(int n);
void saveGame(GtkWidget* save);
void loadGame(GtkWidget* load);

#endif // KULKI_H_INCLUDED
