//Robert-Andrei Raucescu 335CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


typedef int (*TFElem)(void*);     // functie prelucrare element 
typedef int (*TFCmp)(void*, void*); // functie de comparare doua elemente 
typedef void (*TF)(void*);     // functie afisare/eliberare un element
typedef int (*TFHash)(void*);   // functie Hash


typedef struct CelulaG{ // Generic Cell Structure
    void* info;
    struct CelulaG *next;
}TCelulaG,*TLG;

typedef struct THash //Hash Table Structure
{
    size_t M;
    TFHash fh;
    TLG *v;
} TH;

typedef struct Word{//Word Structure
    char* word;
    int count;
}TWord;

typedef struct Len{//Length and list of words Structure
    int len;
    void* words;
}TLen;

int Ins_ELG(TLG*,void*);
TH* InitTH(size_t M, TFHash fh);
int codHash(void* elem);
TWord* AlocTWord(char* word);
void InsTH(TH* a, void* ae, TFCmp fcmp);
int cmpWords(void* e1, void* e2);
int InsIncWordEntry(TLG* aL,void* ae);
TLen* AlocLenEntry(void* ae);
void Afisare(TLG* aL, TF afiEL);
void AfiTH(TH* ah,TF afi_elem,int first, int max_len);
void afisareEl(void* elem);
TLG AlocVEntry(void* ae);
void SortList(TLG List);
void my_swap (TLG a, TLG b);
void AfisareMaxCount(TLG* aL, TF afiEL,int max_count);
