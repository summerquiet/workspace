#include "inl_matrix.h"

int main()
{
    REAL a[3 * 3] = { 1,2,3,6,5,5,8,7,2 };
    REAL b[3 * 3] = {1,2,3,6,5,4,3,2,1};
    MATRIX *A = NULL, * B = NULL, * C = NULL, * D = NULL, * E = NULL, * Z = NULL, * invA = NULL, *m = NULL;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    REAL trace = 0.0;
    STACKS S;

    init_stack(&S);

    Z = creat_zero_matrix(3, 3, &errorID, &S);
    print_matrix(Z, "Z");

    E = creat_eye_matrix(3, &errorID, &S);
    print_matrix(E, "E");

    A = creat_matrix(3, 3, &errorID, &S);
    set_matrix_by_array(A, a, 9);
    print_matrix(A, "A");

    B = creat_matrix(3, 3, &errorID, &S);
    set_matrix_by_array(B, b, 9);
    print_matrix(B, "B");

    C = creat_matrix(3, 3, &errorID, &S);
#if 0
    errorID = matrix_add(A, B, C);
    print_matrix(C, "C");

    errorID = matrix_subtraction(A, B, C);
    print_matrix(C, "C");

    errorID = matrix_multiplication(A, B, C);
    print_matrix(C, "C");

    D = creat_matrix(3, 3, &errorID, &S);
    errorID = matrix_transpose(A, D);
    print_matrix(D, "D");

    invA = creat_matrix(3, 3, &errorID, &S);
    errorID = matrix_inverse(A, invA);
    print_matrix(invA, "invA");
#endif

    errorID = matrix_trace(A, &trace);
    printf("errorID: 0x%x, trace: %f\n", errorID, trace);

    REAL norm = 0.0;
    MATRIX* N = creat_matrix(3, 3, &errorID, &S);
    REAL n[3 * 3] = {-3, 2, 0, 5, 6, 2, 7, 4, 8};
    set_matrix_by_array(N, n, 9);
    errorID = matrix_norm(N, &norm);
    printf("errorID: 0x%x, norm: %f\n",  errorID, norm);

#if 0
    m = creat_multiple_matrices(3, 3, 2, &errorID, &S);
    m[0].p = a;
    m[1].p = b;
#endif

    free_stack(&S);

    return 0;
}
