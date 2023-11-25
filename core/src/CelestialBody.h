#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>
#include <vector>
#define G 6.6743E-11


class CelestialBody: public GameObject
{
    private:
        double radius;
        sf::Shape *circle;
        bool collision;

    public:
        CelestialBody()
        {

        }
        void setValues(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int colorMaping = 0)
        {
           //set member variables
            this->velocity = velocity;
            this->position = position;
            this->mass = mass;
            this->radius = radius;
            collision = false;
            //std::cout << "1 velocityx: " << velocity.x << " Y: "<< velocity.y << " Z:" << velocity.z << std::endl;
            //build the circle shape to draw
            circle = new sf::CircleShape(radius);
            circle->setOutlineThickness(1.f);
            circle->setOutlineColor(sf::Color::White);
            circle->setFillColor(sf::Color::Transparent);
            circle->setOrigin(((sf::CircleShape*)circle)->getRadius(), ((sf::CircleShape*)circle)->getRadius());
            circle->setPosition(position.x, position.y); 
        }
        CelestialBody(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int colorMaping = 0) 
        {
            //set member variables
            this->velocity = velocity;
            this->position = position;
            this->mass = mass;
            this->radius = radius;
            collision = false;
            //std::cout << "1 velocityx: " << velocity.x << " Y: "<< velocity.y << " Z:" << velocity.z << std::endl;
            //build the circle shape to draw
            circle = new sf::CircleShape(radius);
            circle->setOutlineThickness(1.f);
            circle->setOutlineColor(sf::Color::White);
            circle->setFillColor(sf::Color::Transparent);
            circle->setOrigin(((sf::CircleShape*)circle)->getRadius(), ((sf::CircleShape*)circle)->getRadius());
            circle->setPosition(position.x, position.y);
        
        }

        void draw(sf::RenderWindow *window, OrbitMath::Vector3D offset)
        {
            //circle->setPosition(position.x + offset.x, position.y + offset.y);
            sf::Vertex point(sf::Vector2f(position.x, position.y), sf::Color::White);
            window->draw(&point, 1, sf::Points);
        }

        OrbitMath::Vector3D getPosition() { return position;}
        OrbitMath::Vector3D getVelocity() { return velocity;}
        double getMass() {return mass;}
        double getRadius() {return radius;}

        bool withInObject(OrbitMath::Vector3D point)
        {
            int distance = std::sqrt(std::pow(point.x - position.x, 2) + std::pow(point.y - position.y, 2));
            if ( distance <= radius)
                return true;
            else
                return false;
        }

        void collidedWith() {collision = true;}

        void updatePosition(double t) 
        { 
            position =  position + (velocity * t);
            //std::cout << "Fpoint X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
        }
        void applyAccelerationVector(OrbitMath::Vector3D a, double t) { velocity = velocity + (a * t); }
};