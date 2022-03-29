#include <time.h>
#include "inl_matrix.h"

int64_t GetTickCount(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

int main()
{
    REAL a[3 * 3] = { 1,2,3,6,5,5,8,7,2 };
    REAL b[3 * 3] = {1,2,3,6,5,4,3,2,1};
    MATRIX *A = NULL, * B = NULL, * C = NULL, * D = NULL, * E = NULL, * Z = NULL, * invA = NULL, *m = NULL;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    REAL trace = 0.0;
    STACKS S;

    int64_t tick_strat = GetTickCount();

    int times = 1;
    for (int i = 0; i < times; i++) {
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

        // case 1: add
        errorID = matrix_add(A, B, C);
        print_matrix(C, "add");

        // case 2: sub
        errorID = matrix_subtraction(A, B, C);
        print_matrix(C, "sub");

        // case 3: multi
        errorID = matrix_multiplication(A, B, C);
        print_matrix(C, "multi");

        // case 4: trans
        errorID = matrix_transpose(A, C);
        print_matrix(C, "trans");

        // case 5: inverse
        errorID = matrix_inverse(A, C);
        print_matrix(C, "inverse");

        // case 6: trace
        errorID = matrix_trace(A, &trace);
        printf("errorID: 0x%x, trace: %f\n", errorID, trace);

        REAL norm = 0.0;
        MATRIX* N = creat_matrix(3, 3, &errorID, &S);
        REAL n[3 * 3] = {-3, 2, 0, 5, 6, 2, 7, 4, 8};
        set_matrix_by_array(N, n, 9);
        // print_matrix(N, "N");

        // case 7: norm
        errorID = matrix_norm(N, &norm);
        printf("errorID: 0x%x, norm: %f\n",  errorID, norm);

        REAL item = 0.0;
        errorID = get_matrix_item(N, 2, 2, &item);
        printf("errorID: 0x%x, item: %f\n",  errorID, item);

        // case8: cholesky
        MATRIX* Ch = creat_matrix(3, 3, &errorID, &S);
        // REAL ch[3 * 3] = {4, -1, 2, -1, 6, 0, 2, 0, 5};
        REAL ch[3 * 3] = {1, 0, 1, 0, 2, 0, 1, 0, 3};
        set_matrix_by_array(Ch, ch, 9);

        INDEX flag = 0;
        errorID = matrix_cholesky_factor_upper(Ch, C, &flag);
        printf("errorID: 0x%x, flag: %d\n", errorID, flag);
        print_matrix(C, "Cholesky upper");

#if 0
        m = creat_multiple_matrices(3, 3, 2, &errorID, &S);
        m[0].p = a;
        m[1].p = b;
#endif

        free_stack(&S);
    }

    int64_t tick_end = GetTickCount();

    printf("run %d times, cost tick: %lld\n", times, tick_end - tick_strat);

    return 0;
}
