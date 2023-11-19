/*
 * Head
 * Copyright ~
 */

/*---------------------------------------------------------------------------*/
// Include files
#include <math.h>

#ifndef CXX_QUATERNION_H
#   include "Quaternion.h"
#endif

/*---------------------------------------------------------------------------*/
// Const values
static const double EPSILON = 1e-7;
static const double PI      = 3.1415926;
static const double Rad2Deg = 180.0 / PI;
static const double Deg2Rad = PI / 180.0;

/*---------------------------------------------------------------------------*/
// Static values

Quaternion Quaternion::identity(0, 0, 0, 1);

/*---------------------------------------------------------------------------*/
// Constructor
Quaternion::Quaternion(double _x, double _y, double _z, double _w)
{  
    double mag = _x * _x + _y * _y + _z * _z + _w * _w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}

/*---------------------------------------------------------------------------*/
// Copy constructor
Quaternion::Quaternion(const Quaternion& q)
: x(q.x)
, y(q.y)
, z(q.z)
, w(q.w)
{

}

/*---------------------------------------------------------------------------*/
// Constructor by euler angle
Quaternion::Quaternion(const EulerAngle3D& eu)
{
    SetEulerAngle(eu);
}

/*---------------------------------------------------------------------------*/
// Destructor
Quaternion::~Quaternion()  
{

}

/*---------------------------------------------------------------------------*/
// Set values
void Quaternion::Set(double _x, double _y, double _z, double _w)
{  
    x = _x;  
    y = _y;  
    z = _z;  
    w = _w;  
}  

/*---------------------------------------------------------------------------*/
// Set by euler angle
void Quaternion::SetEulerAngle(const EulerAngle3D& eu)
{
    double angle = eu.x * Deg2Rad * 0.5;
    double sinYaw = sin(angle);
    double cosYaw = cos(angle);

    angle = eu.y * Deg2Rad * 0.5;
    double sinPitch = sin(angle);
    double cosPitch = cos(angle);

    angle = eu.z * Deg2Rad * 0.5;
    double sinRoll = sin(angle);
    double cosRoll = cos(angle);

    double _y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    double _x = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
    double _z = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    double _w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

    double mag = _x * _x + _y * _y + _z * _z + _w * _w;
    x = _x / mag;
    y = _y / mag;
    z = _z / mag;
    w = _w / mag;
}

/*---------------------------------------------------------------------------*/
// Cos theta of two quaternion  
double Quaternion::Dot(const Quaternion& lhs, const Quaternion& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

/*---------------------------------------------------------------------------*/
// Lerp
Quaternion Quaternion::Lerp(const Quaternion &a, const Quaternion &b, double t)
{
    // Create a new quaternion decide by t rate
    return Quaternion((1 - t) * a.x + t * b.x,
        (1 - t) * a.y + t * b.y,
        (1 - t) * a.z + t * b.z,
        (1 - t) * a.w + t * b.w);
}

/*---------------------------------------------------------------------------*/
// Slerp
Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, double t)  
{  
    double cos_theta = Dot(a, b);
  
    // if B is on opposite hemisphere from A, use -B instead
    double sign = 0.0;
    if (cos_theta < 0.0) {

        cos_theta = -cos_theta;
        sign = -1.0;
    }  
    else {

        sign = 1.f;
    }
  
    double c1 = 0.0;
    double c2 = 0.0;
    if (cos_theta > 1.0 - EPSILON) {

        // if q2 is (within precision limits) the same as q1,
        // just linear interpolate between A and B.  
        c2 = t;  
        c1 = 1.0 - t;  
    }  
    else {

        //float theta = gFloat::ArcCosTable(cos_theta);
        // faster than table-based:
        //const float theta = myacos(cos_theta);
        double theta = acos(cos_theta);
        double sin_theta = sin(theta);
        double t_theta = t * theta;
        double inv_sin_theta = 1.0 / sin_theta;
        c2 = sin(t_theta) * inv_sin_theta;
        c1 = sin(theta - t_theta) * inv_sin_theta;
    }  
  
    c2 *= sign;
    // or c1 *= sign
    // just affects the overrall sign of the output

    // interpolate
    return Quaternion(a.x * c1 + b.x * c2,
        a.y * c1 + b.y * c2,
        a.z * c1 + b.z * c2,
        a.w * c1 + b.w * c2);  
}  
  
/*---------------------------------------------------------------------------*/
// Caluate angle
double Quaternion::Angle(const Quaternion& lhs, const Quaternion& rhs)  
{  
    double cos_theta = Dot(lhs, rhs);
  
    // if B is on opposite hemisphere from A, use -B instead
    if (cos_theta < 0.f) {

        cos_theta = -cos_theta;
    }

    double theta = acos(cos_theta);
    return 2.0 * Rad2Deg * theta;
}

/*---------------------------------------------------------------------------*/
// Conjugate
Quaternion Quaternion::Conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

/*---------------------------------------------------------------------------*/
// Inverse
Quaternion Quaternion::Inverse() const
{
    return Quaternion(-x, -y, -z, w);
}

/*---------------------------------------------------------------------------*/
// To euler angle
EulerAngle3D Quaternion::EulerAngle() const
{
    double yaw = atan2(2 * (w * x + z * y), 1 - 2 * (x * x + y * y));
    double tmp = 2 * (w * y - x * z);
    if (tmp >= 1.0) {
    
        tmp = 1.0;
    }
    else if (tmp <= -1.0) {

        tmp = -1.0;
    }
    double pitch = asin(tmp);
    double roll = atan2(2 * (w * z + x * y), 1 - 2 * (z * z + y * y));

    return EulerAngle3D(Rad2Deg * yaw, Rad2Deg * pitch, Rad2Deg * roll);
} 

/*---------------------------------------------------------------------------*/
// Operator + (Qp + Qq)
void Quaternion::operator+(const Quaternion& q)
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
}

/*---------------------------------------------------------------------------*/
// Operator - (Qp - Qq)
void Quaternion::operator-(const Quaternion& q)
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
}

/*---------------------------------------------------------------------------*/
// Operator * (Qp * Sq)
void Quaternion::operator*(double s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;
}

/*---------------------------------------------------------------------------*/
// Operator * (Qo = Qp * Qq)
Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
#if 1
    double w1 = lhs.w;
    double w2 = rhs.w;
    Vector3D v1(lhs.x, lhs.y, lhs.z);
    Vector3D v2(rhs.x, rhs.y, rhs.z);
    double w3 = w1 * w2 - Vector3D::Dot(v1, v2);
    Vector3D v3 = Vector3D::Cross(v1, v2) + v2 * w1 + v1 * w2;
    return Quaternion(v3.x, v3.y, v3.z, w3);
#else
    double w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    double x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
    double y = lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z;
    double z = lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x;
    return Quaternion(x, y, z, w);
#endif
}  
  
/*---------------------------------------------------------------------------*/
// Operator * (Vo = Qp * Vq)
Vector3D operator*(const Quaternion& q, const Vector3D& v)
{
    // Extract the vector part of the quaternion
    Vector3D u(q.x, q.y, q.z);

    // Extract the scalar part of the quaternion
    double s = q.w;

    // Do the math
    return u * 2.0 * Vector3D::Dot(u, v)
        + v * (s * s - Vector3D::Dot(u, u))
        + Vector3D::Cross(u, v) * 2.0 * s;
}

/*---------------------------------------------------------------------------*/
/*EOF*/
