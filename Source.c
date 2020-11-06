#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coeff;
	int exp;
	Position next;
}polinom;


Position createPolinom(int, int);

int main() {
	FILE* File;
	Position P = NULL;
	Position head = NULL;
	int coeff = 0, exp = 0;
	char datName[256];
	printf("Unesi ime datoteke: ");
	scanf("%s", datName);
	File = fopen(datName, "r");
	if (!File)
		printf("File failed to open!");
	
	int n;
	char *buffer=malloc(1024);
	while (1) {
		if (fgets(buffer, 50, File) == '\0')
			break;
		n++;
	}
	for (int i = 0;i < n;i++) {
		fscanf(File, "%d %d", &coeff, &exp);
		P = createPolinom(coeff, exp);
	}
}

Position createStudent(int coeff, int exp) {
	Position P = NULL;
	
	P = (Position)malloc(sizeof(polinom));
	if (!P)
		printf("Memory failed to allocate!");
	
	P->coeff = coeff;
	P->exp = exp;

	return P;
}