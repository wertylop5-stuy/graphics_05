#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct Matrix {
	float **m;
	int rows;
	int cols;
	int back;	//last-most col that is being used
};

struct Matrix* new_matrix(int r, int c);

void print_matrix(struct Matrix *m);

//turns m into an indentity matrix
//must be a square matrix
void ident(struct Matrix *m);

//b will be modified with the result
//cols dimensions of a must = rows of b
void matrix_mult(struct Matrix const *a, struct Matrix *b);

void free_matrix(struct Matrix *m);

struct Matrix* copy_matrix(struct Matrix *m);

//doubles the amount of columns
void resize(struct Matrix *m);

//transformations
void scale(struct Matrix *t, float a, float b, float c);
void move(struct Matrix *t, float a, float b, float c);
void rotate(struct Matrix *t, char axis, float deg);	//0: x, 1: y, 2: z

#endif
