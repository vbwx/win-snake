// <vbstrlib.h>: String-Modification Library
// Copyright (C) 2003 Bernhard Waldbrunner
// Letzte Aktualisierung: Dienstag, 15. April 2003

// define-Anweisungen #########################################################
#define LEN 1025

// Funktions-Prototypen #######################################################
char *StrRTrim (char *);
char *StrCopy (char *, const char *);
char *StrLTrim (char *);
char *StrTrim (char *);
char *StrRFillCut (char *, int);
char *StrRRemoveNewline (char *);
char *StrRAddNewline (char *);
int LiesInt (char *);
int StrLen (const char *);
char *StrErsetze (char *, int, int);
int StrAnzZeichen (const char *, char);
char *StrToUpper (char *);
char *StrCat (char *, const char *);
char *StrCopyNChars (char *, char *, int);
void CPrint(const char *);

// Unterprogramme #############################################################
char *StrRTrim (char *s) {
  int i;
  i=0;
  while (*(s+i)!=0) i++;
  i--;
  while (*(s+i)=='\n' || *(s+i)=='\t' || *(s+i)==' ') {
    *(s+i)=0;
    i--;
  }
  return s;
} // StrRTrim: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrCopy (char *target, const char *source) {
  int i;
  i=0;
  while (*(source+i)!=0) {
    *(target+i) = *(source+i);
    i++;
  }
  *(target+i) = 0;
  return target;
} // StrCopy: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrLTrim (char *s) {
  int i, j;
  char copy[LEN];
  StrCopy (copy, s);
  i=0; j=0;
  while (*(copy+j)==' ' || *(copy+j)=='\n' || *(copy+j)=='\t') j++;
  while (*(copy+j)!=0) {
    *(s+i) = *(copy+j);
    i++; j++;
  }
  *(s+i) = 0;
  return s;
} // StrLTrim: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrTrim (char *s) {
  StrLTrim (s);
  StrRTrim (s);
  return s;
} // StrTrim: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrRFillCut (char *s, int quant) {
  int i;
  i=0;
  while (i<=quant) {
    if (*(s+i)==0)
      while (i<quant) {
        *(s+i)=' ';
        i++;
      }
    if (i==quant) *(s+i)=0;
    i++;
  }
  return s;
} // StrRFillCut: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrRRemoveNewline (char *s) {
  int i;
  i=0;
  while (*(s+i)!=0) i++;
  i--;
  while (*(s+i)=='\n') {
    *(s+i)=0;
    i--;
  }
  return s;
} // StrRRemoveNewline: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrRAddNewline (char *s) {
  int i;
  i=0;
  while (*(s+i)!=0) i++;
  if (*(s+i-1)!='\n') {
    *(s+i)='\n';
    *(s+i+1)=0;
  }
  return s;
} // StrRAddNewline: Ende

///////////////////////////////////////////////////////////////////////////////

int LiesInt (char *s) {
   int x;
   puts (s);
   scanf ("%d", &x);
   return x;
}  // LiesInt: Ende

///////////////////////////////////////////////////////////////////////////////

int StrLen (const char *s) {
   int i=0;
   while (s[i] != 0) i++;
   return i;
}  // StrLen: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrErsetze (char *s, int search_char, int change_char) {
   int i;
   i = 0;
   while (*(s+i) != 0) {
      if (*(s+i) == search_char) *(s+i) = change_char;
      i++;
   }
   return s;
}  // StrErsetze: Ende

///////////////////////////////////////////////////////////////////////////////

int StrAnzZeichen (const char *string, char search) {
   int i, n;
   i=0; n=0;
   while (*(string+i)!=0) {
      if (*(string+i)==search) n++;
      i++;
   }
   return n;
}  // StrAnzZeichen: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrToUpper (char *string) {
   int i;
   i=0;
   while (*(string+i)!=0) {
      if ('a' <= *(string+i) && *(string+i) <= 'z')
         *(string+i) -= 32;
      i++;
   }
   return string;
}  // StrToUpper: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrCat (char *string1, const char *string2) {
   int i, j;
   i=0; j=0;
   while (*(string1+i)!=0) i++;
   while (*(string2+j)!=0) {
      *(string1+i) = *(string2+j);
      i++; j++;
   }
   *(string1+i) = *(string2+j);
   return string1;
}  // StrCat: Ende

///////////////////////////////////////////////////////////////////////////////

char *StrCopyNChars (char *target, char *source, int n) {
   int i;
   i=0;
   while (*(source+i)!=0 && i<n) {
      *(target+i) = *(source+i);
      i++;
   }
   *(target+i)=0;
   return target;
}  // StrCopyNChars: Ende

///////////////////////////////////////////////////////////////////////////////

void CPrint(const char *s) {
  int i;
  i=0;
  while (s[i]!=0) {
    if (isspace(s[i]) && s[i]!=' ' && s[i]!='\t' && s[i]!='\a') {
      printf("%c", s[i]);
      i++;
    }
    else {
      cprintf("%c", s[i]);
      i++;
    }
  }
} // CPrint: Ende

// Ende des Listings von <vbstrlib.h> #########################################
