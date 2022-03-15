/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_EULERANGLE3D_H
 #define CXX_EULERANGLE3D_H

/*---------------------------------------------------------------------------*/
// Include files

/*---------------------------------------------------------------------------*/
// Class define

/*
 * Euler angle in 3D (x, y, z) class
 * The unit of x, y, z are all angle.
 */
class EulerAngle3D
{
public:

    // Memebers for euler angle in 3D axis
    double x;
    double y;
    double z;

    // Constructor and destructor
    EulerAngle3D(double _x, double _y, double _z);
    EulerAngle3D(const EulerAngle3D& v);
    virtual ~EulerAngle3D();

    // Calculate functions
    static double Dot(const EulerAngle3D& lhs, const EulerAngle3D& rhs);
    static EulerAngle3D Cross(const EulerAngle3D& lhs, const EulerAngle3D& rhs);

    // Overloaded operator
    EulerAngle3D operator+(const EulerAngle3D& v);
    EulerAngle3D operator*(double s);
    friend EulerAngle3D operator*(const EulerAngle3D& v, double s);

};

/*---------------------------------------------------------------------------*/
#endif  // CXX_EULERANGLE3D_H
/*EOF*/
