/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files

#include <stdio.h>

#ifndef CXX_QUATERNION_H
#   include "Quaternion.h"
#endif

/*---------------------------------------------------------------------------*/
// Declear
void QuaternionTest(void);

/*---------------------------------------------------------------------------*/
// Main
int main(int argc, char** argv)
{
    // Run test
    QuaternionTest();

    // Return
    return 1;
}

/*---------------------------------------------------------------------------*/
void QuaternionTest()
{
    static const double PI = 3.1415926;
    static const double Rad2Deg = 180.0 / PI;
    static const double Deg2Rad = PI / 180.0;

    printf("%f\n", Rad2Deg * PI * 0.25);
    printf("%f\n", Deg2Rad * 45);

    // a is (0, 0, 0)
    Quaternion a = Quaternion::identity;
    EulerAngle3D aEulerAngle = a.EulerAngle();
    printf("a: (%f, %f, %f, %f), euler: (%f, %f, %f)\n", 
        a.x, a.y, a.z, a.w,
        aEulerAngle.x, aEulerAngle.y, aEulerAngle.z);

    // b is (90, 0, 0)
    EulerAngle3D bEu(0, 90, 0);
    Quaternion b(bEu);
    EulerAngle3D bEulerAngle = b.EulerAngle();
    printf("b: (%f, %f, %f, %f), euler: (%f, %f, %f)\n", 
        b.x, b.y, b.z, b.w,
        bEulerAngle.x, bEulerAngle.y, bEulerAngle.z);
    
    // Angle between a and b
    printf("Angle(a, b): %f\n", Quaternion::Angle(a, b));

    // c slerp from a to b with 0.5 (45, 0, 0)
    Quaternion c = Quaternion::Slerp(a, b, 0.5);
    EulerAngle3D cEulerAngle = c.EulerAngle();
    printf("c: (%f, %f, %f, %f), euler: (%f, %f, %f)\n", 
        c.x, c.y, c.z, c.w,
        cEulerAngle.x, cEulerAngle.y, cEulerAngle.z);

    // Angle between a and c
    printf("Angle(a, c): %f\n", Quaternion::Angle(a, c));

    // d is b * c (135, 0, 0)
    Quaternion d = b * c;
    EulerAngle3D dEulerAngle = d.EulerAngle();
    printf("d: (%f, %f, %f, %f), euler: (%f, %f, %f)\n", 
        d.x, d.y, d.z, d.w,
        dEulerAngle.x, dEulerAngle.y, dEulerAngle.z);

    // Angle between a and d
    printf("Angle(a, d): %f\n", Quaternion::Angle(a, d));

    // c * pos
    Vector3D pos(1, 2, 3);
    Vector3D cMPos = c * pos;
    printf("c * (1, 2, 3): (%f, %f, %f)\n",
        cMPos.x, cMPos.y, cMPos.z);
}  

/*---------------------------------------------------------------------------*/
 /*EOF*/
