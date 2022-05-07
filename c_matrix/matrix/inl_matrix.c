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
#define INLLOGE printf

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

VOID print_matrix(const MATRIX* a, STRING string)
{
    INDEX i = 0, j = 0;
    printf("matrix %s:", string);
    printf("\n");
    for (i = 0; i < a->rows; i++) {
        for (j = 0; j < a->columns; j++) {
            printf("%.10f  ", a->p[i * a->columns + j]);
        }

        printf("\n");
    }

    printf("\n");
}

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
        INLLOGE("creat_matrix errorID error\n");
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (rows <= 0 || columns <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        INLLOGE("creat_matrix  error [%d][%d]\n", rows, columns);
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
        INLLOGE("creat_matrix par error\n");
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
        INLLOGE("creat_matrix matrix->p NULL\n");
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
        INLLOGE("creat_zero_matrix par error\n");
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (rows <= 0 || columns <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        INLLOGE("creat_zero_matrix error [%d][%d]\n", rows, columns);
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
        INLLOGE("creat_eye_matrix par error\n");
        return NULL;
    }

    *errorID = _ERROR_NO_ERROR;
    if (n <= 0 || S == NULL) {
        *errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        INLLOGE("creat_eye_matrix S == NULL error\n");
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
Function: matrix_assign
Description: 矩阵赋值，将矩阵A赋值给矩阵B
Input: 矩阵A
Output：矩阵B
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_assign(_IN const MATRIX* A, _OUT MATRIX* B)
{
    ERROR_ID errorID = _ERROR_NO_ERROR;

    // Check input
    if (A == NULL || B == NULL) {
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    if (A->rows != B->rows
        || A->columns != B->columns) {
        return _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
    }

    // Copy items from A 2 B
    memcpy(B->p, A->p, A->rows * A->columns * sizeof(REAL));

    return errorID;
}


/**********************************************************************************************
Function: set_matrix_by_array
Description: 使用array对matrix赋值
Input: 赋值用array，赋值用array count
Input_Output: 矩阵matrix
Return: 错误号
***********************************************************************************************/
ERROR_ID set_matrix_by_array(_IN_OUT MATRIX* matrix, _IN const REAL array[], _IN INDEX array_count)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (matrix == NULL || array == NULL) {
        INLLOGE("set_matrix_by_array matrix == NULL error\n");
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    if (array_count != matrix->rows * matrix->columns) {
        INLLOGE("set_matrix_by_array error[%d][%d]\n", matrix->rows, matrix->columns);
        return _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
    }

    // Copy data
    memcpy(matrix->p, array, array_count * sizeof(REAL));

    return errorID;
}


/**********************************************************************************************
Function: get_matrix_item
Description: 通过输入的行和列获取矩阵中的某个元素
Input: 矩阵matrix，矩阵的行row，矩阵的列colum
Output：矩阵中的某个元素
Return: 错误号
***********************************************************************************************/
ERROR_ID get_matrix_item(_IN const MATRIX* matrix, _IN INDEX row, _IN INDEX column, _OUT REAL* value)
{
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (matrix == NULL || value == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        INLLOGE("get_matrix_item matrix == NULL error\n");
        return errorID;
    }

    if (row >= matrix->rows || column >= matrix->columns) {
        INLLOGE("get_matrix_item matrix->rows [%d][%d] error\n", matrix->rows, matrix->columns);
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    // Get item
    *value = matrix->p[row * matrix->columns + column];

    return errorID;
}

/**********************************************************************************************
Function: get_matrix_items
Description: 获取矩阵中的所有元素
Input: 矩阵matrix
Output：矩阵中的所有元素
Return: 错误号
***********************************************************************************************/
ERROR_ID get_matrix_items(_IN const MATRIX* matrix, _IN_OUT REAL array[], _IN INDEX array_count)
{
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (matrix == NULL || array == NULL) {
        INLLOGE("get_matrix_items matrix == NULL error\n");
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    if (matrix->rows * matrix->columns < array_count) {
        INLLOGE("get_matrix_items matrix->rows [%d][%d] error\n", matrix->rows, matrix->columns);
        return _ERROR_INPUT_PARAMETERS_ERROR;
    }

    // Get items
    memcpy(array, matrix->p, array_count * sizeof(REAL));

    return errorID;
}

/* EOF */
