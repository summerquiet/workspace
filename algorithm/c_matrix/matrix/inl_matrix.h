/*******************************************************************************
*     File Name :                        inl_matrix.h
*     Create Date :                      2022/3/11
*     Abstract Description :             矩阵运算库头文件
*******************************************************************************/

#ifndef  C_INL_MATRIX_H
#define  C_INL_MATRIX_H

/*******************************************************************************
* (1)Debug Switch Section
*******************************************************************************/


/*******************************************************************************
* (2)Include File Section
*******************************************************************************/

#include "inl_matrix_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* (3)Macro Define Section
*******************************************************************************/


/*******************************************************************************
* (4)Struct(Data Types) Define Section
*******************************************************************************/


/*******************************************************************************
* (5)Prototype Declare Section
*******************************************************************************/

// Implement in inl_matrix.c
void print_matrix(const MATRIX* a, STRING string);

/**********************************************************************************************
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S);


/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT STACKS* S);


/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S);


/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
***********************************************************************************************/
MATRIX* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT STACKS* S);


/**********************************************************************************************
Function: matrix_assign
Description: 矩阵赋值，将矩阵A赋值给矩阵B
Input: 矩阵A
Output：矩阵B
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_assign(_IN const MATRIX* A, _OUT MATRIX* B);


/**********************************************************************************************
Function: set_matrix_by_array
Description: 使用array对matrix赋值
Input: 赋值用array，赋值用array count
Input_Output: 矩阵matrix
Return: 错误号
***********************************************************************************************/
ERROR_ID set_matrix_by_array(_IN_OUT MATRIX* matrix, _IN const REAL array[], _IN INDEX array_count);


/**********************************************************************************************
Function: get_matrix_item
Description: 通过输入的行和列获取矩阵中的某个元素
Input: 矩阵matrix，矩阵的行row，矩阵的列column
Output：矩阵中的某个元素
Return: 错误号
***********************************************************************************************/
ERROR_ID get_matrix_item(_IN const MATRIX* matrix, _IN INDEX row, _IN INDEX column, _OUT REAL* value);

/**********************************************************************************************
Function: get_matrix_items
Description: 获取矩阵中的所有元素
Input: 矩阵matrix，矩阵的行row，矩阵的列column
Output：矩阵中的所有元素
Return: 错误号
***********************************************************************************************/
ERROR_ID get_matrix_items(_IN const MATRIX* matrix, _IN_OUT REAL array[], _IN INDEX array_count);


// Implement in inl_matrix_calc_c.c or inl_matrix_calc_eigen.cpp
/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_add(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX *C);


/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX* C);


/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN const MATRIX* A, _IN const MATRIX* B, _OUT MATRIX* C);


/**********************************************************************************************
Function: matrix_num_multiplication
Description: 矩阵乘法B = num * A
Input: 实数num,矩阵A
Output: 矩阵B
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_num_multiplication(_IN REAL num, _IN const MATRIX* A, _OUT MATRIX* B);


/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN const MATRIX* A, _OUT MATRIX* invA);


/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN const MATRIX* A, _OUT MATRIX* transposeA);


/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_trace(_IN const MATRIX* A, _OUT REAL* trace);


/**********************************************************************************************
Function: matrix_norm
Description: 矩阵的Frobenius-范数
Input: 矩阵A
Output: 矩阵A的Frobenius-范数
Input_Output: 无
Return: 错误号
***********************************************************************************************/
ERROR_ID matrix_norm(_IN const MATRIX* A, _OUT REAL* norm);


/**********************************************************************************************
Function: lup_decomposition
Description: n行n列矩阵LUP分解PA = L * U
Input: n行n列矩阵A
Output: n行n列下三角矩阵L，n行n列上三角矩阵U，n行n列置换矩阵P
Input_Output: 无
Return: 错误号
参考：https://zhuanlan.zhihu.com/p/84210687
***********************************************************************************************/
ERROR_ID lup_decomposition(_IN const MATRIX* A, _OUT MATRIX* L, _OUT MATRIX* U, _OUT MATRIX* P);


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
ERROR_ID matrix_cholesky_factor_upper(_IN const MATRIX* A, _OUT MATRIX *R, _OUT INTEGER *flag);


/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
***********************************************************************************************/
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN const MATRIX* A, _IN_OUT MATRIX* B);

#ifdef __cplusplus
}
#endif

#endif  // C_INL_MATRIX_H

/* EOF */
