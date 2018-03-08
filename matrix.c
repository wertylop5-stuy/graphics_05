#include "include/matrix.h"

struct Matrix* new_matrix(int r, int c) {
	struct Matrix *res = (struct Matrix*)malloc(sizeof(struct Matrix));
	res->rows = r;
	res->cols = c;
	res->back = 0;
	
	res->m = (float **)malloc(r*sizeof(float *));
	
	float **pos;
	for (pos = res->m;
			(pos - res->m) < r;
			pos++ ) {
		*pos = (float *)malloc(c*sizeof(float));
	}
	
	return res;
}

void print_matrix(struct Matrix *m) {
	float *pos;
	float **temp;
	for (temp = m->m; m->back != 0 && (temp - m->m) < m->rows; temp++) {
		for (pos = *temp; (pos - *temp) < m->back; pos++) {
			printf("%.2f\t", *pos);
		}
		printf("\n");
	}
	
	printf("\n");
}

void ident(struct Matrix *m) {
	int r = 0, c = 0;
	
	if (m->cols != m->rows) {
		fprintf(stderr, "ident: matrix is not square\n");
		return;
	}
	
	for (; r < m->rows; r++) {
		for (c = 0; c < m->cols; c++) {
			if (r == c) {
				m->m[r][c] = 1.0f;
			}
			else {
				m->m[r][c] = 0.0f;
			}
		}
	}
	m->back = m->cols;
}

void matrix_mult(struct Matrix const *a, struct Matrix *b) {
	int x, r, c;
	float total;
	struct Matrix *temp = copy_matrix(b);
	
	for (x = 0; x < b->back; x++) {
		for (r = 0; r < a->rows; r++) {
			total = 0.0f;
			for (c = 0; c < a->back; c++) {
				total += (temp->m[c][x] * a->m[r][c]);
			}
			b->m[r][x] = total;
		}
	}
	free_matrix(temp);
}

void free_matrix(struct Matrix *m) {
	float **pos;
	for (pos = m->m; (pos - m->m) < m->rows; pos++) {
		free(*pos);
	}
	free(m->m);
	free(m);
}

struct Matrix* copy_matrix(struct Matrix *m) {
	struct Matrix *n = new_matrix(m->rows, m->back);
	n->back = m->back;

	int x;
	for (x = 0; x < n->rows; x++) {
		memcpy(n->m[x], m->m[x], n->back*sizeof(float));
	}
	
	return n;
}

void resize(struct Matrix *m) {
	int counter;
	for (counter = 0; counter < m->rows; counter++) {
		m->m[counter] = realloc(m->m[counter], m->cols*2*sizeof(float));
	}
	m->cols *= 2;
}

void scale(struct Matrix *t, float a, float b, float c) {
	struct Matrix *temp = new_matrix(4, 4);
	ident(temp);
	
	temp->m[0][0] = a;
	temp->m[1][1] = b;
	temp->m[2][2] = c;
	
	matrix_mult(temp, t);
	free_matrix(temp);
}

void move(struct Matrix *t, float a, float b, float c) {
	struct Matrix *temp = new_matrix(4, 4);
	ident(temp);
	
	temp->m[0][3] = a;
	temp->m[1][3] = b;
	temp->m[2][3] = c;
	
	matrix_mult(temp, t);
	free_matrix(temp);
}

void rotate(struct Matrix *t, char axis, float deg) {
	struct Matrix *temp = new_matrix(4, 4);
	ident(temp);
	float rad = deg * (M_PI/180.0f);
	
	switch(axis) {
		case 'z':
			temp->m[0][0] = cosf(rad);
			temp->m[0][1] = -sinf(rad);
			temp->m[1][0] = sinf(rad);
			temp->m[1][1] = cosf(rad);
		break;
		
		case 'x':
			temp->m[1][1] = cosf(rad);
			temp->m[1][2] = -sinf(rad);
			temp->m[2][1] = sinf(rad);
			temp->m[2][2] = cosf(rad);
		break;
		
		case 'y':
			temp->m[0][0] = cosf(rad);
			temp->m[2][0] = -sinf(rad);
			temp->m[0][2] = sinf(rad);
			temp->m[2][2] = cosf(rad);
		break;
	}

	matrix_mult(temp, t);
	free_matrix(temp);
}


