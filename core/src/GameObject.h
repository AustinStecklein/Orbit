#pragma once
#include <SFML/Graphics.hpp>
#include "Vector3D.h"
#include <vector>
class GameObject
{
    protected:
        double mass;
        OrbitMath::Vector3D position;
        OrbitMath::Vector3D velocity;


    public:
        virtual void draw(sf::RenderWindow *window, OrbitMath::Vector3D offset) = 0;
        virtual void setValues(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int colorMaping = 0) = 0;
        virtual void updatePosition(double t) = 0;
        virtual OrbitMath::Vector3D getPosition() = 0;
        virtual double getMass() = 0;
        virtual bool withInObject(OrbitMath::Vector3D point) = 0;
        virtual void collidedWith() = 0;
        virtual void applyAccelerationVector(OrbitMath::Vector3D a, double t) = 0;
        virtual OrbitMath::Vector3D getVelocity() = 0;
};