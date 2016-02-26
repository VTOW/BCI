#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

typedef struct Mat2x1
{
	float data[2];
} Mat2x1;

typedef struct Mat2x2
{
	float data[2][2];
} Mat2x2;

void mat2x1_init(mat2x1 *mat)
{
	mat->data[0] = 0;
	mat->data[1] = 0;
}

void mat2x2_init(mat2x2 *mat)
{
	mat->data[0][0] = 0;
	mat->data[0][1] = 0;
	mat->data[1][0] = 0;
	mat->data[1][1] = 0;
}

mat2x1* mat2x2_2x1_mul(mat2x2 *mat1, mat2x1 *mat2)
{
	mat2x1 final = mat2x1_init(&final);

	final.data[0] = mat1->
}

#endif //MATRIX_H_INCLUDED
