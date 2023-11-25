#pragma once
#inlcude "Vector3D.h"
#include <string>
struct futurePoint
{
    OrbitMath::Vector3D position;
    OrbitMath::Vector3D veloctiy;
    double timestamp;
    std::string currentMainBody;
};