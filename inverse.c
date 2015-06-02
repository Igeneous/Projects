/*
 * inverse.c
 *
 *  Created on: May 31, 2015
 *      Author: michaelzhao1
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void printMatrix(float *a, int size);
int invert(float *a, int n);
void gaussian(float *a, float *b, int n);
void swapRows(float *a, int irow, int jrow, int n);
int ind(int i, int j, int n);

int main() {
	int i, n;
	float *a, *d;

	printf("Size to be entered:");
	scanf("%d", &n);

	a = (float*) calloc(n * n, sizeof(float));
	if (a == NULL) {
		printf("a memory allocation error");
		return (0);
	}
	d = (float*) calloc(n * n, sizeof(float));
	if (d == NULL) {
		printf("a memory allocation error");
		return (0);
	}
	printf("Enter %d numbers:\n", n * n);
	for (i = 0; i < n * n; i++) {
		scanf("%f", &a[i]);
	}
	//invert a
	int result = invert(a, n);
	if (result == 0) {
		printf("invert failed");
		return (0);
	}
	printf("\n");
	printMatrix(a, n);
	return (0);
}

int invert(float *a, int n) {
	float *b, *x;
	b = (float*) calloc(n * n, sizeof(float));
	if (b == NULL) {
		printf("b memory allocation error");
		return 0;
	}
	x = (float*) calloc(n * n, sizeof(float));
	if (x == NULL) {
		printf("x memory allocation error");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		b[i * (n - 1) * (n - 1)] = 1;
	}
	printMatrix(a, n);
	printMatrix(b, n);
	gaussian(a, b, n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < n; k++) {
				b[ind(j, k, n)] -= a[ind(j, i, n)] * b[ind(i, k, n)];
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		x[ind(n - 1, i, n)] = b[ind(n - 1, i, n)] / a[ind(n - 1, n - 1, n)];
		for (int j = n - 2; j >= 0; --j) {

			x[ind(j, i, n)] = b[ind(j, i, n)];

			for (int k = j + 1; k < n; ++k) {

				x[ind(j, i, n)] -= a[ind(j, k, n)] * x[ind(k, i, n)];
			}

			x[ind(j, i, n)] /= a[ind(j, j, n)];
		}
	}
	for (int i = 0; i < n*n; i++) {
		a[i] = x[i];
	}
	free(b);
	free(x);
	return 1;
}

void gaussian(float *a, float *b, int n) {
	float *c;
	c = (float*) calloc(n, sizeof(float));
	if (c == NULL) {
		printf("c memory allocation error");
	}
	for (int i = 0; i < n; i++) {
		float c1 = 0;
		for (int j = 0; j < n; j++) {
			float c0 = fabsf(a[ind(i, j, n)]);
			if (c0 > c1) {
				c1 = c0;
			}
			c[i] = c1;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%f ", c[i]);
		printf("\n");
	}
	int k = 0;
	for (int j = 0; j < n - 1; j++) {
		float pi1 = 0;
		for (int i = j; i < n; i++) {
			float pi0 = fabsf(a[ind(i, j, n)]);
			pi0 /= c[i];
			printf("pi0 = %f\n", pi0);
			printf("pi1 = %f\n", pi1);
			if (pi0 > pi1) {
				pi1 = pi0;
				k = i;
			}
		}
		printf("pi1 = %f\n", pi1);
		printf("k = %d\n", k);

		swapRows(a, j, k, n);
		swapRows(b, j, k, n);
		double temp = c[j];
		c[j] = c[k];
		c[k] = temp;
		for (int i = j + 1; i < n; i++) {
			double pj = a[ind(i, j, n)] / a[ind(j, j, n)];
			a[ind(i, j, n)] = pj;
			for (int l = j + 1; l < n; l++) {
				a[ind(i, l, n)] -= pj * a[ind(j, l, n)];
			}
		}
	}
}
int ind(int i, int j, int n) {
	return (j + i * n);
}

void swapRows(float *a, int j, int k, int n) {
	for (int i = 0; i < n; i++) {
		double temp1 = a[i + n * k];
		a[i + n * k] = a[i + n * j];
		a[i + n * j] = temp1;
	}
}

void printMatrix(float *a, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		printf("\n");
		for (j = 0; j < size; j++) {
			printf(" %f", a[j + i * size]);
		}
	}
	printf("\n");
}

