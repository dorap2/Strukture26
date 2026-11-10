//5. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa rezultat. 
//Stog je potrebno realizirati preko vezane liste


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Cvor {
    double vrijednost;
    struct Cvor* sljedeci;
} Cvor;

//dodavanje na vrh stoga
int push(Cvor** vrh, double vrijednost) {  
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));

    if (novi == NULL) {
        printf("Greska pri alokaciji memorije");
        return 0;
    }

    novi->vrijednost = vrijednost;
    novi->sljedeci = *vrh;
    *vrh = novi;

    return 1;
}

//uklanjanje s vrha stoga 
int pop(Cvor** vrh, double* vrijednost) {
    if (*vrh == NULL) {
        printf("Greska- prazan stog");
        return 0;
    }

    Cvor* pomocni = *vrh;

    *vrijednost = pomocni->vrijednost;
    *vrh = pomocni->sljedeci;

    free(pomocni);

    return 1;
}

int izracunajIzraz(FILE* datoteka, double* rezultat) {
    Cvor* vrh = NULL;
    char znak[50];
    double a, b;

    while (fscanf(datoteka, "%s", znak) != EOF) {

        //broj ide na stog
        if (znak[0] >= '0' && znak[0] <= '9') {
            push(&vrh, atof(znak));    //str u double
        }
        else {
            //ako je operator, skida 2 broja
            pop(&vrh, &b);
            pop(&vrh, &a);

            if (znak[0] == '+') 
                push(&vrh, a + b);
            if (znak[0] == '-') 
                push(&vrh, a - b);
            if (znak[0] == '*') 
                push(&vrh, a * b);
            if (znak[0] == '/') 
                push(&vrh, a / b);
        }
    }

    //uzmi rezultat
    pop(&vrh, rezultat);
    return 1;
}

int main() {
    FILE* datoteka;
    double rezultat;

    datoteka = fopen("postfixdatoteka.txt", "r");

    if (datoteka == NULL) {
        printf("Greska pri otvaranju datoteke");
        return 1;
    }

    if (izracunajIzraz(datoteka, &rezultat)) {
        printf("Rezultat: %f", rezultat);
    }

    fclose(datoteka);

    return 0;
}