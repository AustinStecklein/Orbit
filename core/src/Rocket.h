#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "EllipticalOrbit.h"
#include "CelestialBody.h"
#include "Vector3D.h"
#define PI 3.14159265358979323846
#define G 6.6743E-11

class Rocket : public GameObject
{       
    private:
        //sf::Vector2f velocity;
        //sf::Vector2f position;
         GameObject * orbitingBody;
        double takeOffVelocity;
        sf::Shape *shape;
        double angle;
        int burnDuration;
        bool engineOn;
        bool secondEngineOn;
        double EngineStart;
        double lastUpdate;
        double engineAcc;
        double u;
        double long a;
        double long e;
        double ellipseAngle;
        EllipticalOrbit * orbit;
        std::vector<sf::Vertex> forceVectors;
        std::vector<GameObject *> objects;
        double scalefactor;



        void defineOrbit(double scalefactor)
        {
            //Calculate theta
            OrbitMath::Vector3D pointVector = this->getPointVectorBetween();

            //find the angle between the two vectors pointing to the object pulling us in
            double theta = getAngleBetween2Vectors(velocity, pointVector, false) - (PI/2);
            double long magV = vectorMag(velocity);
            
            double long r =  this->getDistanceFromMainBody() * scalefactor;
            double Q = (std::pow(magV, 2) * r * scalefactor) / u;
            a = r /(2- Q);
            
            e = std::sqrt(1 + Q * (Q - 2) * (std::cos(theta) * std::cos(theta)));
            double long b = std::sqrt(std::pow(a, 2) - std::pow(e * a, 2));
            if (orbit != nullptr)
                delete orbit;
            orbit = new EllipticalOrbit(sf::Vector2f(a / scalefactor, b / scalefactor));
            orbit->setPositionOrigin(sf::Vector2f(orbitingBody->getPosition().x, orbitingBody->getPosition().y));
            

            //calculate ellipse rotation
            double dotProductRV = (velocity.x * (position.x * scalefactor)) + (velocity.y * (position.y * scalefactor));
            double positionScaler = (vectorMag(velocity) / u) - (1 / (vectorMag(position) * scalefactor)) * scalefactor;
            double velocityScaler = (dotProductRV / u);


            OrbitMath::Vector3D eccentricityVector = (positionScaler * position) - (velocityScaler * velocity);
            ellipseAngle = std::atan2(eccentricityVector.y, eccentricityVector.x);
            double thetaE = std::acos((1 - Q * std::pow(std::cos(theta), 2))/(std::sqrt(1 + Q * (Q -2) * std::pow(std::cos(theta), 2))));
            ellipseAngle -= thetaE;
            
            orbit->rotateAroundFoci(ellipseAngle);
        }
        
        bool isCollsion()
        {
            double distance = getDistanceFromMainBody();
            double rocketMesh = std::sqrt(2 * std::pow(10, 2)) / 2;
            if (distance <= (rocketMesh + ((CelestialBody*)orbitingBody)->getRadius()))
                return true;
            else 
                return false;
        }

        double vectorMag(OrbitMath::Vector3D a)
        {
            return std::sqrt(std::pow(a.x,2) + std::pow(a.y,2));
        }

        double getDistanceFromMainBody()
        {
            return std::sqrt(std::pow(position.x - orbitingBody->getPosition().x, 2) + std::pow(position.y - orbitingBody->getPosition().y, 2));
        }

        OrbitMath::Vector3D getPointVectorBetween()
        {
            return OrbitMath::Vector3D(orbitingBody->getPosition().x - position.x, orbitingBody->getPosition().y - position.y, 0);
        }

        double getAngleBetween2Vectors(OrbitMath::Vector3D a, OrbitMath::Vector3D b, bool angleCorrection = false)
        {
            //get magnitude of pointvector and the standard vector used to find angle
            double aMag = vectorMag(a);
            double bMag = vectorMag(b);

            //find the angle between the two vectors pointing to the object pulling us in
            double dotProduct = (a.x * b.x) + (a.y * b.y);
            double theta = 0;
            //This if function is to protect the std::acos function from values outside of the domain
            //This can happen from rounding errors that lead to too large of values
            double inverseCos = dotProduct / (aMag * bMag);
            if (((aMag * bMag) == 0) || (inverseCos == 0))
                theta = PI/2;
            else
            { 
                if (inverseCos > 1 || inverseCos < -1)
                    inverseCos = int(inverseCos);
                theta = std::acos(inverseCos);
            }            
            //since inverse cos only returns an angle between 0 and PI we need to make it negative if the dot product is negative
            if (angleCorrection)
            {
                if (a.y < 0)
                    theta = -theta;
            }

            return theta;
        }

        OrbitMath::Vector3D GetAVector(double scalefactor)
        {

            OrbitMath::Vector3D standardVector(10, 0, 0);

            //orgin shift to the location of the point and have the vector point to the object pulling us in
            OrbitMath::Vector3D pointVector = getPointVectorBetween();
            double distance = vectorMag(pointVector);
            double theta = this->getAngleBetween2Vectors(pointVector, standardVector, true);

            //Calcalute the force of acceleration on the point
            double a = (G * orbitingBody->getMass()) / std::pow(distance * scalefactor, 2);

            return OrbitMath::Vector3D(a * std::cos(theta), a * std::sin(theta), 0);
        }


    public:
        Rocket( GameObject * orbitShape, double mass, sf::Vector2f startPosition, std::vector<GameObject *> objects, double scalefactor)
        {
            //set up graphics
            shape = new sf::RectangleShape(sf::Vector2f(10.f, 10.f));
            shape->setFillColor(sf::Color::Red);
            shape->setOrigin(5.f, 5.f);
            shape->setPosition(startPosition);

            this->orbitingBody = orbitShape;
            this->mass = mass;
            this->position = OrbitMath::Vector3D(startPosition.x, startPosition.y);

            this->burnDuration = 5;
            this->u = orbitShape->getMass() * G;
            orbit = nullptr;
            angle = PI/2;
            //velocity = sf::Vector2f(0, 0);
            engineOn = false;
            secondEngineOn = true;
            engineAcc = -.60;
            lastUpdate = 0;
            EngineStart = 0;
            takeOffVelocity = 0;
            this->objects = objects;
            this->createVectors();
            this->scalefactor = scalefactor;
        }

        void engineTurnOn(double time)
        {
            if(!secondEngineOn)
                secondEngineOn = true;
            else
                secondEngineOn = false;
            engineOn = true;
            EngineStart = time;
            shape->setFillColor(sf::Color::Green);
        }

        void updatePosition(double t, const std::vector<GameObject*> &objects, double scaleFactor, bool pause)
        {
            //std::cout << "Position X: " << shape->getPosition().x << " Y: " << shape->getPosition().y << std::endl; 
            /*
            double elapsedtime = t - lastUpdate;
            //check if engine is still on
            if(t >= (EngineStart + burnDuration) && engineOn)
            {
                engineOn = false;
                shape->setFillColor(sf::Color::Red);
                defineOrbit(scalefactor);
            }

            //updated velocity & position differently since engine is on
            if (engineOn)
            {
                if (secondEngineOn)
                {
                    velocity += OrbitMath::Vector3D(1.75 * engineAcc * elapsedtime * std::cos(angle) * -1, 1.75 * engineAcc * elapsedtime * std::sin(angle));
                    position = position + OrbitMath::Vector3D(velocity.x * elapsedtime, velocity.y * elapsedtime);
                    defineOrbit(scalefactor);
                }
                else
                {
                    takeOffVelocity += engineAcc * elapsedtime;
                    velocity = OrbitMath::Vector3D(takeOffVelocity* std::cos(angle) * -1, takeOffVelocity * std::sin(angle));
                    position = position +OrbitMath::Vector3D(takeOffVelocity * elapsedtime * std::cos(angle) * -1, takeOffVelocity * elapsedtime* std::sin(angle));
                }
            }
            else
            {
                if(!this->isCollsion())
                {
                    OrbitMath::Vector3D acceleration = this->GetAVector(scalefactor);
                    velocity = velocity + OrbitMath::Vector3D(elapsedtime * acceleration.x, elapsedtime * acceleration.y);
                    position = position + OrbitMath::Vector3D(velocity.x * elapsedtime , velocity.y * elapsedtime);
                }
            }
            
       
           
            shape->setPosition(position.x, position.y);
            lastUpdate = t;*/
        }

        void draw(sf::RenderWindow *window, OrbitMath::Vector3D offset)
        {
            if (shape != nullptr)
                window->draw(*shape);
            //if (orbit != nullptr)
            //    orbit->draw(window);

            //this->drawVectors(window);
        }

        void angleLeft()
        {
            angle += PI/128;
            shape->rotate(-(PI/128) * 180/PI);

        }

        void angleRight()
        {
            angle -= PI/128;
            shape->rotate((PI/128) * 180/PI);
        }

        OrbitMath::Vector3D getPosition() {return position;}
        double getMass() {return mass;}

        bool withInObject(OrbitMath::Vector3D point)
        {
            if (point.x >= (position.x - 5) && point.x <= (position.x + 5) && point.y >= (position.y - 5) && point.y <= (position.y + 5))
                return true;
            else
                return false;
        }

    OrbitMath::Vector3D updateVectors(OrbitMath::Vector3D point)
    {
        OrbitMath::Vector3D summedVector(0,0);
        //This is the standardvector that is used to help find angle
        OrbitMath::Vector3D standardVector(10, 0);
        int scale = 100;

        for(auto it = objects.begin(); it != objects.end(); it++)
        {
            OrbitMath::Vector3D pointVector((*it)->getPosition().x - point.x, (*it)->getPosition().y - point.y);
            double distance = vectorMag(pointVector);
            double theta = this->getAngleBetween2Vectors(pointVector, standardVector, true);
            double a = G * (*it)->getMass() * scale / std::pow(distance * scalefactor, 2);
            summedVector +=  OrbitMath::Vector3D(a * std::cos(theta), a * std::sin(theta));
        }

        //fix the summedVector to be offset again
        summedVector += OrbitMath::Vector3D(point.x, point.y);
        return summedVector;
    }

    void createVectors()
    {
        int spacing = 50; //20 pixel spacing
        int squareSize = 1000; //1000 by 1000 square of dots;

        int numberOf = (squareSize / spacing);
        for (int i = -500; i <= squareSize - 500; i = i + spacing)
        {
            for (int j = -500; j <= squareSize- 500; j = j + spacing)
            {
                sf::Vertex point(sf::Vector2f(i, j));
                forceVectors.push_back(point);
            }
        }


    }

    void drawVectors(sf::RenderWindow *window)
    {
        sf::Vertex convertedVector[2];
        for (auto it = forceVectors.begin(); it != forceVectors.end(); it++)
        {
            OrbitMath::Vector3D newVector = updateVectors(OrbitMath::Vector3D(it->position.x, it->position.y));
            convertedVector[0] = sf::Vertex(sf::Vector2f(it->position.x, it->position.y));
            convertedVector[1] = sf::Vertex(sf::Vector2f(newVector.x, newVector.y));
            window->draw(convertedVector, 2, sf::Lines);
        }
    }
    void collidedWith() {}
    OrbitMath::Vector3D futurePoint() {return OrbitMath::Vector3D();}
    std::vector<OrbitMath::Vector3D> getFuturePoints() {return futurePoints;}
};