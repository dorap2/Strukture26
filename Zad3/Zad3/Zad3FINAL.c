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
#include <string.h>


typedef struct _Person* Position;  //pokazivac tipa _Person

typedef struct _Person {
	char name[30];
	char surname[30];
	int year;
	Position next;

}Person;

int insertBegin(char* name, char* surname, int god, Position p) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));  //alokacija prostora

	newPerson->year = god;
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);

	newPerson->next = NULL;
	insertAfter(p, newPerson);
};

//fja za povezivanje cvorova s headom i cvorova medusobno
int insertAfter(Position p, Position newPerson) {
	newPerson->next = p->next;
	p->next = newPerson;
	return 0;

}

int PrintList(Position p) {
	for (Position q = p->next; q != NULL; q = q->next) {
		printf(" %s %s %d \n", q->name, q->surname, q->year);
	}
	return 0;
}

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
Position findLastName(char* surname, Position p) {
	Position q = NULL;
	for (q = p->next; q != NULL; q = q->next) {
		if (strcmp(q->surname, surname) == 0) {
			printf("Prezime pronadeno");
			return q;
		}
	}
	return NULL;
}


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
			prev = curr;
			curr = curr->next;
		}
	}
	return 0;
}

//A
int insertAfterSurname(Position head, char* LastN) {
	Position newPerson = NULL;
	
	
	Position trazeno = findLastName(LastN, head);
	if (trazeno == NULL) {
		printf("Prezime nije pronadeno");
		return -1;
	}

	newPerson = (Position)malloc(sizeof(Person));

	printf("\nIme osobe koju dodajemo: ");
	scanf("%s", newPerson->name);
	printf("\nPrezime osobe koju dodajemo: ");
	scanf("%s", newPerson->surname);
	printf("\nGodiste osobe koju dodajemo: ");
	scanf("%d", &newPerson->year);   //kod int treba &
	insertAfter(trazeno, newPerson);

	printf("\nNova lista:\n");
	PrintList(head);

	return 0;
}

//B
int insertBeforeSurname(Position head, char* LastN) {
	Position newPerson = NULL;
	Position prev = head;

	while (prev->next != NULL && strcmp(prev->next->surname, LastN) != 0) {
		prev = prev->next;
	}
	if (prev->next == NULL) {
		printf("Prezime nije pronadeno");
		return -1;
	}

	newPerson = (Position)malloc(sizeof(Person));
	
	printf("\nIme osobe koju dodajemo: ");
	scanf("%s", newPerson->name);
	printf("\nPrezime osobe koju dodajemo: ");
	scanf("%s", newPerson->surname);
	printf("\nGodiste osobe koju dodajemo: ");
	scanf("%d", &newPerson->year);  
	
	insertAfter(prev, newPerson);

	printf("\nNova lista:\n");
	PrintList(head);

	return 0;
}

//C- Bubble sort
//provjera-je li lista prazna (head->next ==NULL)
int sortList(Position head) {
	Position q = head;
	Position p = q->next;
	Position temp = NULL;

	while (p->next != NULL) {
		if (strcmp(p->surname, p->next->surname) > 0) {
			temp = p->next;
			q->next = temp;
			p->next = temp->next;
			temp->next = p;
			q = head;
			p = q->next;
		}
		else {
			q = p;
			p = p->next;
		}
	}
}

//D
int writeInFile(Position head) {
	FILE *fp = fopen("zad3.txt", "w");
	if (fp == NULL) {
		printf("\nGreska pri otvaranju");
		return 1;
	}

	for (Position q = head->next; q != NULL; q = q->next) {
		fprintf(fp, "%s %s %d\n", q->name, q->surname, q->year);
	}

	fclose(fp);
	return 0;
}

//E
int readFromFile(Position head) {
	FILE *fp = fopen("zad3.txt", "r");
	char name[30], surname[30];
	int year;

	if (fp == NULL) {
		printf("\nGreska pri otvaranju");
		return 1;
	}

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", name, surname, &year);
		insertEnd(name, surname, year, head);
	}


	fclose(fp);
	return 0;
}



int main() {
	Person Head = { .name = "", .surname = {0}, .year = 0, .next = NULL };
	Person Head2 = { .name = "", .surname = {0}, .year = 0, .next = NULL };
	Position p = &Head;
	Position p2 = &Head2;

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

	printf("\nPrezime osobe iza koje dodajemo: ");
	scanf("%s", trazeno);

	insertAfterSurname(p, trazeno);

	printf("\nPrezime osobe ispred koje dodajemo: ");
	scanf("%s", trazeno);

	insertBeforeSurname(p, trazeno);


	printf("\nSortirana lista:\n");
	sortList(p);
	PrintList(p);

	writeInFile(p);

	readFromFile(p2);
	printf("\nLista iz datoteke:\n");
	PrintList(p2);


	while (p->next != NULL) {
		deletePerson(p->next->surname, p);
	}

	while (p->next != NULL) {
		Position temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;




}