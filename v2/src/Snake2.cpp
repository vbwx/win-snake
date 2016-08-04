// Copyright (C) 2002-2007 Bernhard Waldbrunner
// Snake 2.99
// Letzte Aktualisierung: Mon, 2007/01/29
/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// includes ###################################################################
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dos.h>
#include "VBSTRLIB.H"

// defines ####################################################################
#define SubMenuQuant 5

// vordefinierte Makros #######################################################
#ifdef __BCPLUSPLUS__
#  if __BCPLUSPLUS__==0x0310
#    define bool char
#    define true 1
#    define false 0
#  endif
#endif

// Funktions-Prototypen #######################################################
void Background (void);
short Snake_Game (short, short, bool);
void Instructions (void);
void SetLevel (short *);
void ErrorLine(const char *);

// Hauptprogramm ##############################################################
void main (void) {
   short level, record, mark, points, i, lastmark;
   char button, Menu[SubMenuQuant][16];
   bool exit, walls;
   FILE *recordf;
   textbackground (7); clrscr(); gotoxy(1, 1);
   textmode (C80); _setcursortype (_NOCURSOR); randomize();
   level=3; record=0; mark=1; exit=false; points=0; lastmark=1; walls=false;
   StrCopy (Menu[0], "Neues Spiel    ");
   StrCopy (Menu[1], "Ebene:");
   StrCopy (Menu[3], "Anleitung      ");
   StrCopy (Menu[4], "Beenden        ");
   recordf = fopen("record.dat", "rb");
   if (recordf==NULL) {
     ErrorLine("Die Rekorddatei wurde noch nicht erstellt oder wurde geloescht.\nSie wird generiert.");
   }
   else {
     fread(&record, sizeof(short), 1, recordf);
     fread(&level, sizeof(short), 1, recordf);
     fread(&walls, sizeof(bool), 1, recordf);
     fclose(recordf);
     if (record>=20000 || record<0 || level>5 || level<1) {
       ErrorLine("Die Rekorddatei (record.dat) wurde manipuliert und enthaelt\nFalschinformationen. Die gespeicherten Werte werden wieder auf den\nAnfangswert zurueckgesetzt.");
       record=0; level=3;
     }
   }
   StrCopy(Menu[2], walls ? "W\x84nde          " : "Keine W\x84nde    ");
   do {
     Background ();
     textcolor (15);
     gotoxy (10, 18); cprintf ("Tastenbefehle");
     gotoxy (14, 19); cprintf ("'8': \x18");
     gotoxy (14, 20); cprintf ("'2': \x19");
     gotoxy (14, 21); cprintf ("'5': Auswahl");
     textcolor (0);
      if (points>record) {
        record=points;
        gotoxy(54, 2); cprintf("Neuer ");
      }
       gotoxy (60, 2); cprintf ("Rekord: %d", record);
      for (i=0; i<SubMenuQuant; i++) {
         gotoxy (10, i+1); cprintf ("%s", Menu[i]);
         if (i==1) cprintf (" %2d      ", level);
      }
      do {
         if (lastmark!=mark) {
            textcolor (0); textbackground (7);
            gotoxy (7, lastmark); cprintf ("   %s", Menu[lastmark-1]);
            if (lastmark==2) cprintf (" %2d      ", level);
         }
         textcolor (0); textbackground (7);
         gotoxy (7, mark); cprintf ("\xAF ");
         textcolor (7); textbackground (0);
         cprintf (" %s", Menu[mark-1]);
         if (mark==2) cprintf (" %2d      ", level);
         button=getch ();
         lastmark=mark;
         if ((button=='2' || button=='s') && mark<SubMenuQuant) mark++;
         else if ((button=='8' || button=='w') && mark>1) mark--;
      }  while (button!='5' && button!=' ');
     if (mark==1) { points=Snake_Game(level, record, walls); }
     else if (mark==2) SetLevel (&level);
     else if (mark==3)
        if (walls) {
           walls = false; StrCopy(Menu[2], "Keine W\x84nde    ");
        }
        else {
           walls = true; StrCopy(Menu[2],  "W\x84nde          ");
        }
     else if (mark==4) Instructions ();
     else if (mark==5) exit=true;
   }  while (exit!=true);
   recordf = fopen("record.dat", "wb");
   if (recordf!=NULL) {
     fwrite(&record, sizeof(short), 1, recordf);
     fwrite(&level, sizeof(short), 1, recordf);
     fwrite(&walls, sizeof(bool), 1, recordf);
     fclose(recordf);
   }
}  // main: Ende

// Unterprogramme #############################################################
void Background (void) {
   textmode (C80); textbackground (7); textcolor (8); clrscr();
   gotoxy (1, 8);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1   \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1    \xB1\xB1\xB1\xB1 \xB1\xB1\xB1\xB1");
   gotoxy (1, 9);
   cprintf ("         \xB1\xB1    \xB1\xB1  \xB1\xB1\xB1    \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1           \xB1\xB1 \xB1\xB1");
   gotoxy (1, 10);
   cprintf ("         \xB1\xB1        \xB1\xB1\xB1\xB1   \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1           \xB1\xB1 \xB1\xB1");
   gotoxy (1, 11);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1 \xB1\xB1  \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1\xB1\xB1     \xB1\xB1\xB1\xB1\xB1        \xB1\xB1 \xB1\xB1");
   gotoxy (1, 12);
   cprintf ("               \xB1\xB1  \xB1\xB1  \xB1\xB1 \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1           \xB1\xB1 \xB1\xB1");
   gotoxy (1, 13);
   cprintf ("         \xB1\xB1    \xB1\xB1  \xB1\xB1   \xB1\xB1\xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1           \xB1\xB1 \xB1\xB1");
  gotoxy (1, 14);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1    \xB1\xB1\xB1\xB1 \xB1\xB1\xB1\xB1");
   gotoxy (1, 25);
   cprintf ("Copyright \xB8 2002-2007 Bernhard Waldbrunner");
}  // Background: Ende

///////////////////////////////////////////////////////////////////////////////

short Snake_Game (short level, short record, bool walls) {
   int i;
   short points, dir[2], head_pos[2], point_pos[2], snake_length;
   short snake_pos[1000][2]/*, dt = 200/level*/;
   char button;
   bool game_over, choke = false;
   points=0;
   textmode (C80); randomize ();
   textbackground (7); textcolor (8); clrscr();
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
   head_pos[0]=47; head_pos[1]=15; game_over=false;
   textcolor (4);
   gotoxy (head_pos[0], head_pos[1]); cprintf ("\xDB");
   for (i=0; i<snake_length; i++) {
      snake_pos[i][0]=48+i; snake_pos[i][1]=15;
      gotoxy (snake_pos[i][0], snake_pos[i][1]);
      cprintf ("\xB0");
   }
   point_pos[0]=(rand() % 50) + 16;
   point_pos[1]=(rand() % 20) + 4;
   textcolor (14);
   gotoxy (point_pos[0], point_pos[1]); cprintf ("\xF");
   textcolor (0); gotoxy (17, 2); cprintf ("Rekord: %5d", record);
   gotoxy (52, 2); cprintf ("Punkte: %5d", points);
   while (!game_over) {
     gotoxy (snake_pos[snake_length-1][0], snake_pos[snake_length-1][1]);
      cprintf (" ");
      for (i=(snake_length-1); i>0; i--) {
	snake_pos[i][0]=snake_pos[i-1][0];
	snake_pos[i][1]=snake_pos[i-1][1];
      }
      snake_pos[i][0]=head_pos[0]; snake_pos[i][1]=head_pos[1];
      head_pos[0]+=dir[0]; head_pos[1]+=dir[1];
      if (walls) {
         if (head_pos[0]<16 || head_pos[0]>65 || head_pos[1]<4 || head_pos[1]>23)
            game_over=true;
      }
      else {
         if (head_pos[0]<16) head_pos[0]=65;
         else if (head_pos[0]>65) head_pos[0]=16;
         else if (head_pos[1]<4) head_pos[1]=23;
         else if (head_pos[1]>23) head_pos[1]=4;
      }
      textcolor (4);
      gotoxy (head_pos[0], head_pos[1]); cprintf ("\xDB");
      gotoxy (snake_pos[0][0], snake_pos[0][1]); cprintf ("\xB0");
      if (head_pos[0]==point_pos[0] && head_pos[1]==point_pos[1]) {
  points += level * (walls ? 2 : 1);
  snake_length++;
  point_pos[0]=(rand () % 50) + 16;
  point_pos[1]=(rand () % 20) + 4;
  textcolor (14); gotoxy (point_pos[0], point_pos[1]);
  cprintf ("\xF"); textcolor (0);
  gotoxy (60, 2); cprintf ("%5d", points);
  if (points>record) {
    gotoxy(34, 2); cprintf("NEUER REKORD !");
  }
      }
      for (i=0; i<snake_length; i++)
  if (head_pos[0]==snake_pos[i][0] && head_pos[1]==snake_pos[i][1])
     game_over=true;
      //delay(dt);
      int j=0; while (j<(8000000/(choke ? 1 : level*2))) j++;
      if (kbhit ()) {
  button=getch ();
  button = tolower(button);
  if ((button=='1' || button=='y') && !(dir[0]==1 && dir[1]==-1))
     { dir[0]=-1; dir[1]=1; }
   else if ((button=='2' || button=='5' || button=='s') && !(dir[0]==0 && dir[1]==-1))
     { dir[0]=0; dir[1]=1; }
   else if ((button=='3' || button=='x') && !(dir[0]==-1 && dir[1]==-1))
     { dir[0]=1; dir[1]=1; }
   else if ((button=='4' || button=='a') && !(dir[0]==1 && dir[1]==0))
     { dir[0]=-1; dir[1]=0; }
   else if ((button=='6' || button=='d') && !(dir[0]==-1 && dir[1]==0))
     { dir[0]=1; dir[1]=0; }
   else if ((button=='7' || button=='q') && !(dir[0]==1 && dir[1]==1))
     { dir[0]=-1; dir[1]=-1; }
   else if ((button=='8' || button=='w') && !(dir[0]==0 && dir[1]==1))
     { dir[0]=0; dir[1]=-1; }
   else if ((button=='9' || button=='e') && !(dir[0]==-1 && dir[1]==1))
     { dir[0]=1; dir[1]=-1; }
   else if (button=='\033') game_over=true;
   else if (button=='#') choke = !choke;
   else if (button=='*') {
      textcolor (14); gotoxy (point_pos[0], point_pos[1]);
      cprintf ("\xF"); textcolor (0);
   }
   else if (button!='1' && button!='2' && button!='3' && button!='4' &&
            button!='5' && button!='6' && button!='7' && button!='8' && button!='9' &&
            button!='w' && button!='a' && button!='s' && button!='d' &&
            button!='q' && button!='e' && button!='x' && button!='y') {
      gotoxy(34,2); textcolor(0); cprintf("  (Pausiert)  ");
      while (true) {
       button = getch();
       if (button=='\033') game_over = true;
       if (button=='1' || button=='2' || button=='3' || button=='\033'
           || button=='4' || button=='5' || button=='6' || button=='7' || button=='8'
           || button=='9' || button=='w' || button=='a' || button=='s' || button=='d'
           || button=='q' || button=='e' || button=='x' || button=='y') break;
       if (button=='*') {
         textcolor (14); gotoxy (point_pos[0], point_pos[1]);
         cprintf ("\xF"); textcolor (0);
       }
      }
      gotoxy(36,2); cprintf("          ");
     }
    }
   }
   cprintf ("\a");
   textcolor (0); gotoxy (34, 2); cprintf ("  GAME OVER!  ");
   getch ();
   return points;
}  // Snake_Game: Ende

///////////////////////////////////////////////////////////////////////////////

void SetLevel (short *level) {
   short ActiveLevel, i;
   char button;
   ActiveLevel = *level; Background ();
   textmode (C80); textbackground (7); textcolor (15);
   gotoxy (10, 18); cprintf ("Tastenbefehle");
   gotoxy (14, 19); cprintf ("'+': H\x94here Ebene");
   gotoxy (14, 20); cprintf ("'-': Tiefere Ebene");
   gotoxy (14, 21); cprintf ("'5': Ebene speichern");
   gotoxy (14, 22); cprintf ("',': Abbrechen");
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
      if ((button=='+' || button=='d') && ActiveLevel<5) ActiveLevel++;
      else if ((button=='-' || button=='a') && ActiveLevel>1) ActiveLevel--;
   }  while (button!='5' && button!=',' && button!=' ' && button!='\033');
   if (button=='5' || button==' ') *level = ActiveLevel;
}  // SetLevel: Ende

///////////////////////////////////////////////////////////////////////////////

void Instructions (void) {
   FILE *hf; char s[LEN+1]; int i=0;
   textmode(C80); textbackground(7); textcolor(0); clrscr();
   hf = fopen("Instructions.hlp", "rb");
   if (hf==NULL) {
     ErrorLine("Die Hilfedatei <Instructions.hlp> konnte nicht geladen werden.\n"
     "Bitte installieren Sie Snake 2 erneut! <Snake2_setup.exe>");
     return;
   }
   while (fgets(s, LEN, hf)!=NULL) {
     CPrint(s); i++;
     if (i%23==0) {
       textcolor(15); gotoxy(58, 25); CPrint("Weiter mit [RETURN]...");
       getch(); textcolor(0); clrscr();
     }
   }
   fclose(hf);
   getch();
}  // Instructions: Ende

///////////////////////////////////////////////////////////////////////////////

void ErrorLine(const char *msg) {
  textmode(C80); textbackground(7); textcolor(12); _setcursortype(_NORMALCURSOR);
  CPrint("/!\\ Snake 2: Hinweis\n");
  textcolor(0); CPrint(msg);
  getch(); cprintf(" OK"); CPrint("\n\n");
  _setcursortype(_NOCURSOR);
} // ErrorLine: Ende

// Ende des Listings ##########################################################
