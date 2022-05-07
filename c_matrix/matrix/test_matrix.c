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

        C = creat_matrix(3, 3, &errorID, &S);
#if 0
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

        INTEGER flag = 0;
        errorID = matrix_cholesky_factor_upper(Ch, C, &flag);
        printf("errorID: 0x%x, flag: %d\n", errorID, flag);
        print_matrix(C, "Cholesky upper");

        // case9 assign
        errorID = matrix_assign(A, C);
        print_matrix(C, "C");
#endif
#if 1
        // case10 chol
        REAL rhpht[6 * 6] = {
#if 0
            1.4437152094,  0.0003072904,  0.0000527303,  0.0149401767,  0.0006304482,  0.0001221742,
            0.0003072904,  1.2421761409,  -0.0000842451,  0.0009729321,  0.0133628106,  -0.0001612021,
            0.0000527303,  2.0648847549,  1.0012674081,  0.0005338688,  -0.0004680384,  0.0015566292,
            0.0149401767,  0.0009729321,  0.0154178688,  0.0203986677,  0.0011321009,  0.0008395179,
            0.0006304482,  0.0133628106,  -0.0004680384,  0.0160161009,  0.0181273751,  -0.0007378654,
            0.0001221742,  -0.0001612021,  0.0015566292,  0.0008395179,  0.0141461346,  0.0046064354

            0.7395531753,  0.0093663630,  0.0113922195,  0.0106397034,  0.0158147590,  0.0030785418,
            0.0205576982,  0.4031221462,  -0.0103169234,  0.0263950748,  -0.0046372129,  -0.0062922805,
            -0.0212013781,  3.7190073110,  -0.0006863888,  -0.0380166843,  0.0010009256,  0.0086211116,
            -0.0053321527,  0.0187907746,  0.0152459558,  0.0219845745,  0.0316161984,  0.0052984598,
            0.0300650137,  -0.0098611574,  -0.0143964763,  0.0669610736,  0.0049181255,  -0.0083260570,
            -0.0175934100,  0.0095275364,  0.0001756399,  -0.0349307117,  0.0146662935,  0.0139015615
#else
            1, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0
#endif
            };

        MATRIX* RHPHt = creat_zero_matrix(6, 6, &errorID, &S);
        set_matrix_by_array(RHPHt, rhpht, 6 * 6);
        print_matrix(RHPHt, "RHPHt");
        // [U, ndf] = chol(RHPHt);
        MATRIX* U = creat_zero_matrix(6, 6, &errorID, &S);

        errorID = matrix_inverse(RHPHt, U);
        printf("errorID[%X]\n", errorID);
        print_matrix(U, "inverse");
#endif
        free_stack(&S);
    }

    int64_t tick_end = GetTickCount();

    printf("run %d times, cost tick: %lld\n", times, tick_end - tick_strat);

    return 0;
}
