#pragma once
#include <math.h>

struct vector3
{
    float x, y, z;

    vector3& operator +(vector3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3& operator -(vector3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vector3& operator *(float& other)
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    float dot(vector3& other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    vector3 cross(vector3& other)
    {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }

    float lengthSquared()
    {
        return x*x + y*y + z*z;
    }

    float length()
    {
        sqrt(lengthSquared());
    }
};

struct quat
{

};