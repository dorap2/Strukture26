//4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortira
/*
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Poly* Position;

typedef struct Poly {
	int coeff;
	int pow;
	Position next;
}polynom;


//zbrajanje polinoma : 1) ista potencija = >zbroji koeficijente, sort unos
			//	2) nije ista potencija=>sort unos neiskorištene potencije
			//  3) if(p->coeff==0) free (p)

//mnozenje polinoma: prvi el. headFirst mnoziti sa svakim headSecond
				//za buduca mnozenja=> provjera zbrajanja!
				//prvi-> coeff*= drugi->coeff;
				//prvi->pow +=drugi->pow;
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct _Poly* Position;

typedef struct _Poly {
	int coeff;
	int pow;
	Position next;
} Poly;

int insertAfter(Position p, Position newEl) {
	newEl->next = p->next;
	p->next = newEl;
	return 0;
}

int insertSorted(Position head, int coeff, int pow) {
	Position prev = head;
	Position newEl = NULL;

	while (prev->next != NULL && prev->next->pow > pow)
		prev = prev->next;

	newEl = (Position)malloc(sizeof(Poly));
	if (newEl == NULL)
		return 0;

	newEl->coeff = coeff;
	newEl->pow = pow;
	insertAfter(prev, newEl);

	return 0;
}

int readPoly(FILE* fp, Position head) {
	int coeff, pow;
	int c;                              // int zbog EOF

	while (fscanf(fp, "%d %d", &coeff, &pow) == 2) {
		insertSorted(head, coeff, pow);

		c = fgetc(fp);                  // procitaj znak iza para
		while (c == ' ')                   // preskoci razmake
			c = fgetc(fp);

		if (c == '\n' || c == EOF)      // kraj retka ili datoteke
			break;

		ungetc(c, fp);                // pocetak sljedeceg broja->vrati ga
	}

	return 0;
}


int readFile(char* fileName, Position head1, Position head2) {
	FILE* fp = fopen(fileName, "r");

	if (fp == NULL) {
		printf("Greska kod otvaranja datoteke");
		return 0;
	}

	readPoly(fp, head1);
	readPoly(fp, head2);

	fclose(fp);
	return 1;                          
}

//zbrajanje polinoma : 1) ista potencija = >zbroji koeficijente, sort unos
			//	2) nije ista potencija=>sort unos neiskorištene potencije
			//  3) if(p->coeff==0) free (p)
int addPoly(Position first, Position second, Position result) {
	Position p = first->next;
	Position q = second->next;
	int sum;

	while (p != NULL && q != NULL) {
		if (p->pow == q->pow) {              //ista potencija->zbroji
			sum = p->coeff + q->coeff;
			if (sum != 0)                           
				insertSorted(result, sum, p->pow);
			p = p->next;
			q = q->next;
		}
		else if (p->pow > q->pow) {          //p ima vecu potenciju->prepisi p
			insertSorted(result, p->coeff, p->pow);
			p = p->next;
		}
		else {                               //q ima vecu potenciju->prepisi q
			insertSorted(result, q->coeff, q->pow);
			q = q->next;
		}
	}

	while (p != NULL) {                      // ostatak prvog
		insertSorted(result, p->coeff, p->pow);
		p = p->next;
	}

	while (q != NULL) {                      // ostatak drugog
		insertSorted(result, q->coeff, q->pow);
		q = q->next;
	}

	return 0;
}

int multiplyPoly(Position first, Position second, Position result) {
	Position p = NULL;
	Position q = NULL;
	Position r = NULL;
	int coeff, pow;

	for (p = first->next; p != NULL; p = p->next) {
		for (q = second->next; q != NULL; q = q->next) {
			coeff = p->coeff * q->coeff;
			pow = p->pow + q->pow;

			r = result->next;                    // trazi istu potenciju
			while (r != NULL && r->pow != pow)
				r = r->next;

			if (r != NULL)
				r->coeff += coeff;               // nasao->zbroji
			else
				insertSorted(result, coeff, pow);   // nije->ubaci novi
		}
	}

	return 0;
}

int printPoly(Position head) {
	Position q = NULL;

	for (q = head->next; q != NULL; q = q->next)
		printf("%+dx^%d ", q->coeff, q->pow);

	printf("\n");
	return 0;
}

int freeList(Position head) {
	Position temp = NULL;

	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return 0;
}

int main() {
	Poly p1 = { 0, 0, NULL };
	Poly p2 = { 0, 0, NULL };
	Poly sum = { 0, 0, NULL };
	Poly prod = { 0, 0, NULL };

	if (!readFile("C:\\Projekti\\Strukture_podataka\\Zad4\\x64\\Debug\\polinomi.txt", &p1, &p2))
		return 0;

	printf("1. polinom:      "); printPoly(&p1);
	printf("2. polinom:      "); printPoly(&p2);

	addPoly(&p1, &p2, &sum);
	printf("Zbroj:   "); printPoly(&sum);

	multiplyPoly(&p1, &p2, &prod);
	printf("Umnozak: "); printPoly(&prod);

	freeList(&p1);
	freeList(&p2);
	freeList(&sum);
	freeList(&prod);

	return 0;
}