#include "matrix.h"

int main()
{
	REAL a[3 * 3] = { 1,2,3,6,5,5,8,7,2 };
	REAL b[3 * 3] = {1,2,3,6,5,4,3,2,1};
	MATRIX *A = NULL, * B = NULL, * C = NULL, * D = NULL, * E = NULL, * Z = NULL, * invA = NULL, *m = NULL;
	ERROR_ID errorID = _ERROR_NO_ERROR;
	REAL trace;
	STACKS S;

	init_stack(&S);

	Z = creat_zero_matrix(3, 3, &errorID, &S);
	print_matrix(Z, "Z");

	E = creat_eye_matrix(3, &errorID, &S);
	print_matrix(E, "E");

	A = creat_matrix(3, 3, &errorID, &S);
	A->p = a;
	print_matrix(A, "A");

	B = creat_matrix(3, 3, &errorID, &S);
	B->p = b;
	print_matrix(B, "B");

	C = creat_matrix(3, 3, &errorID, &S);
	D = creat_matrix(3, 3, &errorID, &S);
	invA = creat_matrix(3, 3, &errorID, &S);

	errorID = matrix_add(A, B, C);
	errorID = matrix_subtraction(A, B, C);
	errorID = matrix_multiplication(A, B, C);

	errorID = matrix_transpose(A, D);
	print_matrix(D, "D");

	errorID = matrix_trace(A, &trace);

	errorID = matrix_inverse(A, invA);
    print_matrix(invA, "invA");

	errorID = matrix_multiplication(invA, A, Z);
	print_matrix(Z, "Z");

	m = creat_multiple_matrices(3, 3, 2, &errorID, &S);
	m[0].p = a;
	m[1].p = b;

	free_stack(&S);

	return 0;
}
