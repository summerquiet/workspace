/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_VECTOR3D_H
 #define CXX_VECTOR3D_H

/*---------------------------------------------------------------------------*/
// Include files

/*---------------------------------------------------------------------------*/
// Class define

/*
 * Vector in 3D (x, y, z)
 */
class Vector3D
{
public:

    // Memebers for vector in 3D axis
    double x;
    double y;
    double z;

    // Constructor and destructor
    Vector3D(double _x, double _y, double _z);
    Vector3D(const Vector3D& v);
    virtual ~Vector3D();

    // Calculate functions
    static double Dot(const Vector3D& lhs, const Vector3D& rhs);
    static Vector3D Cross(const Vector3D& lhs, const Vector3D& rhs);

    // Overloaded operator
    Vector3D operator+(const Vector3D& v);
    Vector3D operator*(double s);
    friend Vector3D operator*(const Vector3D& v, double s);

};

/*---------------------------------------------------------------------------*/
#endif  // CXX_VECTOR3D_H
/*EOF*/
