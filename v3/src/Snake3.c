/*
    Snake
    Version 3.1 alpha
    Copyright (C) 2007 Bernhard Waldbrunner
    Latest Revision: Wed, 03-07-07
*/

///DIRECTIVES//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <windows.h>

typedef char bool;
#define true  1
#define false 0

///PROTOTYPES//////////////////////////////////////////////////////////////////

void draw_background (void);
void transition (void);
void transition_reverse (void);
int game (int, short, bool, char*);

///MAIN////////////////////////////////////////////////////////////////////////

void main (void)
{
    char cmd = 0;
    bool is_walls = false;
    short level = 5;
    int record = 0;
    textmode(C80); _setcursortype(_NOCURSOR);
    transition_reverse(); draw_background();
    do {
        if (cmd=='n') game(record, level, is_walls, "");
        else if (cmd=='r') game(record, level, is_walls, "recording");
        textbackground(BLACK);
        textcolor(YELLOW); gotoxy(67, 3); cprintf("N");
        textcolor(WHITE); cprintf("ew Game");
        textcolor(YELLOW); gotoxy(67, 5); cprintf("R");
        textcolor(WHITE); cprintf("eplay");
        textcolor(YELLOW); gotoxy(67, 7); cprintf("Q");
        textcolor(WHITE); cprintf("uit");
    } while ((cmd = getch())!=033 && cmd!='q');
} // main()

///SUBS////////////////////////////////////////////////////////////////////////

void draw_background (void)
{
    int i;
    gotoxy(1, 9);
    cprintf(
        "      \xB1\xB1\xB1\xB1   \xB1    \xB1   \xB1\xB1\xB1\xB1   "
        "\xB1   \xB1  \xB1\xB1\xB1\xB1\xB1          \xB1  \xB1  \xB1\n\r     "
        "\xB1    \xB1  \xB1\xB1   \xB1  \xB1    \xB1  \xB1  \xB1 "
        "  \xB1             \xB1  \xB1  \xB1\n\r     "
        "\xB1       \xB1 \xB1  \xB1  \xB1    \xB1  \xB1 \xB1    \xB1          "
        "  \xB1  \xB1  \xB1\n\r     "
        " \xB1\xB1\xB1\xB1   \xB1  \xB1 \xB1  \xB1    \xB1  \xB1\xB1     \xB1"
        "\xB1\xB1\xB1        \xB1  \xB1  \xB1\n\r     "
        "     \xB1  \xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1  \xB1 \xB1    "
        "\xB1          \xB1  \xB1  \xB1\n\r     "
        "\xB1    \xB1  \xB1    \xB1  \xB1    \xB1  \xB1  \xB1   \xB1         "
        "\xB1  \xB1  \xB1\n\r     "
        " \xB1\xB1\xB1\xB1   \xB1    \xB1  \xB1    \xB1  \xB1   \xB1  \xB1\xB1"
        "\xB1\xB1\xB1    \xB1  \xB1  \xB1"
    );
    gotoxy(13, 18);
    cprintf("Copyright \xB8 2007 Bernhard Waldbrunner");
    for (i = 1; i<=25; i++) {
        gotoxy(63, i); cprintf("\xB0\xB1\xB2");
    }
} // draw_background()


void transition (void)
{
    int i, j;
    textbackground(BLACK); clrscr();
    textcolor(BLACK); textbackground(BLUE);
    for (i = 1; i<=32; i++) {
        gotoxy(33-i, 13-(int)((double)i/32*12)); cprintf("\xDA");
        for (j = 1; j<i*2; j++) cprintf("\xC4");
        cprintf("\xBF");
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33-i, 13-(int)((double)i/32*12)+j);
                cprintf("\xB3");
            }
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33+i, 13-(int)((double)i/32*12)+j);
                cprintf("\xB3");
            }
        gotoxy(33-i, 13+(int)((double)i/32*12)); cprintf("\xC0");
        for (j = 1; j<i*2; j++) cprintf("\xC4");
        cprintf("\xD9");
        Sleep(5);
        gotoxy(33-i, 13-(int)((double)i/32*12)); cprintf(" ");
        for (j = 1; j<i*2; j++) cprintf(" ");
        cprintf(" ");
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33-i, 13-(int)((double)i/32*12)+j);
                cprintf(" ");
            }
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33+i, 13-(int)((double)i/32*12)+j);
                cprintf(" ");
            }
        gotoxy(33-i, 13+(int)((double)i/32*12)); cprintf(" ");
        for (j = 1; j<i*2; j++) cprintf(" ");
        cprintf(" ");
    }
} // transition()


void transition_reverse (void)
{
    int i, j;
    textbackground(BLACK); clrscr();
    textcolor(BLACK); textbackground(BLUE);
    for (i = 32; i>=1; i--) {
        gotoxy(33-i, 13-(int)((double)i/32*12)); cprintf("\xDA");
        for (j = 1; j<i*2; j++) cprintf("\xC4");
        cprintf("\xBF");
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33-i, 13-(int)((double)i/32*12)+j);
                cprintf("\xB3");
            }
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33+i, 13-(int)((double)i/32*12)+j);
                cprintf("\xB3");
            }
        gotoxy(33-i, 13+(int)((double)i/32*12)); cprintf("\xC0");
        for (j = 1; j<i*2; j++) cprintf("\xC4");
        cprintf("\xD9");
        Sleep(5);
        gotoxy(33-i, 13-(int)((double)i/32*12)); cprintf(" ");
        for (j = 1; j<i*2; j++) cprintf(" ");
        cprintf(" ");
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33-i, 13-(int)((double)i/32*12)+j);
                cprintf(" ");
            }
        if (i>1)
            for (j = 1; j<(int)((double)i/32*12)*2; j++) {
                gotoxy(33+i, 13-(int)((double)i/32*12)+j);
                cprintf(" ");
            }
        gotoxy(33-i, 13+(int)((double)i/32*12)); cprintf(" ");
        for (j = 1; j<i*2; j++) cprintf(" ");
        cprintf(" ");
    }
} // transition_reverse()


int game (int record, short level, bool is_wall, char* maze)
{
    int i, points = 0;
    char dir[2], point[2], bonus[2], length, snake[1624][3], head[3];
    long wait_ms = 120/level;
    char button;
    bool pause = false, dummy, game_over, replay;
    FILE* rec;

    if (strcmp(maze, "recording")==0 && (rec=fopen(maze, "rb"))!=NULL) {
        replay = true;
    }
    else {
        rec = fopen("recording", "wb");
        if (rec==NULL) exit(1);
        replay = false;
    }
    for (i = 0; i<1624; i++) {
        snake[i][0] = 0; snake[i][1] = 0; snake[i][2] = 0;
    }
    transition();
    getch(); randomize();
    textbackground(BLUE); textcolor(WHITE);
    button = 'a'; dir[0] = -1; dir[1] = 0; length = 2;
    head[0] = 35; head[1] = 15; head[2] = 0;
    gotoxy(head[0], head[1]); cprintf("\xDB");
    snake[0][0] = 35; snake[0][1] = 15;
    gotoxy(snake[0][0], snake[0][1]); cprintf("\xB0");
    snake[1][0] = 36; snake[1][1] = 15;
    gotoxy(snake[1][0], snake[1][1]); cprintf("\xB0");
    game_over = false;
    if (replay) {
        fread(&point[0], sizeof(char), 1, rec);
        fread(&point[1], sizeof(char), 1, rec);
    }
    else {
        do {
            dummy = false;
            point[0] = rand()%65 + 1;
            point[1] = rand()%25 + 1;
            for (i=0; i<length; i++)
                if (point[0]==snake[i][0] && point[1]==snake[i][1]) {
                    dummy = true; break;
                }
        } while (dummy);
        fwrite(&point[0], sizeof(char), 1, rec);
        fwrite(&point[1], sizeof(char), 1, rec);
    }
    textcolor(LIGHTCYAN);
    gotoxy(point[0], point[1]); cprintf("\xFA");
    textcolor(LIGHTGRAY); textbackground(BLACK); gotoxy(67, 2);
    cprintf("%-4d Points", points); textbackground(BLUE);
    while (!game_over) {
        if (snake[length-1][0] && snake[length-1][1]) {
            gotoxy(snake[length-1][0], snake[length-1][1]);
            cprintf (" ");
        }
        for (i = length-1; i>0; i--) {
            snake[i][0] = snake[i-1][0];
            snake[i][1] = snake[i-1][1];
        }
        snake[i][0] = head[0];
        snake[i][1] = head[1];
        head[0] += dir[0];
        head[1] += dir[1];
        if      (head[0]<1)  head[0] = 65;
        else if (head[0]>65) head[0] = 1;
        if      (head[1]<1)  head[1] = 25;
        else if (head[1]>25) head[1] = 1;
        textcolor(WHITE);
        gotoxy(head[0], head[1]); cprintf("\xDB");
        gotoxy(head[0], head[1]); cprintf("\xB0");
        if (head[0]==point[0] && head[1]==point[1]) {
            points += level; length++;
            if (replay) {
                fread(&point[0], sizeof(char), 1, rec);
                fread(&point[1], sizeof(char), 1, rec);
            }
            else {
                do {
                    dummy = false;
                    point[0] = rand()%65 + 1;
                    point[1] = rand()%25 + 1;
                    for (i = 0; i<length; i++)
                        if (point[0]==snake[i][0] && point[1]==snake[i][1]) {
                            dummy = true; break;
                        }
                } while (dummy);
                fwrite(&point[0], sizeof(char), 1, rec);
                fwrite(&point[1], sizeof(char), 1, rec);
            }
            textcolor(LIGHTCYAN); gotoxy(point[0], point[1]); cprintf("\xFA");
            textcolor(LIGHTGRAY); textbackground(BLACK);
            gotoxy(67, 2); cprintf("%-4d", points);
            textbackground(BLUE);
        }
        for (i = 0; i<length; i++)
            if (head[0]==snake[i][0] && head[1]==snake[i][1])
                game_over = true;
        Sleep(30*wait_ms);
        if (replay) {
            if (feof(rec)) game_over = true;
            fread(&button, sizeof(char), 1, rec);
            if (button=='y') {
                dir[0]=-1; dir[1]=1;
            }
            else if (button=='s' || button=='x') {
                dir[0] = 0; dir[1] = 1;
            }
            else if (button=='c') {
                dir[0] = 1; dir[1] = 1;
            }
            else if (button=='a') {
                dir[0] = -1; dir[1] = 0;
            }
            else if (button=='d') {
                dir[0] = 1; dir[1] = 0;
            }
            else if (button=='q') {
                dir[0] = -1; dir[1] = -1;
            }
            else if (button=='w') {
                dir[0] = 0; dir[1] = -1;
            }
            else if (button=='e') {
                dir[0] = 1; dir[1] = -1;
            }
        }
        else {
            dummy = 0;
            fwrite(&dummy, sizeof(bool), 1, rec);
        }
        if (kbhit()) {
            do {
                button = getch();
                if (!replay) {
                    if (button=='y' && !(dir[0]==1 && dir[1]==-1)) {
                        dir[0]=-1; dir[1]=1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if ((button=='s' || button=='x') && !(dir[0]==0 && dir[1]==-1)) {
                        dir[0] = 0; dir[1] = 1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='c' && !(dir[0]==-1 && dir[1]==-1)) {
                        dir[0] = 1; dir[1] = 1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='a' && !(dir[0]==1 && dir[1]==0)) {
                        dir[0] = -1; dir[1] = 0; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='d' && !(dir[0]==-1 && dir[1]==0)) {
                        dir[0] = 1; dir[1] = 0; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='q' && !(dir[0]==1 && dir[1]==1)) {
                        dir[0] = -1; dir[1] = -1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='w' && !(dir[0]==0 && dir[1]==1)) {
                        dir[0] = 0; dir[1] = -1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    else if (button=='e' && !(dir[0]==-1 && dir[1]==1)) {
                        dir[0] = 1; dir[1] = -1; pause = false;
                        fwrite(&button, sizeof(char), 1, rec);
                    }
                    /*else {
                        dummy = 0;
                        fwrite(&dummy, sizeof(char), 1, rec);
                    }*/
                }
                if (button=='p')
                    pause = !pause;
                if (button==033) {
                    game_over = true; pause = false;
                }
            } while (pause);
            button = 0;
        }
        /*else {
            dummy = 0;
            fwrite(&dummy, sizeof(char), 1, rec);
        }*/
    }
    cprintf("\a"); getch();
    transition_reverse(); draw_background();
    fclose(rec);
    return points;
} // game()

///EOF/////////////////////////////////////////////////////////////////////////
