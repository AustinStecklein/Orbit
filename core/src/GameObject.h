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
        std::vector<OrbitMath::Vector3D> futurePoints;

    public:
        virtual void draw(sf::RenderWindow *window) = 0;
        virtual void updatePosition(double t, const std::vector<GameObject*> &objects, double scaleFactor, bool pause) = 0;
        virtual OrbitMath::Vector3D getPosition() = 0;
        virtual double getMass() = 0;
        virtual bool withInObject(OrbitMath::Vector3D point) = 0;
        virtual void collidedWith() = 0;
        virtual OrbitMath::Vector3D futurePoint() = 0;
        virtual std::vector<OrbitMath::Vector3D> getFuturePoints() = 0;
};