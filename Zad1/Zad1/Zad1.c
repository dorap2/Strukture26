/*1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_BR_BODOVA 50

typedef struct _Student {
    char name[30];
    char surname[30];
    int bodovi;
}stud;


int main() {
    stud* studenti = NULL; //deklaracija pokazivaca na strukturu stud

    FILE* dat;
    dat = fopen("dat.txt", "r");  //otvaranje datoteke za citanje
    if (!dat) {         //!dat isto sto i dat==NULL
        printf("Greska- datoteka!");     //provjera otvaranja datoteke
        return -1;
    }
    char buffer[50] = { 0 };
    int counter = 0;

    while (fgets(buffer, 50, dat) != NULL) {  //citanje liniju po liniju FGETS(niz u koji se sprema, max br znakova -1, dat iz koje cita)
        counter++;      //broj studenata
    }

    studenti = (stud*)malloc(counter * sizeof(stud));
    if (!studenti) {
        printf("Greska- alokacija!");
        //fclose(dat); //na izlazu iz datoteke
        return -1;
    }

    rewind(dat);  //vracamo se na pocetak datoteke nakon fgets


    for (int i = 0; i < counter; i++) {    //ucitavanje i spremanje
        fscanf(dat, "%s %s %d", studenti[i].name, studenti[i].surname, &studenti[i].bodovi);  //&bodovi-scanf treba adresu, obican int
    }

    

    for (int i = 0; i < counter; i++) {
        double relativna = (double)studenti[i].bodovi / MAX_BR_BODOVA * 100;
        printf("%s %s -apsolutni broj bodova: %d, relativni broj bodobva: %.2f %%\n",      //format ispisa- string string cijeli br decimalni br %
            studenti[i].name,
            studenti[i].surname,
            studenti[i].bodovi,
            relativna);
    }


    free(studenti); //!!!
    fclose(dat);

    return 0;
}