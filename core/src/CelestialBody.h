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
        std::vector<sf::Vertex> points;
        sf::Color orbitColor;
        bool collision;

    public:
        CelestialBody(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int colorMaping = 0) 
        {
            //set member variables
            this->velocity = velocity;
            this->position = position;
            this->mass = mass;
            this->radius = radius;
            collision = false;
            points.push_back(sf::Vertex(sf::Vector2f(position.x, position.y)));    
            
            //build the circle shape to draw
            circle = new sf::CircleShape(radius);
            circle->setOutlineThickness(1.f);
            circle->setOutlineColor(sf::Color::White);
            circle->setFillColor(sf::Color::Transparent);
            circle->setOrigin(((sf::CircleShape*)circle)->getRadius(), ((sf::CircleShape*)circle)->getRadius());
            circle->setPosition(position.x, position.y);

            switch (colorMaping)
            {
                case 0:
                    orbitColor = sf::Color::White;
                    break;
                case 1:
                    orbitColor = sf::Color::Red;
                    break;
                case 2:
                    orbitColor = sf::Color::Blue;
                    break;
                case 3:
                    orbitColor = sf::Color::Green;
                    break;
                case 4:
                    orbitColor = sf::Color::Magenta;
                    break;
                case 5:
                    orbitColor = sf::Color::Cyan;
                    break;
                default:
                    orbitColor = sf::Color::White;
                    break;
            }
        
        }

        void draw(sf::RenderWindow *window)
        {
            window->draw(*circle);
        }

        void updatePosition(double t, const std::vector<GameObject*> &objects, double scaleFactor, bool pause)
        {
            if(collision)
                return;
            OrbitMath::Vector3D a;
            OrbitMath::Vector3D lastPointVector = this->futurePoint();
            
            for (auto it = objects.begin(); it != objects.end(); it++)
            {
                if((CelestialBody*)*it != this)
                {
                    if((*it)->withInObject(lastPointVector))
                    {
                        collision = true;
                        (*it)->collidedWith();
                        break;
                    }
                    OrbitMath::Vector3D otherBody = (*it)->futurePoint();
                    double distance2 = lastPointVector.distanceSquared(otherBody) * std::pow(scaleFactor, 2);
                    OrbitMath::Vector3D direction =  otherBody - lastPointVector;
                    direction = direction.Normalized();
                    a += direction * (((G * (*it)->getMass())/ distance2));
                }
            }
            if(!collision)
            {
                velocity += (a * t);
                futurePoints.push_back(lastPointVector + (velocity * t));  
                points.push_back(sf::Vertex(sf::Vector2f(lastPointVector.x + (velocity.x * t), lastPointVector.y + (velocity.y * t)), orbitColor));
                if(!pause)
                {
                    position =  *(futurePoints.begin());
                    futurePoints.erase(futurePoints.begin());
                }
            }
        }
        OrbitMath::Vector3D getPosition() { return position;}
        double getMass() {return mass;}
        double getRadius() {return radius;}

        bool withInObject(OrbitMath::Vector3D point)
        {
            int distance = std::sqrt(std::pow(point.x - position.x, 2)
            std::pow(point.y - position.y, 2));
            if ( distance <= radius)
                return true;
            else
                return false;
        }

        OrbitMath::Vector3D futurePoint()
        {
            if (futurePoints.size() != 0)
                return *(futurePoints.end() - 1);
            else
                return position;
        }

        std::vector<OrbitMath::Vector3D> getFuturePoints() {return futurePoints;}
        sf::Color getOrbitColor() {return orbitColor;}
        void collidedWith() {collision = true;}
};