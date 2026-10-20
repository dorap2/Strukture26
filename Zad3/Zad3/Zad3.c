/*Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


typedef struct _Person* Position;  //pokazivac tipa _Person

typedef struct _Person {
	char name[30];
	char surname[30];
	int year;
	Position next;

}Person;

//fja UnosIza s predavanja- s int
/*int UnosIza(int x, int y, Pozicija p) {
	Pozicija q;
	p=p->next;

	while (p != NULL && p->Element != y)
		p = p->Next;

	if (p != NULL) {
		q = (Pozicija)malloc(sizeof(cvor));
		q->Element = x;
		q->Next = p->Next;
		p->Next = q;
	}

	return 0;
}*/


int InsertAfter(char* name, char* surname, int god, char* LastN, Position p) {
	Position q = NULL;

	p = p->next; 
	while (p != NULL && strcmp(p->surname, LastN) != 0) {
		p = p->next;
	}

	if (p != NULL) {
		q = (Position)malloc(sizeof(Person));
		if (q == NULL) {
			return -1;
		}

		q->year = god;
		strcpy(q->name, name);
		strcpy(q->surname, surname);

		q->next = p->next;
		p->next = q;
		return 0;
	}

	return -1;   // prezime LastN ne postoji u listi
}


//fja UnosIspred s predavanja- s int
/*
int UnosIspred(int x, int y, Pozicija p) {
	Pozicija q;

	while (p->Next != NULL && p->Next->Element != y)
		p = p->Next;

	if (p->Next != NULL) {
		q = (Pozicija)malloc(sizeof(cvor));
		q->Element = x;
		q->Next = p->Next;
		p->Next = q;
	}

	return 0;
}*/

int InsertBefore(char* name, char* surname, int god, char* LastN, Position p) {
	Position q;

	while (p->next != NULL && strcmp(p->next->surname, LastN) != 0)
		p = p->next;

	if (p->next != NULL) {
		q = (Position)malloc(sizeof(Person));
		q->year = god;
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->next = p->next;
		p->next = q;
	}

	return 0;
}

//UnosSort po prez s predavanja
/*
	while (p->next !=NULL && strcmp(p->next->prez, q->prez)<0)
*/


int UnosSort(char* LastN, Position p) {
	Position q= (Position)malloc(sizeof(Person));

	strcpy(q->surname, LastN);

	while (p->next != NULL && strcmp(p->next->surname, q->surname) < 0) {
		p = p->next;
	}

	q->next = p->next;
	p->next = q;

	return 0;
}







//A
int insertBegin(char* name, char* surname, int god, Position p) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));  //alokacija prostora

	newPerson->year = god;
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);

	newPerson->next = NULL;
	insertAfter(p, newPerson);

	return 0;
};

//fja za povezivanje cvorova s headom i cvorova medusobno
int insertAfter(Position p, Position newPerson) {
	newPerson->next = p->next;
	// KRIVO newPerson->next = newPerson;
	p->next = newPerson;
	return 0;

}

//B
int PrintList(Position p) {
	//Position q;
	//KRIVO for (Position q = p; q->next != NULL; q = q->next) {
	for (Position q = p->next; q != NULL; q = q->next) {
		printf(" %s %s %d \n", q->name, q->surname, q->year);
	}
	return 0;
}

//C
int insertEnd(char* name, char* surname, int god, Position p) {
	while (p->next != NULL) {
		p = p->next;
	}
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	newPerson->year = god;
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);

	newPerson->next = NULL;

	insertAfter(p, newPerson);

	return 0;
}
//D
int findLastName(char* surname, Position p) {
	Position q = NULL;
	for (q = p->next; q != NULL; q = q->next) {
		if (strcmp(q->surname, surname) == 0) {
			printf("Prezime pronadeno");
			return 1;
		}//dodati ispis da je pronadeno
	}
	return 0;
}

//E

int deletePerson(char* LastN, Position p) {
	Position curr = NULL;
	Position prev = p;

	curr = prev->next;

	//usporedba el
	while (curr != NULL) { //prolazi cijelu listu
		if (strcmp(curr->surname, LastN) == 0) {
			prev->next = curr->next;
			free(curr);
			return 1;
		}

		else {
			//prev = prev->next;
			//curr = prev->next;
			prev = curr;
			curr = curr->next;
		}
	}
	return 0;
}



int main() {
	Person Head = { .name = "", .surname = {0}, .year = 0, .next = NULL };
	Position p = &Head;

	char trazeno[30];
	char del_prezime[30];

	insertBegin("Ana", "Anic", 2003, p);
	insertBegin("Dora", "Doric", 2004, p);
	insertBegin("Lana", "Lanic", 2005, p);
	insertEnd("Marko", "Markic", 2001, p);
	insertEnd("Ivan", "Ivic", 2002, p);

	printf("Lista:\n");
	PrintList(p);

	printf("\nKoje prezime trazimo:  ");
	scanf("%s", trazeno);
	//findLastName(trazeno, p);

	if (!findLastName(trazeno, p))
		printf("\nPrezime nije pronadeno");

	printf("\nOsoba koju brisemo (prezime):");
	scanf("%s", del_prezime);
	if (!findLastName(del_prezime, p))
		printf("\nPrezime nije pronadeno, nije moguce izbrisati");
	else {
		deletePerson(del_prezime, p);
		printf("\nOsoba izbrisana");
	}

	printf("\nNova lista:\n");
	PrintList(p);


	while (p->next != NULL) {
		deletePerson(p->next->surname, p);
	}

	while (p->next != NULL) {
		Position temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	/*
	InsertBefore("Pero", "Peric", 1999,"Doric", p);

  
    InsertAfter("Nika", "Nikic", 1898, "Lalic", p); 

    
    UnosSort("Babić", p);
    UnosSort("Anić", p);
    UnosSort("Marić", p);

    PrintList(p);*/



























	return 0;



}