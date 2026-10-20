/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
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

//A
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
	// KRIVO newPerson->next = newPerson;
	p->next = newPerson;
	return 0;

}

//B
int PrintList(Position p) {
	//Position q;
	//KRIVO for (Position q = p; q->next != NULL; q = q->next) {
	for (Position q = p->next; q!= NULL; q = q->next){
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
	
	insertAfter(p,newPerson);

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



int main(){
	Person Head = { .name = "", .surname = {0}, .year = 0, .next = NULL};
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
	return 0;



}