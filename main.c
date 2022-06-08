//Robert-Andrei Raucescu 335CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Helpers.h"


int main(int argc, char* argv[]){
    char* input = malloc(sizeof(char)*250);
    char* ptr;
    TH* h = NULL;
    TWord* aux;

    FILE* f = fopen(argv[1],"r");
    if(!f){
        printf("Eroare la deschiderea fisierului!");
    }
    
    size_t M = ('Z'-'A'); // Determine size of Hash Table
    h = (TH*) InitTH(M+1,codHash);


    while(fgets(input,250,f)){ //Parse input commands
        ptr = strtok(input," \n");
        

        if(strcmp(ptr,"insert") == 0){ // Break input in words to be inserted
            ptr = strtok(NULL," ,.");
            while(ptr != NULL){
                if(strlen(ptr) >= 3){
                    
                    if(ptr[strlen(ptr) - 1] == '\n')
                        ptr[strlen(ptr) - 1] = '\0';
                    
                    
                    aux = AlocTWord(ptr);
                    InsTH(h,aux,cmpWords);
                }

                ptr = strtok(NULL," ,.");

            }
        }

        else{
            if(strcmp(ptr,"print") == 0){ 
            // Parse print parameters to determine how to print
                ptr = strtok(NULL," ,.");
                if(!ptr)
                    AfiTH(h,afisareEl,-1,-1);//Print all the Hash Tble
                else{
                    if((*ptr >= 'a' && *ptr <= 'z') ||
                     (*ptr >= 'A' && *ptr <= 'Z')){
                        char first = *ptr;
                        ptr = strtok(NULL," ,.");
                        if(first >= 'a' && first <= 'z')
                            //Print with a first letter and length condition
                            AfiTH(h,afisareEl,first-'a',atoi(ptr));
                        else
                            AfiTH(h,afisareEl,first-'A',atoi(ptr));
                    }
                    else{
                        //Print with a max_count condition
                        AfiTH(h,afisareEl,-1,atoi(ptr));
                    }
                }
                
                

            }
        }        
    }
    

    fclose(f);

    return 0;
}