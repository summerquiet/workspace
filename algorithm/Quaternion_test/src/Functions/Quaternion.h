/*
 * Head
 * Copyright ~
 */

 #ifndef CXX_QUATERNION_H
 #define CXX_QUATERNION_H

/*---------------------------------------------------------------------------*/
// Include files

#ifndef CXX_EULERANGLE3D_H
#   include "EulerAngle3D.h"
#endif
#ifndef CXX_VECTOR3D_H
#   include "Vector3D.h"
#endif

/*---------------------------------------------------------------------------*/
// Class define

/*
 * Quaternion class in (x, y, z, w)
 */
class Quaternion
{
public:

    // Members for quaternion
    double  x;
    double  y;
    double  z;
    double  w;

    // Constructor and destructor
    Quaternion(double _x, double _y, double _z, double _w);
    Quaternion(const Quaternion& q);
    Quaternion(const EulerAngle3D& eu);
    virtual ~Quaternion();

    // Set value
    void Set(double _x, double _y, double _z, double _w);
    void SetEulerAngle(const EulerAngle3D& eu);

    // Calculate functions
    static Quaternion identity;
    static double Dot(const Quaternion& lhs, const Quaternion& rhs);
    static Quaternion Lerp(const Quaternion& a, const Quaternion& b, double t);
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, double t);
    static double Angle(const Quaternion& lhs, const Quaternion& rhs);
  
    Quaternion Conjugate() const;
    Quaternion Inverse() const;
    EulerAngle3D EulerAngle() const;
  
    void operator+(const Quaternion &q);
    void operator-(const Quaternion &q);
    void operator*(double s);
    friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);
    friend Vector3D operator*(const Quaternion& q, const Vector3D& v);

};

/*---------------------------------------------------------------------------*/
#endif  // CXX_QUATERNION_H
/*EOF*/
