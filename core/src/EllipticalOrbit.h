#pragma once
#include "EllipseShape.h"
#include <iostream>
#define PI 3.14159265358979323846
class EllipticalOrbit 
{
    public:
        EllipticalOrbit(const sf::Vector2f& radius)
        {
            primeFoci = new sf::CircleShape (3.f);
            subPrimeFoci = new sf::CircleShape (3.f);
    
            primeFoci->setFillColor(sf::Color::White);
            subPrimeFoci->setFillColor(sf::Color::White);

            primeFoci->setOrigin(primeFoci->getRadius(), primeFoci->getRadius());
            subPrimeFoci->setOrigin(subPrimeFoci->getRadius(), subPrimeFoci->getRadius());

            orbitPath = new EllipseShape(radius);
            orbitPath->setFillColor(sf::Color::Transparent);
            orbitPath->setOutlineColor(sf::Color::White);
            orbitPath->setOutlineThickness(1);
            orbitPath->setOrigin(orbitPath->getRadius().x, orbitPath->getRadius().y);
            updatePosition(sf::Vector2f(0, 0));
        }
        
        ~EllipticalOrbit()
        {
            if (orbitPath != nullptr)
                delete orbitPath;
            if (primeFoci != nullptr)
                delete primeFoci;
            if (subPrimeFoci != nullptr)
                delete subPrimeFoci;
        }

        void setPositionOrigin(const sf::Vector2f& newPosition) {updatePosition(newPosition);}
        
        //At some point change the second parameter to a direction vector
        //We do not want the simulator to know that the prime focus is forced on one side
        void setPositionFoci(const sf::Vector2f& newPosition)
        {
            sf::Vector2f adjustedPosition(newPosition);
            adjustedPosition -= orbitPath->getPrimeFoci();

            updatePosition(adjustedPosition);
        }

        void rotateAroundFoci(double angle)
        {
            //orbitPath->setOrigin(orbitPath->getPrimeFoci());
            double C = orbitPath->getC();
            orbitPath->setRotation(angle * 180 / (PI));
            sf::Vector2f newPosition(orbitPath->getPosition());
            newPosition.x = newPosition.x - ( C * std::cos(angle));
            newPosition.y = newPosition.y - (C * std::sin(angle));
            orbitPath->setPosition(newPosition);

        }

        void draw(sf::RenderWindow *window)
        {
            window->draw(*orbitPath);
            window->draw(*primeFoci);
            window->draw(*subPrimeFoci); 
        }

        double getE() {return orbitPath->getE();}
        double getA() {return orbitPath->getRadius().x;}

    private:
        void updatePosition(const sf::Vector2f& newPosition)
        {
            orbitPath->setPosition(newPosition);
            primeFoci->setPosition(orbitPath->getPrimeFoci() + orbitPath->getPosition());
            subPrimeFoci->setPosition(orbitPath->getSubPrimeFoci() + orbitPath->getPosition());
        }

        EllipseShape *orbitPath = nullptr;
        sf::CircleShape *primeFoci = nullptr;
        sf::CircleShape *subPrimeFoci = nullptr;
};