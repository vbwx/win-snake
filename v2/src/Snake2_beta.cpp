// Copyright (C) 2003 Bernhard Waldbrunner
// Snake 2.4 beta
// Letzte Aktualisierung: Sonntag, 15. Juni 2003

// includes ###################################################################
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "VBSTRLIB.H"

// defines ####################################################################
#define SubMenuQuant 4

// Funktions-Prototypen #######################################################
void Background (void);
short Snake_Game (short, short, short);
void Instructions (void);
void SetLevel (short *);
void ErrorLine(const char *);

// Hauptprogramm ##############################################################
void main (void) {
   short level, record, mark, points, i, lastmark, game;
   char button, Menu[SubMenuQuant][16];
   bool exit;
   FILE *recordf;
   textbackground (7); clrscr(); gotoxy(1, 1);
   textmode (C80); _setcursortype (_NOCURSOR); randomize();
   level=3; record=0; mark=1; exit=false; points=0; lastmark=1; game=0;
   StrCopy (Menu[0], "Neues Spiel    ");
   StrCopy (Menu[1], "Ebene:");
   StrCopy (Menu[2], "Anleitung      ");
   StrCopy (Menu[3], "Beenden        ");
   recordf = fopen("record.dat", "rb");
   if (recordf==NULL) {
     ErrorLine("Die Rekorddatei wurde noch nicht erstellt oder wurde geloescht.\nSie wird neu erstellt.");
   }
   else {
     fread(&record, sizeof(short), 1, recordf);
     fread(&level, sizeof(short), 1, recordf);
     fread(&game, sizeof(short), 1, recordf);
     fclose(recordf);
     if (record>=10000 || record<0 || level>5 || level<1 || game<0) {
       ErrorLine("Die Rekorddatei (record.dat) wurde manipuliert und enthaelt\nFalschinformationen. Die gespeicherten Werte werden wieder auf den\nAnfangswert zurueckgesetzt.");
       record=0; level=3; game=0;
     }
   }
   do {
     Background ();
     textcolor (15);
     gotoxy (10, 18); cprintf ("Tastenbefehle");
     gotoxy (15, 19); cprintf ("'8': \x18");
     gotoxy (15, 20); cprintf ("'2': \x19");
     gotoxy (15, 21); cprintf ("'5': Auswahl");
     textcolor (0);
      if (points>record) {
        record=points;
        gotoxy(54, 2); cprintf("Neuer ");
      }
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
     if (mark==1) { game++; points=Snake_Game(level, game, record); }
     else if (mark==2) SetLevel (&level);
     else if (mark==3) Instructions ();
     else if (mark==4) exit=true;
   }  while (exit!=true);
   recordf = fopen("record.dat", "wb");
   if (recordf!=NULL) {
     i = rand();
     fwrite(&record, sizeof(short), 1, recordf);
     fwrite(&level, sizeof(short), 1, recordf);
     fwrite(&game, sizeof(short), 1, recordf);
     fwrite(&i, sizeof(short), 1, recordf);
     fclose(recordf);
   }
}  // main: Ende

// Unterprogramme #############################################################
void Background (void) {
   textmode (C80); textbackground (7); textcolor (8); clrscr();
   gotoxy(37, 5); cprintf("Snake 2 Beta (Unveroeffentlichtes Werk)");
   gotoxy (1, 7);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1   \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1    \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1");
   gotoxy (1, 8);
   cprintf ("         \xB1\xB1    \xB1\xB1  \xB1\xB1\xB1    \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1           \xB1\xB1  \xB1\xB1");
   gotoxy (1, 9);
   cprintf ("         \xB1\xB1        \xB1\xB1\xB1\xB1   \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1           \xB1\xB1  \xB1\xB1");
   gotoxy (1, 10);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1 \xB1\xB1  \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1\xB1\xB1     \xB1\xB1\xB1\xB1\xB1        \xB1\xB1  \xB1\xB1");
   gotoxy (1, 11);
   cprintf ("               \xB1\xB1  \xB1\xB1  \xB1\xB1 \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1  \xB1\xB1 \xB1\xB1    \xB1\xB1           \xB1\xB1  \xB1\xB1");
   gotoxy (1, 12);
   cprintf ("         \xB1\xB1    \xB1\xB1  \xB1\xB1   \xB1\xB1\xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1  \xB1\xB1   \xB1\xB1           \xB1\xB1  \xB1\xB1");
  gotoxy (1, 13);
   cprintf ("          \xB1\xB1\xB1\xB1\xB1\xB1   \xB1\xB1     \xB1\xB1  \xB1\xB1    \xB1\xB1  \xB1\xB1   \xB1\xB1  \xB1\xB1\xB1\xB1\xB1\xB1\xB1    \xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1");
   gotoxy (1, 16);
   cprintf ("                   mit den besten Empfehlungen von NOKIA \xA9");
   gotoxy (1, 25);
   cprintf ("Copyright \xB8 2003 Bernhard Waldbrunner");
}  // Background: Ende

///////////////////////////////////////////////////////////////////////////////

short Snake_Game (short level, short game, short record) {
   int i, j;
   short points, dir[2], head_pos[2], point_pos[2], snake_length;
   short snake_pos[1000][2];
   char button;
   bool game_over;
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
   textcolor (0); gotoxy (16, 2); cprintf ("Spiel: %d", game);
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
      if (head_pos[0]<16) head_pos[0]=65;
      else if (head_pos[0]>65) head_pos[0]=16;
      else if (head_pos[1]<4) head_pos[1]=23;
      else if (head_pos[1]>23) head_pos[1]=4;
      textcolor (4);
      gotoxy (head_pos[0], head_pos[1]); cprintf ("\xDB");
      gotoxy (snake_pos[0][0], snake_pos[0][1]); cprintf ("\xB0");
      if (head_pos[0]==point_pos[0] && head_pos[1]==point_pos[1]) {
        points+=level*2; snake_length++;
        point_pos[0]=(rand () % 50) + 16;
        point_pos[1]=(rand () % 20) + 4;
        textcolor (14); gotoxy (point_pos[0], point_pos[1]);
        cprintf ("\xF"); textcolor (0);
        gotoxy (61, 2); cprintf ("%4d", points);
        if (points>record) {
          gotoxy(33, 2); cprintf("NEUER REKORD !");
        }
      }
      for (i=0; i<snake_length; i++)
        if (head_pos[0]==snake_pos[i][0] && head_pos[1]==snake_pos[i][1])
           game_over=true;
      j=0; while (j<(4000000/level)) j++;
      if (kbhit ()) {
        button=getch ();
        if (button=='1' && !(dir[0]==1 && dir[1]==-1))
           { dir[0]=-1; dir[1]=1; }
         else if ((button=='2' || button=='5') && !(dir[0]==0 && dir[1]==-1))
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
         else if (button=='\033') break;
         else if (button!='1' && button!='2' && button!='3' && button!='4' &&
            button!='5' && button!='6' && button!='7' && button!='8' && button!='9')
            while (!kbhit () && (button!='1' && button!='2' && button!='3'
            && button!='4' && button!='5' && button!='6' && button!='7' && button!='8'
            && button!='9')) button=getch ();
      }
   }
   cprintf ("\a");
   textcolor (0); gotoxy (33, 2); cprintf ("  GAME OVER!  ");
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
   textmode(C80); textbackground(7); textcolor(0); clrscr();
   gotoxy(1, 1);
   cprintf("Snake 2 beta - Anleitung");
   gotoxy(1, 4);
   cprintf("Steuerung der Schlange"); gotoxy(5, 5);
   cprintf("(Numerischer Tastenblock)"); gotoxy(5, 6);
   cprintf("\\   \x18   /"); gotoxy(5, 7);
   cprintf("  7 8 9              [ESC]: Abbruch des Spiels"); gotoxy(5, 8);
   cprintf("\x1B 4 5 6 \x1A"); gotoxy(5, 9);
   cprintf("  1 2 3              (beliebige Taste): Pause"); gotoxy(5, 10);
   cprintf("/   \x19   \\"); gotoxy(1, 12);
   cprintf("Das Spiel"); gotoxy(5, 13);
   cprintf("Hoehere Ebene -> mehr Punkte pro Sonne, aber schnellere Schlange.");
   gotoxy(5, 14);
   cprintf("Ziel: Die Schlange lenken, Sonnen verschlingen, aber nicht sich selbst!");
   gotoxy(1, 16); cprintf("HINWEIS"); gotoxy(5, 17);
   cprintf("Die Anleitung ist noch unvollstaendig, da dies ein unveroeffentlichtes");
   gotoxy(5, 18); cprintf("Werk ist. Ab Snake 3 wird eine ausfuehrliche "
     "Hilfe existieren."); gotoxy(1, 20);
   cprintf("Feedback"); gotoxy(5, 21);
   cprintf("Wenn Sie als Beta-Tester Bugs oder logische Fehler im Spiel ent"
     "decken,"); gotoxy(5, 22);
   cprintf("koennen Sie ein Feedback an mich senden.");
   gotoxy(5, 23);
   cprintf("E-Mail: "); textcolor(1); cprintf("waldbrunner_bernhard@hotmail.com");
   textcolor(0); gotoxy(1, 25); cprintf("Nun viel Spass bei Snake 2 beta!");
   getch();
}  // Instructions: Ende

///////////////////////////////////////////////////////////////////////////////

void ErrorLine(const char *msg) {
  textmode(C80); textbackground(7); textcolor(12); _setcursortype(_NORMALCURSOR);
  CPrint("/!\\ Snake 2 beta: Hinweis\n");
  textcolor(0); CPrint(msg);
  getch(); cprintf(" OK"); CPrint("\n\n");
  _setcursortype(_NOCURSOR);
} // ErrorLine: Ende

// Ende des Listings ##########################################################
