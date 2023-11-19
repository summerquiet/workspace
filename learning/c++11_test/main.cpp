/*
 *
 */

/*---------------------------------------------------------------------------*/
// Include files
#include <string>
// #include "test_instance.h"

#include <iostream>
#include <Eigen/Core>

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
int main()
{
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Random();                             //生成一个3*3的随机矩阵
    std::cout << "random matrix: \n"<< matrix_33 << std::endl;
    std::cout << "transpose : \n"<< matrix_33.transpose() << std::endl;  //转置
    std::cout << "sum :" << matrix_33.sum() << std::endl;                //求和
    std::cout << "trace : "<< matrix_33.trace() << std::endl;            //求迹
    std::cout << "time 10: \n"<< 10 * matrix_33 << std::endl;            //数乘
    std::cout << "inverse : \n"<< matrix_33.inverse() << std::endl;      //求逆
    // std::cout << "det : \n"<< matrix_33.determinant() << std::endl;      //求行列式
}
