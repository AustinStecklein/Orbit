#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "Vector3D.h"
using namespace std;
#define TopLeftFront 0
#define TopRightFront 1
#define BottomRightFront 2
#define BottomLeftFront 3
#define TopLeftBottom 4
#define TopRightBottom 5
#define BottomRightBack 6
#define BottomLeftBack 7

#define G 6.6743E-11
#define THETA 1

// Structure of a point
struct Point {
    //int x;
    //int y;
    //int z;
    OrbitMath::Vector3D position;
    OrbitMath::Vector3D velocity;
    double mass;
    Point() :  mass(0)
    {
    }
 
    Point(OrbitMath::Vector3D position, OrbitMath::Vector3D velocity, double mass) : position(position), velocity(velocity), mass(mass)
    {
    }
};


class Octree
{
    public:    
        // Constructor with three arguments
        Octree(Point *point)
        {
            // To declare point node
            this->point = point;
            centerOfMass = point->position;
            mass = point->mass;
            children.assign(8, nullptr);
        }
    
        // Constructor with six arguments
        Octree(OrbitMath::Vector3D topLeftFront, OrbitMath::Vector3D bottomRightBack)
        {
            mass = 0;
            point = nullptr;
            this->topLeftFront = topLeftFront;
            this->bottomRightBack = bottomRightBack;   
            children.assign(8, nullptr);
        }

        ~Octree()
        {
            for (auto it = children.begin(); it != children.end(); it++)
            {
                if((*it) != nullptr)
                    delete (*it);
            }
        }

        void insert(Point* point);
        //used for testing
        bool find(Point point);
        void setCenterMass(OrbitMath::Vector3D center) {this->centerOfMass = center;}
        OrbitMath::Vector3D getCenterMass() {return centerOfMass;}
        void setMass(double mass) {this->mass = mass;}
        double getMass() {return mass;}
        void calculateCenterOfMass();
        OrbitMath::Vector3D calculateForce(Point* point, double scaleFactor);
        void printOctree(int level);

    protected:
        Point* point;
        // Represent the boundary of the cube
        OrbitMath::Vector3D topLeftFront, bottomRightBack;
        vector<Octree*> children;

        //TODO use point as the centerOfmass at some point
        OrbitMath::Vector3D centerOfMass;
        double mass;

        void octInsert(Point * point, Octree * node);
};

