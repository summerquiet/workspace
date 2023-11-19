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
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_add(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX* C)
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
ERROR_ID matrix_subtraction(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX* C)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
        || A->columns != B->columns || A->columns != C->columns || B->columns != C->columns) {
        INLLOGE("CPP matrix_subtraction error A[%d*%d] B[%d*%d] C[%d*%d]\n", A->rows, A->columns, B->rows, B->columns, C->rows, C->columns);
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
ERROR_ID matrix_multiplication(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX* C)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || B == NULL || C == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns) {
        INLLOGE("CPP matrix_multiplication error A[%d*%d] B[%d*%d] C[%d*%d]\n", A->rows, A->columns, B->rows, B->columns, C->rows, C->columns);
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
Function: matrix_num_multiplication
Description: 矩阵乘法B = num * A
Input: 实数num,矩阵A
Output: 矩阵B
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_num_multiplication(_IN REAL num, _IN const MATRIX* A, _OUT MATRIX* B)
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

    // Convert A to Eigen Matrix
    Eigen::MatrixXd em_A(A->rows, A->columns);
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->columns; j++) {
            em_A(i, j) = *(A->p + i * A->columns + j);
        }
    }

    // Calculation
    em_A *= num;

    // Convert Eigen Matrix to output
    for (i = 0; i < B->rows; i++) {
        for (j = 0; j < B->columns; j++) {
            *(B->p + i * B->columns + j) = em_A(i, j);
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
ERROR_ID matrix_inverse(_IN const MATRIX* A, _OUT MATRIX* invA)
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

    // Check is invertible
    Eigen::FullPivLU<Eigen::MatrixXd> lu(em_A);
    if (!lu.isInvertible()) {
        errorID = _ERROR_MATRIX_INVERSE_FAILED;
        return errorID;
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
ERROR_ID matrix_transpose(_IN const MATRIX* A, _OUT MATRIX* transposeA)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || transposeA == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != transposeA->columns || A->columns != transposeA->rows) {
        INLLOGE("matrix_transpose [%d*%d]=[%d*%d]\n", A->rows, A->columns, transposeA->rows, transposeA->columns);
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
ERROR_ID matrix_trace(_IN const MATRIX* A, _OUT REAL *trace)
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
Description: 矩阵的Frobenius-范数
Input: 矩阵A
Output: 矩阵A的Frobenius-范数
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_norm(_IN const MATRIX* A, _OUT REAL* norm)
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
ERROR_ID lup_decomposition(_IN const MATRIX* A, _OUT MATRIX* L, _OUT MATRIX* U, _OUT MATRIX* P)
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
Function: matrix_cholesky_factor_upper
Description: n行n列矩阵Cholesky分解A = R'*R
Input: n行n列矩阵A
Output: 将对称正定矩阵 A 分解成满足 A = R'*R 的上三角 R;
如果 flag = 0，则输入矩阵是对称正定矩阵，分解成功。
如果 flag 不为零，则输入矩阵不是对称正定矩阵，flag 为整数，表示分解失败的主元位置的索引。
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_cholesky_factor_upper(_IN const MATRIX* A, _OUT MATRIX *R, _OUT INTEGER *flag)
{
    INDEX i = 0, j = 0;
    ERROR_ID errorID = _ERROR_NO_ERROR;

    if (A == NULL || R == NULL || flag == NULL) {
        errorID = _ERROR_INPUT_PARAMETERS_ERROR;
        return errorID;
    }

    if (A->rows != A->columns
        || R->rows != R->columns) {
        errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
        return errorID;
    }

    if (A->rows != R->rows
        || A->columns != R->columns) {
        errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
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
    Eigen::LLT<Eigen::MatrixXd> llt;
    llt.compute(em_A);
    if (llt.info() == Eigen::Success) {
        *flag = 0;

        // Convert Eigen Matrix to output
        Eigen::MatrixXd LT = llt.matrixU();
        for (i = 0; i < R->rows; i++) {
            for (j = 0; j < R->columns; j++) {
                *(R->p + i * R->columns + j) = LT(i, j);
            }
        }
    }
    else {
        *flag = 1;
        errorID = _ERROR_CHOLESKY_DECOMPOSITION_FAILED;
    }

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
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN const MATRIX* A, _IN_OUT MATRIX* B)
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
