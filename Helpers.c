//Robert-Andrei Raucescu 335CB
#include "Helpers.h"

//Insert elem at beginning of list
int Ins_ELG(TLG* aL, void* elem){
    
    TLG aux = malloc(sizeof(TCelulaG));
    if(!aux)
        return 0;
    
    aux->info = elem;
    aux->next = *aL;

    *aL = aux;
    return 1;
}

//Initialize Hash Table
TH* InitTH(size_t M, TFHash fh){
    
    TH* h = (TH*) calloc(sizeof(TH),1);
    if(!h){
        printf("Eroare la alocarea tabelei HASH!");
        return NULL;
    }

    h->v = (TLG*) calloc(M,sizeof(TLG));
    if(!h->v){
        printf("Eroare la alocarea vectorului de pointeri in HASH");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

//Print an element
void afisareEl(void* elem){
    TWord * aux = (TWord*) elem;
    printf("%s/%d",aux->word,aux->count);
}

//Function for printing each element of list
void Afisare(TLG* aL, TF afiEL)
{
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	for(; *aL; aL = &(*aL)->next) {
		afiEL((*aL)->info);
        if((*aL)->next != NULL)
            printf(", ");
    }
    printf(")");
}

//Function for printing elements that appear no more than max_count times
void AfisareMaxCount(TLG* aL, TF afiEL,int max_count)
{

    int none = 0;
	if(!*aL) {
        printf("Lista vida\n");
        return;
    }

	for(; *aL; aL = &(*aL)->next) {

		if(((TWord*)((*aL)->info))->count <= max_count){
            if(none == 0){
                none = 1;
            }

            if( none == 1){
                printf("(%lu: ",strlen(((TWord*)((*aL)->info))->word));
                none = -1;
            }

            afiEL((*aL)->info);
            
            if((*aL)->next != NULL)
                printf(", ");
        }
    }
    if(none != 0)
        printf(")");
}

//Swap function used in sorting the lists
void my_swap(TLG a, TLG b){
    int tempC;
    char* tempW;

    tempC = ((TWord*)(a->info))->count;
    tempW = ((TWord*)(a->info))->word;
    
    ((TWord*)(a->info))->count = ((TWord*)(b->info))->count;
    ((TWord*)(a->info))->word = ((TWord*)(b->info))->word;

    ((TWord*)(b->info))->count = tempC;
    ((TWord*)(b->info))->word = tempW;
}

//Sorting function
void SortList(TLG List){
    int swapped;
    TLG aux;
    TLG prev = NULL;

    if(List == NULL)
        return;

    do{
        swapped = 0;
        aux = List;

        while(aux->next != prev){
            if(((TWord*)(aux->info))->count < ((TWord*)(aux->next->info))->count){
                my_swap(aux,aux->next);
                swapped = 1;
            }
            else{
                if(((TWord*)(aux->info))->count == 
                    ((TWord*)(aux->next->info))->count){
                    if(strcmp(((TWord*)(aux->info))->word,
                        ((TWord*)(aux->next->info))->word) > 0){
                        my_swap(aux,aux->next);
                        swapped = 1;
                    }
                }
            }
            aux = aux->next;
        }
        prev = aux;
    }
    while (swapped);
    
}

//Function for hashin an elem
int codHash(void* elem){
    TWord* cuvant = (TWord *) elem;
    char* aux = cuvant->word;
    if(aux[0] >= 'A' && aux[0] <= 'Z')
        return *aux - 'A';
    else
        return *aux - 'a';
}

//Allocatinging memory for a TWord structure
TWord* AlocTWord(char* word){
    TWord* aux = (TWord*) malloc(sizeof(TWord));
    aux->word = malloc(strlen(word)*sizeof(char));
    strcpy(aux->word,word);
    aux->count = 1;

    return aux;
}

//Check if there is at least one elem that fits the max_count condition
int checkForElemCount(TLG ae,int max_count){
    for(TLG aux = ae; aux != NULL; aux = aux->next){
        for(TLG aux2 = ((TLen*)(aux->info))->words; 
            aux2 != NULL; aux2=aux2->next){
            if(((TWord*)(aux2->info))->count <= max_count)
                return 1;
        }
    }

    return 0;
}

//Printing function for the Hash Table and conditions for it
void AfiTH(TH* ah,TF afi_elem,int first, int max_len)
{
    
    if(first != -1){//Has a beginning letter condition
        
        TLG maux = ah->v[first];
        if(maux){
            for(maux = ah->v[first]; maux != NULL; maux = maux->next){
                if(((TLen*)(maux->info))->len == max_len){
                    printf("(%d:",((TLen*)(maux->info))->len);
                    TLG oau = ((TLen*)(maux->info))->words;
                    SortList(oau);
                    Afisare(&oau,afisareEl);
                    printf("\n");
                }
                
            }
            
        }
    }
    else{
        if(max_len != -1){//Has a max lenght condition or a max count condition
            for(int i = 0; i< ah->M;i++){
            TLG maux = ah->v[i];
                if(maux){
                    int afis =0;
                    if(checkForElemCount(maux,max_len) == 1){
                        printf("pos%d: ",i);
                        afis =1;
                    }
                    for(maux = ah->v[i]; maux != NULL; maux = maux->next){
                        TLG oau = ((TLen*)(maux->info))->words;
                        SortList(oau);
                        AfisareMaxCount(&oau,afisareEl,max_len);
                        
                    }
                    if(afis == 1)
                        printf("\n");
                }
            }
        }
        else{//Has no condition and prints the whole Table
        for(int i = 0; i< ah->M;i++){
            TLG maux = ah->v[i];
                if(maux){
                    printf("pos %d: ",i);
                    for(maux = ah->v[i]; maux != NULL; maux = maux->next){
                        printf("(%d:",((TLen*)(maux->info))->len);
                        TLG oau = ((TLen*)(maux->info))->words;
                        SortList(oau);
                        Afisare(&oau,afisareEl);
                        
                    }
                    printf("\n");
                }
            }
        }
    }
}

//Dummy function
int cmpWords(void* e1, void* e2){
    return 1;
}


//returns the size of a word
int wordSize(void* ae){
    TWord* aux = (TWord*) ae;

    return strlen(aux->word);
}

//Insert a TWord Cell in given list
int InsIncWordEntry(TLG* aL, void* ae){
    TLG aux = malloc(sizeof(TCelulaG));
    if(!aux)
        return 0;
    
    aux->info = ae;
    aux->next = *aL;
    *aL = aux;

    return 1;
}

//Allocating memory for a generic list
TLG AlocGenericList(void* ae){
    TLG aux = malloc(sizeof(TCelulaG));
    aux->info = ae;
    aux->next = NULL;

    return aux;
}

//Allocation memory and initialization for a cell that contains size x words
TLen* AlocLenEntry(void* ae){
    TLen* aux = (TLen*) malloc(sizeof(TLen));
    aux->len = strlen(((TWord*)(ae))->word);
    aux->words = AlocGenericList(ae);

    return aux;
}

//Allocating memory and initialization for an entry in Hash Table Vector
TLG AlocVEntry(void* ae){
    
    TLG aux = malloc(sizeof(TCelulaG));
    TLen* len_aux = AlocLenEntry(ae);
    aux->info = len_aux;
    aux->next = NULL;
    return aux;
}

//Insert a vector entry in an existing list
void InsVEntry(TLG* aL,void* ae){
    TLG elem = NULL;
    TLG prev = NULL;

    if(wordSize(ae) < ((TLen*)((*aL)->info))->len){
        elem = AlocVEntry(ae);
        elem->next = *aL;
        *aL = elem;
        return;
    }
    
    for(TLG aux = (*aL); aux != NULL ;prev = aux, aux = aux->next){
        if(wordSize(ae) < ((TLen*)(aux->info))->len &&
        wordSize(ae) > ((TLen*)(prev->info))->len){
            elem = AlocVEntry(ae);
            elem->next = aux;
            prev->next = elem;
            return;
        }
    }

    if(wordSize(ae) > ((TLen*)((prev)->info))->len){
        elem = AlocVEntry(ae);
        prev->next = elem;
    }
}

//Check if the length of word exists in table already
int checkForLen(TLG aL,int size){
    for(TLG aux = aL; aux != NULL; aux = aux->next){
        
        if(((TLen*)(aux->info))->len == size){
            return 1;
        }
    }

    return 0;
}

//Check if the word exists in the table already
int checkForExistingWord(TLG aL,void* ae){
    for(TLG aux = aL; aux != NULL; aux = aux->next){
        if(strcmp(((TWord*)(aux->info))->word,((TWord*)(ae))->word) == 0) {
            ((TWord*)(aux->info))->count++;
            return 1;
        }
    }

    return 0;
}

//Insert a new word in the table
void InsTH(TH* a, void* ae, TFCmp fcmp){
    int cod = a->fh(ae);

    if(a->v[cod] == NULL){
        TLG v_aux = AlocVEntry(ae);

        a->v[cod] = v_aux;
    }
    else{
        
        if(checkForLen(a->v[cod],wordSize(ae)) == 1){
            for(TLG anotherAux = a->v[cod]; anotherAux != NULL;
             anotherAux = anotherAux->next){
                if(((TLen*)(anotherAux->info))->len == wordSize(ae)){
                    
                    if(checkForExistingWord(((TLen*)
                        (anotherAux->info))->words,ae) == 0){
                        InsIncWordEntry(((TLG*)&((TLen*)
                            ((anotherAux)->info))->words),ae);
                    }
                    else{
                        continue;
                    }
                }
            }
        }
        else{
            InsVEntry(&a->v[cod],ae);
        }
    }

}
