/*******************************************************************************
*     File Name :                        inl_matrix_c.c
*     Create Date :                      2022/3/11
*     Abstract Description :             矩阵运算库源文件
*******************************************************************************/

/*******************************************************************************
* (1)Debug Switch Section
*******************************************************************************/


/*******************************************************************************
* (2)Include File Section
*******************************************************************************/
#include "inl_matrix.h"


/*******************************************************************************
* (3)Macro Define Section
*******************************************************************************/


/*******************************************************************************
* (4)Struct(Data Types) Define Section
*******************************************************************************/


/*******************************************************************************
* (5)Prototype Declare Section
*******************************************************************************/


/*******************************************************************************
* (6)Global Variable Declare Section
*******************************************************************************/


/*******************************************************************************
* (7)File Static Variable Define Section
*******************************************************************************/


/*******************************************************************************
* (8)Function Define Section
*******************************************************************************/

/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_add(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
    INDEX i = 0, j = 0;
    INTEGER rows = 0, columns = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
        || A->columns != B->columns || A->columns != C->columns || B->columns != C->columns) {
        errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
        return errorID;
    }

    rows = A->rows;
    columns = A->columns;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            C->p[i * columns + j] = A->p[i * columns + j] + B->p[i * columns + j];
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
    INDEX i = 0, j = 0;
    INTEGER rows = 0, columns = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
        || A->columns != B->columns || A->columns != C->columns || B->columns != C->columns) {
        errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
        return errorID;
    }

    rows = A->rows;
    columns = A->columns;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            C->p[i * columns + j] = A->p[i * columns + j] - B->p[i * columns + j];
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
    INDEX i = 0, j = 0, k = 0;
    REAL sum = 0.0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns) {
        errorID = _ERROR_MATRIX_MULTIPLICATION;
        return errorID;
    }

    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            sum = 0.0;
            for (k = 0; k < A->columns; k++) {
                sum += A->p[i * A->columns + k] * B->p[k * B->columns + j];
            }

            C->p[i * B->columns + j] = sum;
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_num_multiplication
Description: 矩阵乘法B = num * A
Input: 实数num,矩阵A
Output: 矩阵B
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_num_multiplication(_IN REAL num, _IN MATRIX* A, _OUT MATRIX* B)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    // Check input
    if (A == NULL || B == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != B->rows || A->columns != B->columns) {
        errorID = _ERROR_MATRIX_MULTIPLICATION;
        return errorID;
    }

    // Calculation
    for (i = 0; i < B->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            *(B->p + i * B->columns + j) = *(A->p + i * A->columns + j) * num;
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN MATRIX* A, _OUT MATRIX* invA)
{
    INDEX i = 0;
    INTEGER n = 0;
    MATRIX* ATemp = NULL;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    STACKS S;

    if (A == NULL || invA == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    init_stack(&S);

    n = A->rows;
    ATemp = creat_matrix(n, n, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR) goto EXIT;

    memcpy(ATemp->p, A->p, n * n * sizeof(REAL));
    memset(invA->p, 0, n * n * sizeof(REAL));
    for (i = 0; i < n; i++) {
        invA->p[i * n + i] = 1.0;
    }

    errorID = solve_matrix_equation_by_lup_decomposition(ATemp, invA);

EXIT:
    free_stack(&S);
    return errorID;
}


/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN MATRIX* A, _OUT MATRIX* transposeA)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || transposeA == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != transposeA->columns || A->columns != transposeA->rows) {
        errorID = _ERROR_MATRIX_TRANSPOSE_FAILED;
        return errorID;
    }

    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            transposeA->p[j * A->rows + i] = A->p[i * A->columns + j];
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_trace(_IN MATRIX* A, _OUT REAL *trace)
{
    INDEX i = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || trace == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    *trace = 0.0;
    for (i = 0; i < A->rows; i++) {
        *trace += A->p[i * A->columns + i];
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_norm
Description: 矩阵的Frobenius-范数
Input: 矩阵A
Output: 矩阵A的Frobenius-范数
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_norm(_IN MATRIX* A, _OUT REAL* norm)
{
    INDEX i = 0, j = 0;
    MATRIX* AT = NULL, *ATA = NULL;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    STACKS S;
    REAL sum = 0.0;
    INTEGER found_tr = 0;

    if (A == NULL || norm == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    // Calc Frobenius-norm
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            sum += A->p[i * A->columns + j] * A->p[i * A->columns + j];
        }
    }

    *norm = sqrt(sum);

    return errorID;
}

/**********************************************************************************************
Function: lup_decomposition
Description: n行n列矩阵LUP分解PA = L * U
Input: n行n列矩阵A
Output: n行n列下三角矩阵L，n行n列上三角矩阵U，n行n列置换矩阵P
Input_Output: 无
Return: 错误号
参考：https://zhuanlan.zhihu.com/p/84210687
***********************************************************************************************/
ERROR_ID lup_decomposition(_IN MATRIX* A, _OUT MATRIX* L, _OUT MATRIX* U, _OUT MATRIX* P)
{
    INDEX i = 0, j = 0, k = 0, index = 0, s = 0, t = 0;
    INTEGER n = 0;
    REAL maxValue = 0.0, temp = 0.0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || L == NULL || U == NULL || P == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    n = A->rows;
    memcpy(U->p, A->p, n * n * sizeof(REAL));
    memset(L->p, 0, n * n * sizeof(REAL));
    memset(P->p, 0, n * n * sizeof(REAL));

    for (i = 0; i < n; i++) {
        L->p[i * n + i] = 1.0;
        P->p[i * n + i] = 1.0;
    }

    for (j = 0; j < n - 1; j++) {
        //Select i(>= j) that maximizes | U(i, j) |
        index = -1;
        maxValue = 0.0;
        for (i = j; i < n; i++) {
            temp = fabs(U->p[i * n + j]);
            if (temp > maxValue) {
                maxValue = temp;
                index = i;
            }
        }

        if (index == -1) {
            continue;
        }

        //Interchange rows of U : U(j, j : n) < ->U(i, j : n)
        for (k = j; k < n; k++) {
            s = j * n + k;
            t = index * n + k;
            temp = U->p[s];
            U->p[s] = U->p[t];
            U->p[t] = temp;
        }

        //Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
        for (k = 0; k < j; k++) {
            s = j * n + k;
            t = index * n + k;
            temp = L->p[s];
            L->p[s] = L->p[t];
            L->p[t] = temp;
        }

        //Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n)
        for (k = 0; k < n; k++) {
            s = j * n + k;
            t = index * n + k;
            temp = P->p[s];
            P->p[s] = P->p[t];
            P->p[t] = temp;
        }

        for (i = j + 1; i < n; i++) {
            s = i * n + j;
            L->p[s] = U->p[s] / U->p[j * n + j];
            for (k = j; k < n; k++) {
                U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
            }
        }
    }

    return errorID;
}


/**********************************************************************************************
Function: matrix_cholesky_factor_upper
Description: n行n列矩阵Cholesky分解A = R'*R
Input: n行n列矩阵A
Output: 将对称正定矩阵 A 分解成满足 A = R'*R 的上三角 R;
如果 flag = 0，则输入矩阵是对称正定矩阵，分解成功。
如果 flag 不为零，则输入矩阵不是对称正定矩阵，flag 为整数，表示分解失败的主元位置的索引。
Input_Output: 无
Return: 错误号
参考：武汉大学github分享代码
***********************************************************************************************/
ERROR_ID matrix_cholesky_factor_upper(_IN MATRIX* A, _OUT MATRIX *R, _OUT INTEGER *flag)
{
    INDEX n = 0, i = 0, j = 0, k = 0;
    REAL sum2 = 0.0;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    MATRIX* L = NULL;
    STACKS S;

    // check input
    if (A == NULL || R == NULL || flag == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    if (A->rows != R->rows
        || A->columns != R->columns) {
        errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
        return errorID;
    }

    // init output
    *flag = 0;

    init_stack(&S);

    L = creat_matrix(R->rows, R->columns, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR) {
        goto EXIT;
    }

    n = A->rows;
    memcpy(L->p, A->p, n * n * sizeof(REAL));

    for (j = 0; j < n; j++) {
        for (i = 0; i < j; i++) {
            L->p[j + i * n] = 0.0;
        }

        for (i = j; i < n; i++) {
            sum2 = L->p[i+j*n];

            for (k = 0; k < j; k++) {
                sum2 = sum2 - L->p[k + j * n] * L->p[k + i * n];
            }

            if (i == j) {
                if (sum2 <= 0.0) {
                    *flag = 1;
                    errorID = _ERROR_CHOLESKY_DECOMPOSITION_FAILED;
                    goto EXIT;
                }

                L->p[j + i * n] = sqrt(sum2);
            }
            else {
                if (L->p[j + j * n] != 0.0) {
                    L->p[j + i * n] = sum2 / L->p[j + j * n];
                }
                else {
                    L->p[j + i * n] = 0.0;
                }
            }
        }
    }

    // Need transpose from L to R
    errorID = matrix_transpose(L, R);

EXIT:
    free_stack(&S);

    return errorID;
}


/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
***********************************************************************************************/
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN MATRIX* A, _IN_OUT MATRIX* B)
{
    INDEX i = 0, j = 0, k = 0, index = 0, s = 0, t = 0;
    INTEGER n = 0, m = 0;
    REAL sum = 0.0, maxValue = 0.0, temp = 0.0;
    MATRIX* L = NULL, * U = NULL, * y = NULL;
    ERROR_ID errorID = _ERROR_NO_ERROR;
    STACKS S;

    if (A == NULL || B == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    init_stack(&S);

    n = A->rows;
    m = B->columns;

    L = creat_matrix(n, n, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR) goto EXIT;

    U = creat_matrix(n, n, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR) goto EXIT;

    y = creat_matrix(n, m, &errorID, &S);
    if (errorID != _ERROR_NO_ERROR) goto EXIT;

    memcpy(U->p, A->p, n * n * sizeof(REAL));
    memset(L->p, 0, n * n * sizeof(REAL));
    for (i = 0; i < n; i++) {
        L->p[i * n + i] = 1.0;
    }

    for (j = 0; j < n - 1; j++) {
        //Select i(>= j) that maximizes | U(i, j) |
        index = -1;
        maxValue = 0.0;
        for (i = j; i < n; i++) {
            temp = fabs(U->p[i * n + j]);
            if (temp > maxValue) {
                maxValue = temp;
                index = i;
            }
        }

        if (index == -1) {
            continue;
        }

        //Interchange rows of U : U(j, j : n) < ->U(i, j : n)
        for (k = j; k < n; k++) {
            s = j * n + k;
            t = index * n + k;
            temp = U->p[s];
            U->p[s] = U->p[t];
            U->p[t] = temp;
        }

        //Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
        for (k = 0; k < j; k++) {
            s = j * n + k;
            t = index * n + k;
            temp = L->p[s];
            L->p[s] = L->p[t];
            L->p[t] = temp;
        }

        //Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n), C = P * B，等价于对B交换行
        for (k = 0; k < m; k++) {
            s = j * m + k;
            t = index * m + k;
            temp = B->p[s];
            B->p[s] = B->p[t];
            B->p[t] = temp;
        }

        for (i = j + 1; i < n; i++) {
            s = i * n + j;
            L->p[s] = U->p[s] / U->p[j * n + j];
            for (k = j; k < n; k++)
            {
                U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (fabs(U->p[i * n + i]) < 1.0e-20) {
            errorID = _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS;
            goto EXIT;
        }
    }

    //L * y = C
    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            sum = 0.0;
            for (k = 0; k < i; k++) {
                sum = sum + L->p[i * n + k] * y->p[k * m + j];
            }
            y->p[i * m + j] = B->p[i * m + j] - sum;
        }
    }

    //U * x = y
    for (j = 0; j < m; j++) {
        for (i = n - 1; i >= 0; i--) {
            sum = 0.0;
            for (k = i + 1; k < n; k++) {
                sum += U->p[i * n + k] * B->p[k * m + j];
            }
            B->p[i * m + j] = (y->p[i * m + j] - sum) / U->p[i * n + i];
        }
    }

EXIT:
    free_stack(&S);
    return errorID;
}

/* EOF */
