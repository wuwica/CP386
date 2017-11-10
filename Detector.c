/*
 * Detector.c
 *
 *  Created on: Nov 6, 2017
 *      Author: Jonathan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int bool;
#define true 1
#define false 0

int sumMatrix(int matrix[], int size);
bool update(int matrix[], int size);

int main(int argc, char *argv[]) {

	int ch;

	int n = 0, m = 0;

	scanf("%i %i", &n, &m);
	while ((ch = fgetc(stdin)) == '\n' || isspace(ch))
		;

	ungetc(ch, stdin);

	int n2 = n;
	n = n * 2 + 1;

	int matrix[n][m];

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < m; j++) {
			while ((ch = fgetc(stdin)) != '\n' && isspace(ch))
				;

			if (ch == '\n' || ch == EOF) {
				ch = fgetc(stdin);
			}

			ungetc(ch, stdin);
			if (1 != scanf("%i", &matrix[i][j])) {
				break;
			}
		}

	}
	//save address of U to a new variable for easier referencing
	int* uMatrix = matrix[n - 1];

	int* rMatrix = matrix[0];
	int* aMatrix = matrix[n2];

	int tMatrix[m];
	bool pFlag[n2];
	bool flag = true;
	for (int i = 0; i < m; i++) {
		tMatrix[i] = uMatrix[i];
	}

	for (int process = 0; process < n2; process++) {
		pFlag[process] = update(&aMatrix[process * m], m);
	}
	int remove = -1;
	do {
		//printf("\n");
		do {
			flag = false;
			for (int process = 0; process < n2; process++) {
				if (!pFlag[process]) {
					flag = true;
					for (int i = 0; i < m; i++) {
						if (rMatrix[process * m + i] > tMatrix[i]) {
							flag = false;
							break;
						}
					}
				}
				if (flag && !pFlag[process]) {
					pFlag[process] = true;
					//flag = false;
					printf("%d ", process + 1);
					for (int i = 0; i < m; i++) {
						tMatrix[i] += aMatrix[process * m + i];
					}
				}
			}
		} while (flag);

		printf("\n");
		remove = -1;
		int max = 0, temp = 0; // remove deadlock
		for (int process = 0; process < n2; process++) { //check deadlock
			if (!pFlag[process]) {
				printf("%d ", process + 1); //remove d when done
				if ((temp = sumMatrix(&aMatrix[process * m], m)) > max) {
					remove = process;
					max = temp;
				}
			}
		}

		if (remove != -1) {
			pFlag[remove] = true;
			printf("\n%i\n", remove + 1);
			for (int i = 0; i < m; i++) {
				tMatrix[i] += aMatrix[remove * m + i];
			}
		}
	} while (remove != -1);

}

int sumMatrix(int matrix[], int size) {
	int temp = 0;
	for (int i = 0; i < size; i++) {
		temp += matrix[i];
	}
	return temp;
}

bool matrixCmp(int matrix1[], int matrix2[], int size) {
	for (int i = 0; i < size; i++) {
		if (matrix1[i] > matrix2[i]) {
			return false;
		}
	}
	return true;
}
bool update(int matrix[], int size) {
	int temp = 0;
	for (int i = 0; i < size; i++) {
		//printf("%i ",matrix[i]);
		temp += matrix[i];
	}
	//printf("\n");
	return temp == 0;
}
