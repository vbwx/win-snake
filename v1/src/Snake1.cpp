// Copyright (c) 2003 vbwx
// Snake 1.7
// Letzte Aktualisierung: Mon, 2007/01/22

// includes ###################################################################
#include <conio.h>
#include <stdlib.h>
#include "VBSTRLIB.H"

// defines ####################################################################
#define SubMenuQuant 4

// Funktions-Prototypen #######################################################
void ClrScrn (int, int);
void Background (void);
int Snake_Game (int, int);
void Instructions (void);
void SetLevel (int *);
char *StrCopy (char *, const char *);

// Hauptprogramm ##############################################################
void main (void) {
   int level, record, mark, points, exit, i, lastmark, game;
   char button, Menu[SubMenuQuant][16];
   textmode (C80);
   level=3; record=0; mark=1; exit=0; points=0; lastmark=1; game=0;
   StrCopy (Menu[0], "Neues Spiel    ");
   StrCopy (Menu[1], "Ebene:");
   StrCopy (Menu[2], "Anleitung      ");
   StrCopy (Menu[3], "Beenden        ");
   do {
   	Background ();
   	textcolor (15); textbackground (7);
   	gotoxy (10, 18); cprintf ("Tastenbefehle");
   	gotoxy (15, 19); cprintf ("'8': \x18");
   	gotoxy (15, 20); cprintf ("'2': \x19");
   	gotoxy (15, 21); cprintf ("'5': Auswahl");
   	textcolor (0);
  	 	gotoxy (60, 2); cprintf ("Rekord: %d", record);
      for (i=0; i<SubMenuQuant; i++) {
         gotoxy (10, i+1); cprintf ("%s", Menu[i]);
         if (i==1) cprintf (" %d       ", level);
      }
      do {
         if (lastmark!=mark) {
            textcolor (0); textbackground (7);
            gotoxy (7, lastmark); cprintf ("   %s", Menu[lastmark-1]);
            if (lastmark==2) cprintf (" %d       ", level);
         }
         textcolor (0); textbackground (7);
         gotoxy (7, mark); cprintf ("\xAF ");
         textcolor (7); textbackground (0);
         cprintf (" %s", Menu[mark-1]);
         if (mark==2) cprintf (" %d       ", level);
         button=getch ();
         lastmark=mark;
         if (button=='2' && mark<SubMenuQuant) mark++;
         else if (button=='8' && mark>1) mark--;
      }  while (button!='5');
   	if (mark==1) { game++; points=Snake_Game (level, game); }
   	else if (mark==2) SetLevel (&level);
   	else if (mark==3) Instructions ();
   	else exit=1;
      if (points>record) record=points;
   }  while (exit!=1);
}  // main: Ende

// Unterprogramme #############################################################
void ClrScrn (int cols, int rows) {
   int i, j;
   textmode (C80);
   textbackground (7);
   for (i=0; i<rows; i++) {
      gotoxy (1, 1+i);
      for (j=0; j<cols; j++)
         cprintf (" ");
   }
   gotoxy (1, 1);
}  // ClrScrn: Ende

///////////////////////////////////////////////////////////////////////////////

void Background (void) {
   int i, j;
   textmode (C80);
   textbackground (7);
   for (i=0; i<25; i++)
   	for (j=0; j<80; j++) {
   		gotoxy (1+j, 1+i);
         cprintf (" ");
      }
   textcolor (8);
gotoxy (1, 25); cprintf ("Copyright \xB8 2003 vbwx");
   gotoxy (10, 7);
   cprintf (" \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1   \xB1"
   "\xB1\xB1\xB1\xB1\xB1   \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1"
   "\xB1\xB1\xB1            \xB1\xB1");
   gotoxy (10, 8);
   cprintf ("\xB1\xB1    \xB1\xB1  \xB1\xB1\xB1    \xB1\xB1  \xB1\xB1    "
   "\xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1                \xB1"
   "\xB1\xB1");
   gotoxy (10, 9);
   cprintf ("\xB1\xB1        \xB1\xB1\xB1\xB1   \xB1\xB1  \xB1\xB1    \xB1"
   "\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1              \xB1\xB1\xB1"
   "\xB1\xB1");
   gotoxy (10, 10);
   cprintf (" \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1 \xB1\xB1  \xB1\xB1  \xB1"
   "\xB1    \xB1\xB1  \xB1\xB1\xB1\xB1     \xB1\xB1\xB1\xB1\xB1"
   "              \xB1\xB1");
   gotoxy (10, 11);
   cprintf ("      \xB1\xB1  \xB1\xB1  \xB1\xB1 \xB1\xB1  \xB1\xB1\xB1\xB1"
   "\xB1\xB1\xB1\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1              "
   "   \xB1\xB1");
   gotoxy (10, 12);
   cprintf ("\xB1\xB1    \xB1\xB1  \xB1\xB1   \xB1\xB1\xB1\xB1  \xB1\xB1  "
   "  \xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1                 \xB1"
   "\xB1");
	gotoxy (10, 13);
   cprintf (" \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1  \xB1\xB1  "
   "  \xB1\xB1  \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1"
   "            \xB1\xB1");
   gotoxy (10, 16);
   cprintf ("          mit den besten Empfehlungen von NOKIA \xA9");
}  // Background: Ende

///////////////////////////////////////////////////////////////////////////////

int Snake_Game (int level, int game) {
   int i, j;
   short points, dir[2], head_pos[2], point_pos[2], snake_length, dummy;
   short snake_pos[1000][2], game_over;
   char button;
   points=0;
   textmode (C80); randomize ();
   Background (); textbackground (7); textcolor (8);
   for (i=0; i<24; i++)
   	for (j=0; j<50; j++) {
      	gotoxy (16+j, 1+i);
         cprintf (" ");
      }
   gotoxy (15, 1); cprintf ("\xC9");
   for (i=0; i<50; i++) {
      gotoxy (16+i, 1); cprintf ("\xCD");
   }
   gotoxy (66, 1); cprintf ("\xBB");
   for (i=0; i<22; i++) {
      gotoxy (66, 2+i); cprintf ("\xBA");
   }
   gotoxy (66, 24); cprintf ("\xBC");
   for (i=0; i<50; i++) {
      gotoxy (16+i, 24); cprintf ("\xCD");
   }
   gotoxy (15, 24); cprintf ("\xC8");
   for (i=0; i<22; i++) {
      gotoxy (15, 2+i); cprintf ("\xBA");
   }
   gotoxy (15, 3); cprintf ("\xCC");
   for (i=0; i<50; i++) {
   	gotoxy (16+i, 3); cprintf ("\xCD");
   }
   gotoxy (66, 3); cprintf ("\xB9");
   getch ();

   textbackground (7);
   button='4'; dir[0]=-1; dir[1]=0; snake_length=2;
   head_pos[0]=47; head_pos[1]=15;
   dummy=1; game_over=0;
   textcolor (4);
   gotoxy (head_pos[0], head_pos[1]); cprintf ("\xDB");
   for (i=0; i<snake_length; i++) {
      snake_pos[i][0]=48+i; snake_pos[i][1]=15;
      gotoxy (snake_pos[i][0], snake_pos[i][1]);
      cprintf ("\xB0");
   }
   do {
      point_pos[0]=(rand () % 50) + 16;
      point_pos[1]=(rand () % 20) + 4;
      for (i=0; i<snake_length; i++)
         if (point_pos[0]==snake_pos[i][0] && point_pos[1]==snake_pos[i][1]) {
         dummy=0; break;
      }
   }  while (!dummy);
   textcolor (14);
   gotoxy (point_pos[0], point_pos[1]); cprintf ("\xF");
   textcolor (0); gotoxy (16, 2); cprintf ("Spiel: %3d", game);
   gotoxy (53, 2); cprintf ("Punkte: %4d", points);
   while (!game_over) {
   	gotoxy (snake_pos[snake_length-1][0], snake_pos[snake_length-1][1]);
      cprintf (" ");
      for (i=(snake_length-1); i>0; i--) {
      	snake_pos[i][0]=snake_pos[i-1][0];
         snake_pos[i][1]=snake_pos[i-1][1];
      }
      snake_pos[i][0]=head_pos[0]; snake_pos[i][1]=head_pos[1];
      head_pos[0]+=dir[0]; head_pos[1]+=dir[1];
      textcolor (4);
      gotoxy (head_pos[0], head_pos[1]); cprintf ("\xDB");
      gotoxy (snake_pos[0][0], snake_pos[0][1]); cprintf ("\xB0");
      if (head_pos[0]==point_pos[0] && head_pos[1]==point_pos[1]) {
      	points+=level*2; snake_length++;
         dummy=1;
         do {
         	point_pos[0]=(rand () % 50) + 16;
            point_pos[1]=(rand () % 20) + 4;
            for (i=0; i<snake_length; i++)
            	if (point_pos[0]==snake_pos[i][0] && point_pos[1]==snake_pos[i][1]) {
               	dummy=0; break;
               }
         }  while (!dummy);
         textcolor (14); gotoxy (point_pos[0], point_pos[1]);
         cprintf ("\xF"); textcolor (0);
         gotoxy (61, 2); cprintf ("%4d", points);
      }
      if (head_pos[0]<16 || head_pos[0]>65 || head_pos[1]<4 || head_pos[1]>23)
      	game_over=1;
      for (i=0; i<snake_length; i++)
      	if (head_pos[0]==snake_pos[i][0] && head_pos[1]==snake_pos[i][1])
         	game_over=1;
      j=0; while (j<(4000000/level)) j++;
      if (kbhit ()) {
      	button=getch ();
      	if (button=='1' && !(dir[0]==1 && dir[1]==-1))
         	{ dir[0]=-1; dir[1]=1; }
         else if ((button=='2'||button=='5') && !(dir[0]==0 && dir[1]==-1))
         	{ dir[0]=0; dir[1]=1; }
         else if (button=='3' && !(dir[0]==-1 && dir[1]==-1))
         	{ dir[0]=1; dir[1]=1; }
         else if (button=='4' && !(dir[0]==1 && dir[1]==0))
         	{ dir[0]=-1; dir[1]=0; }
         else if (button=='6' && !(dir[0]==-1 && dir[1]==0))
         	{ dir[0]=1; dir[1]=0; }
         else if (button=='7' && !(dir[0]==1 && dir[1]==1))
         	{ dir[0]=-1; dir[1]=-1; }
         else if (button=='8' && !(dir[0]==0 && dir[1]==1))
         	{ dir[0]=0; dir[1]=-1; }
         else if (button=='9' && !(dir[0]==-1 && dir[1]==1))
         	{ dir[0]=1; dir[1]=-1; }
      }
   }
   cprintf ("\a");
   textcolor (0); gotoxy (35, 2); cprintf ("GAME OVER!");
   getch ();
   return points;
}  // Snake_Game: Ende

///////////////////////////////////////////////////////////////////////////////

void SetLevel (int *level) {
   int ActiveLevel, i;
   char button;
   ActiveLevel = *level;
   textmode (C80);
   Background ();
   textbackground (7); textcolor (15);
   gotoxy (10, 18); cprintf ("Tastenbefehle");
   gotoxy (15, 19); cprintf ("'+': H\x94here Ebene");
   gotoxy (15, 20); cprintf ("'-': Tiefere Ebene");
   gotoxy (15, 21); cprintf ("'5': Ebene speichern");
   gotoxy (15, 22); cprintf ("',': Abbrechen");
   gotoxy (10, 2);
   textcolor (0);
   cprintf ("Ebene: ");
   do {
   	textcolor (4);
      gotoxy (17, 2);
      for (i=0; i<ActiveLevel; i++) cprintf ("\xDB");
      textcolor (8); gotoxy (17+ActiveLevel, 2);
      for (i=0; i<5-ActiveLevel; i++) cprintf ("\xB0");
      textcolor (0); gotoxy (25, 2);
      cprintf ("%d", ActiveLevel);
      button=getch ();
      if (button=='+' && ActiveLevel<5) ActiveLevel++;
      else if (button=='-' && ActiveLevel>1) ActiveLevel--;
   }  while (button!='5' && button!=',');
   if (button=='5') *level = ActiveLevel;
}  // SetLevel: Ende

///////////////////////////////////////////////////////////////////////////////

void Instructions (void) {
   int i, j;
   textmode (C80); Background (); textbackground (7);
   textcolor (8);
   for (i=0; i<24; i++)
   	for (j=0; j<50; j++) {
      	gotoxy (16+j, 1+i);
         cprintf (" ");
      }
   gotoxy (15, 1); cprintf ("\xDA");
   for (i=0; i<50; i++) {
      gotoxy (16+i, 1); cprintf ("\xC4");
   }
   gotoxy (66, 1); cprintf ("\xBF");
   for (i=0; i<18; i++) {
      gotoxy (66, 2+i); cprintf ("\xB3");
   }
   gotoxy (66, 20); cprintf ("\xD9");
   for (i=0; i<50; i++) {
      gotoxy (16+i, 20); cprintf ("\xC4");
   }
   gotoxy (15, 20); cprintf ("\xC0");
   for (i=0; i<18; i++) {
      gotoxy (15, 2+i); cprintf ("\xB3");
   }
   gotoxy (15, 3); cprintf ("\xC3");
   for (i=0; i<50; i++) {
   	gotoxy (16+i, 3); cprintf ("\xC4");
   }
   gotoxy (66, 3); cprintf ("\xB4");
   textcolor (0);
   gotoxy (16, 2); cprintf ("                Snake 1: Anleitung");
   gotoxy (16, 4); cprintf ("     Willkommen bei Snake 1! Snake ist ja ein");
   gotoxy (16, 5);
   cprintf ("Spiel, das bereits jedem bekannt sein sollte. Das");
   gotoxy (16, 6);
   cprintf ("  finnische Unternehmen NOKIA\xA9 hat bereits vor");
   gotoxy (16, 7);
   cprintf ("  einigen Jahren das Konzept dieses simplen aber");
   gotoxy (16, 8);
   cprintf (" doch unterhaltsamen Spieles in die Realit\x84t um-");
   gotoxy (16, 9);
   cprintf ("  gesetzt und dieses in das Nokia-Mobiltelephon");
   gotoxy (16, 10);
   cprintf ("    3210 eingebaut. Es hat auch den Usern des");
   gotoxy (16, 11);
   cprintf (" Nokia 3210, wie man sieht, viel Freude bereitet,");
   gotoxy (16, 12);
   cprintf ("               Snake zu spielen...");
   gotoxy (16, 14);
   cprintf ("  Falls jemand mit dem Spiel \"Snake\" noch nicht");
   gotoxy (16, 15);
   cprintf (" vertraut ist, sich aber trotzdem den Spa\xE1 nicht");
   gotoxy (16, 16);
   cprintf (" entgehen lassen will, sollte im Benutzerhandbuch");
   gotoxy (16, 17);
   cprintf ("    zu Snake 1 nachschlagen, das der Anwendung");
   gotoxy (16, 18);
   cprintf ("  (.EXE) als Adobe Acrobat-Dokument (.PDF) bei-");
   gotoxy (16, 19);
   cprintf ("                      liegt.");
   getch ();
}  // Instructions: Ende

// Ende des Listings ##########################################################
