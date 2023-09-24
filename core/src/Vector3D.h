#pragma once
#include <cmath>
namespace OrbitMath
{
    class Vector3D
    {
        public:
            double x;
            double y;
            double z;

            Vector3D(): x(0), y(0), z(0) {}
            Vector3D(double x, double y, double z): x(x), y(y), z(z) {}

            /****************************************
            * Math functions start
            ****************************************/

            Vector3D Normalized()
            {
                double mag = this->magnitude();
                return Vector3D(this->x/mag, this->y/mag, this->z/mag);
            }

            double magnitude(){return std::sqrt((x * x) + (y * y) + (z * z));}

            double distance(const Vector3D & other)
            {
                double xCombined = other.x - this->x;
                double yCombined = other.y - this->y;
                double zCombined = other.z - this->z;
                return std::sqrt((xCombined * xCombined) + (yCombined * yCombined) + (zCombined * zCombined));
            }

            double distanceSquared(const Vector3D & other)
            {
                double xCombined = other.x - this->x;
                double yCombined = other.y - this->y;
                double zCombined = other.z - this->z;
                return (xCombined * xCombined) + (yCombined * yCombined) + (zCombined * zCombined);
            }

            double dot(const Vector3D & rhs) { return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z); }

            Vector3D cross(const Vector3D & other) { return Vector3D((this->y * other.z) - (this->z * other.y), (this->z * other.x) - (this->x * other.z), (this->x * other.y) - (this->y * other.x)); }
            /****************************************
            * Math functions end
            ****************************************/

            /****************************************
            * Operator overloads start
            ****************************************/
            Vector3D& operator+=(const Vector3D & rhs)&
            {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                return *this;
            }

            friend Vector3D operator+(Vector3D & lhs, const Vector3D & rhs)
            {
                return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
            }

            Vector3D& operator-=(const Vector3D & rhs)
            {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                return *this;
            }

            friend Vector3D operator-(Vector3D & lhs, const Vector3D & rhs) 
            {
                return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
            }

            Vector3D& operator*=(const double & rhs)
            {
                x *= rhs;
                y *= rhs;
                z *= rhs;
                return *this;
            }

            friend Vector3D operator*(Vector3D & lhs, const double & rhs) 
            {
                return Vector3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
            }

            friend Vector3D operator*(double & lhs, const Vector3D & rhs) { return Vector3D(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs); }

            Vector3D& operator/=(const double & rhs)
            {
                x /= rhs;
                y /= rhs;
                z /= rhs;
                return *this;
            }

            friend Vector3D operator/(Vector3D & lhs, const double & rhs) 
            {
                return Vector3D(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
            }

            friend Vector3D operator/(double & lhs, const Vector3D & rhs) { return Vector3D(rhs.x / lhs, rhs.y / lhs, rhs.z / lhs); }

            friend bool operator==(const Vector3D& lhs, const Vector3D& rhs) {return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);}
            friend bool operator!=(const Vector3D& lhs, const Vector3D& rhs) { return !(lhs == rhs);}
            
            void operator=(const Vector3D &rhs)
            {
                x = rhs.x;
                y = rhs.y;
                z = rhs.z;
            }

            operator sf::Vector3f() const { return sf::Vector3f(x, y, x); }
            /****************************************
            * Operator overloads end
            ****************************************/
    };

}