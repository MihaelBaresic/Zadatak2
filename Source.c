#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M (256)

struct _person;
typedef struct _person* Position;

typedef struct _person {
	char firstName[M];
	char lastName[M];
	int year;
	Position next;
}Person;

Position createStudent(char*, char*, int);
void insertStart(Position, Position);
void printList(Position);
void insertEnd(Position, Position);
Position Find(char*, Position);
void Delete(Position, Position);
Position findPrev(char*, Position);
void insertAfter(Position, Position);
void insertBefore(Position, Position);
void Sort(Position);
int createNode(char*, char*, int);
void insertList(char*, Position);
int countRows(char*);

int main(void)
{
	FILE* Dat;
	char c;
	Person head;
	Position p = NULL;
	char firstName[M] = { NULL };
	char lastName[M] = { NULL };
	int year=0;
	head.next = NULL;
	int i, n;

	printf("\nHow many students do you want to enter:\t");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		year=createNode(firstName, lastName, year);
		p = createStudent(firstName, lastName, year);
		insertStart(&head, p);
		puts("\n");
		printList(&head);
	}

	while (1) {

		printf("\n\nMENU:\nChoose one option:\n\tB->insert new person at the beginning of the list\n");
		printf("\tA->insert new person at the end of the list\n\tF->find a person(by last name)\n\tD->delete a person\n\tC->Input list to text file");
		printf("\n\tI->insert new person after selected person\n\tU->insert new person before selected person\n\tS->Sort List(by last names)\n");
		printf("\tR->Read list from file\n\tE->if you are done with the selection\n\tOption:\t");
		scanf(" %c", &c);

		switch (c)
		{
		case 'b':
		case 'B':
			year = createNode(firstName, lastName, year);
			p = createStudent(firstName, lastName, year);
			insertStart(&head, p);
			puts("\n");
			printList(&head);
			break;
		case 'a':
		case 'A':
			year = createNode(firstName, lastName, year);
			p = createStudent(firstName, lastName, year);
			insertEnd(&head, p);
			puts("\n");
			printList(&head);
			break;
		case'r':
		case'R':
			printf("Insert file name: ");
			char fileN[M];
			scanf("%s", fileN);
			int n = countRows(fileN);
			FILE* Dat;
			Dat = fopen(fileN, "r");
			if (!Dat)
				printf("File not opened correctly!");
			for (i = 0; i < n; i++) {
				fscanf(Dat, "%s %s %d", firstName, lastName, &year);
				p = createStudent(firstName, lastName, year);
				insertStart(&head, p);
				puts("\n");
			}
			printList(&head);
			break;
		case 'f':
		case 'F':
			printf("\nPlease insert person last name:");
			scanf("%s", lastName);
			puts("\n");
			p = Find(lastName, &head);
			if (p != NULL)
				printf("\t\nFound: %s %s %d\n", p->firstName, p->lastName, p->year);
			else
				printf("Last name not found in linked list!");
			printList(&head);
			break;
		case 'c':
		case 'C':
			printf("Insert file name: ");
			char fileNm[M];
			scanf("%s", fileNm);
			insertList(fileNm, &head);
			break;
		case 'd':
		case 'D':
			printf("\nPlease insert person last name:");
			scanf(" %s", lastName);
			puts("\n");
			Delete(lastName, &head);
			printList(&head);
			break;
		case 'E':
		case 'e':
			printList(&head);
			return EXIT_SUCCESS;
			break;
		case 'I':
		case 'i':
			year = createNode(firstName, lastName, year);
			p = createStudent(firstName, lastName, year);
			insertAfter(&head, p);
			puts("\n");
			printList(&head);

			break;
		case 'U':
		case 'u':
			year = createNode(firstName, lastName, year);
			p = createStudent(firstName, lastName, year);
			insertBefore(&head, p);
			puts("\n");
			printList(&head);
			break;
		case 's':
		case 'S':
			Sort(&head);
			puts("\n");
			printList(&head);
			break;

		default:
			puts("Input error!!");
		}
	}
	return 0;
}

int createNode(char* firstName, char* lastName, int year) {
	printf("\nPlease insert person:\n");

	printf("First name:\t");
	scanf(" %s", firstName);

	printf("Last name:\t");
	scanf(" %s", lastName);

	printf("Birth year:\t");
	scanf(" %d", &year);
	
	return year;
}

Position createStudent(char* firstName, char* lastName, int year) {
	Position p = NULL;

	p = (Position)malloc(sizeof(Person));

	if (!p) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);
	p->year = year;
	p->next = NULL;

	return p;

}

void insertEnd(Position head, Position p) {
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = p;
	p->next = NULL;
}


void insertStart(Position head, Position p) {
	p->next = head->next;
	head->next = p;
}

Position Find(char* lastName, Position head) {
	Position p = NULL;
	p = head->next;
	int L = 0;

	while (p != NULL) {
		if (strcmp(p->lastName, lastName) == 0) {
			L = 1;
			break;
		}
		else
			L = 0;
		p = p->next;
	}
	if (L == 1)
		return p;
	else
		return NULL;
}


Position findPrev(char* lastName, Position P) {
	Position prev = P;
	P = P->next;

	while (P != NULL && strcmp(P->lastName, lastName) != 0) {
		prev = P;
		P = P->next;
	}
	if (P == NULL)
		return NULL;
	else
		return prev;
}

void insertAfter(Position head, Position p) {
	Position q = NULL;

	char lName[M] = { NULL };
	printf("\nPlease insert person last name:");
	scanf("%s", lName);
	q = Find(lName, head);

	p->next = q->next;
	q->next = p;
}


void insertBefore(Position head, Position p) {
	Position q = NULL;

	char lName[M] = { NULL };
	printf("\nPlease insert person last name:");
	scanf("%s", lName);
	q = findPrev(lName, head);

	p->next = q->next;
	q->next = p;

}

void Sort(Position where)
{
	Position end = NULL, temp, what, prev;

	while (where->next != end)
	{
		prev = where;
		what = where->next;
		while (what->next != end)
		{
			if (strcmp(what->lastName, what->next->lastName) > 0)
			{
				temp = what->next;
				prev->next = temp;
				what->next = temp->next;
				temp->next = what;
				what = temp;
			}
			else if (strcmp(what->lastName, what->next->lastName) == 0)
			{
				if (strcmp(what->firstName, what->next->firstName) > 0)
				{
					temp = what->next;
					prev->next = temp;
					what->next = temp->next;
					temp->next = what;
					what = temp;
				}
			}

			prev = what;
			what = what->next;
		}
		end = what;
	}
}


void Delete(char* lastName, Position P) {
	Position prev;
	prev = findPrev(lastName, P);

	if (prev != NULL)
	{
		P = prev->next;
		prev->next = P->next;
		free(P);
	}
	else
		printf("Last name not found in linked list!");
}

void insertList(char* fileN, Position p) {
	FILE* Dat;
	Dat = fopen(fileN, "w");
	if (!Dat)
		printf("Failed to open file!");
	if (p->next == NULL)
		fprintf(Dat, "Linked list is empty!");
	Position q=p->next;

	while (q != NULL) {
		fprintf(Dat,"%s %s %d\n", q->firstName, q->lastName, q->year);
		q = q->next;
	}
}

int countRows(char* fileName) 
{
	FILE* Dat;
	Dat = fopen(fileName, "r");
	if (!Dat)
	printf("Krivo otvorena datoteka");
	int n = 0;
	char* buffer = malloc(1024);
	while (1) {
		if (fgets(buffer, 50, Dat) == '\0')
			break;
		n++;
	}
	fclose(Dat);
	return n;
}

void printList(Position head) {
	Position p = NULL;
	printf("\nlist content:\n");
	if (head->next == NULL)
		printf("Linked list is empty!");
	for (p = head->next; p != NULL; p = p->next)
		printf("\t%s %s %d\n", p->firstName, p->lastName, p->year);

	printf("\n");

}
