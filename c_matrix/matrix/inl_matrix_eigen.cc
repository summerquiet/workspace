/*******************************************************************************
*     File Name :                        inl_matrix_eigen.cpp
*     Create Date :                      2022/3/11
*     Abstract Description :             matrix eigen implement
*******************************************************************************/

/*******************************************************************************
* (1)Debug Switch Section
*******************************************************************************/


/*******************************************************************************
* (2)Include File Section
*******************************************************************************/
#include "inl_matrix.h"
#include <Eigen/Dense>

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
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
    MATRIX* matrix = NULL;
    MATRIX_NODE* matrixNode = NULL;
    MATRIX_ELEMENT_NODE* matrixElementNode = NULL;

    if (errorID == NULL) {
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (rows <= 0 || columns <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return NULL;
    }

    matrix = (MATRIX*)malloc(sizeof(MATRIX));
    matrixNode = (MATRIX_NODE*)malloc(sizeof(MATRIX_NODE));
    matrixElementNode = (MATRIX_ELEMENT_NODE*)malloc(sizeof(MATRIX_ELEMENT_NODE));
    if (matrix == NULL || matrixNode == NULL || matrixElementNode == NULL) {
        free(matrix);
        matrix = NULL;
        free(matrixNode);
        matrixNode = NULL;
        free(matrixElementNode);
        matrixElementNode = NULL;

        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
        return NULL;
    }

    matrix->rows = rows;
    matrix->columns = columns;
    matrix->p = (REAL*)malloc(rows * columns * sizeof(REAL));  //确保matrix非空才能执行指针操作
    if (matrix->p == NULL) {
        free(matrix->p);
        matrix->p = NULL;
        free(matrix);
        matrix = NULL;
        free(matrixNode);
        matrixNode = NULL;
        free(matrixElementNode);
        matrixElementNode = NULL;

        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
        return NULL;
    }

    matrixNode->ptr = matrix;
    matrixNode->next = S->matrixNode;
    S->matrixNode = matrixNode;

    matrixElementNode->ptr = matrix->p;
    matrixElementNode->next = S->matrixElementNode;
    S->matrixElementNode = matrixElementNode;

    return matrix;
}


/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
    INDEX i = 0;
    MATRIX* matrix = NULL, *p = NULL;
    MATRIX_NODE* matrixNode = NULL;

    if (errorID == NULL) {
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (rows <= 0 || columns <= 0 || count <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return NULL;
    }

    matrix = (MATRIX*)malloc(count * sizeof(MATRIX));
    matrixNode = (MATRIX_NODE*)malloc(sizeof(MATRIX_NODE));
    if (matrix == NULL || matrixNode == NULL) {
        free(matrix);
        matrix = NULL;
        free(matrixNode);
        matrixNode = NULL;

        *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
        return NULL;
    }

    for (i = 0; i < count; i++) {
        p = creat_matrix(rows, columns, errorID, S);
        if (p == NULL) {
            free(matrix);
            matrix = NULL;
            free(matrixNode);
            matrixNode = NULL;

            *errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
            return NULL;
        }

        matrix[i] = *p;
    }

    matrixNode->ptr = matrix;
    matrixNode->next = S->matrixNode;
    S->matrixNode = matrixNode;

    return matrix;
}

/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
    MATRIX* matrix = NULL;

    if (errorID == NULL) {
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (rows <= 0 || columns <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return NULL;
    }

    matrix = creat_matrix(rows, columns, errorID, S);
    if (*errorID == _ERROR_NO_ERROR) {
        memset(matrix->p, 0, rows * columns * sizeof(REAL));
    }

    return matrix;
}


/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
    INDEX i = 0;
    MATRIX* matrix = NULL;

    if (errorID == NULL) {
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (n <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return NULL;
    }

    matrix = creat_matrix(n, n, errorID, S);
    if (*errorID == _ERROR_NO_ERROR) {
        memset(matrix->p, 0, n * n * sizeof(REAL));
        for (i = 0; i < n; i++) {
            matrix->p[i * n + i] = 1.0;
        }
    }

    return matrix;
}


/**********************************************************************************************
Function: set_matrix_by_array
Description: 使用array对matrix赋值
Input: 赋值用array，赋值用array count
Input_Output: 矩阵matrix
Return: 错误号
***********************************************************************************************/
ERROR_ID set_matrix_by_array(_IN_OUT MATRIX* matrix, _IN REAL array[], _IN INDEX array_count)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (matrix == NULL || array == NULL) {
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    if (array_count != matrix->rows * matrix->columns) {
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    // Copy data
    memcpy(matrix->p, array, array_count * sizeof(REAL));

    return errorID;
}


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

    // Convert A and B to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    Eigen::MatrixXd em_B(B->rows, B->columns);
    for (i = 0; i < B->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            em_B(i, j) = *(B->p + i * B->columns + j);
        }
    }

    // Calculation
    em_A += em_B;

    // Convert Eigen Matrix to output
    for (i = 0; i < C->rows; i++) {
        for (j = 0; j < C->columns; j++) {
            *(C->p + i * C->columns + j) = em_A(i, j);
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

    // Convert A and B to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    Eigen::MatrixXd em_B(B->rows, B->columns);
    for (i = 0; i < B->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            em_B(i, j) = *(B->p + i * B->columns + j);
        }
    }

    // Calculation
    em_A -= em_B;

    // Convert Eigen Matrix to output
    for (i = 0; i < C->rows; i++) {
        for (j = 0; j < C->columns; j++) {
            *(C->p + i * C->columns + j) = em_A(i, j);
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
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns) {
        errorID = _ERROR_MATRIX_MULTIPLICATION;
        return errorID;
    }

    // Convert A and B to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    Eigen::MatrixXd em_B(B->rows, B->columns);
    for (i = 0; i < B->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            em_B(i, j) = *(B->p + i * B->columns + j);
        }
    }

    // Calculation
    em_A *= em_B;

    // Convert Eigen Matrix to output
    for (i = 0; i < C->rows; i++) {
        for (j = 0; j < C->columns; j++) {
            *(C->p + i * C->columns + j) = em_A(i, j);
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
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || invA == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    // Convert A to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    // Calculation
    Eigen::MatrixXd em_B = em_A.inverse();

    // Convert Eigen Matrix to output
    for (i = 0; i < invA->rows; i++) {
        for (j = 0; j < invA->columns; j++) {
            *(invA->p + i * invA->columns + j) = em_B(i, j);
        }
    }

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

    // Convert A to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    // Calculation
    Eigen::MatrixXd em_B = em_A.transpose();

    // Convert Eigen Matrix to output
    for (i = 0; i < transposeA->rows; i++) {
        for (j = 0; j < transposeA->columns; j++) {
            *(transposeA->p + i * transposeA->columns + j) = em_B(i, j);
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
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || trace == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    // Convert A to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    // Calculation
    *trace = em_A.trace();

    return errorID;
}


/**********************************************************************************************
Function: matrix_norm
Description: 矩阵的2-范数
Input: 矩阵A
Output: 矩阵A的2-范数
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_norm(_IN MATRIX* A, _OUT REAL* norm)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || norm == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    // Convert A to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    // Calculation
    *norm = em_A.norm();

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

    // No need implement in Eigen version
    errorID = _ERROR_NO_IMPLEMENT;
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

    // No need implement in Eigen version
    errorID = _ERROR_NO_IMPLEMENT;
    return errorID;
}

/* EOF */
