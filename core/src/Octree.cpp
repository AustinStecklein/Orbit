//#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "Vector3D.h"
#include "Octree.h"
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

void Octree::insert(Point* point)
{
    // If the point is out of bounds
    if (point->position.x < topLeftFront.x || point->position.x > bottomRightBack.x  || point->position.y < topLeftFront.y 
     || point->position.y > bottomRightBack.y || point->position.z < topLeftFront.z || point->position.z > bottomRightBack.z) 
    {
        //cout << "Point is out of bound" << endl;
        return;
    }
    //std::cout << "point X: " << point->position.x << " Y: " << point->position.y << " Z: " << point->position.z << std::endl;
    // Binary search to insert the point
    double midx = (topLeftFront.x + bottomRightBack.x) / 2;
    double midy = (topLeftFront.y + bottomRightBack.y) / 2;
    double midz = (topLeftFront.z + bottomRightBack.z) / 2;
    int pos = -1;
    // Checking the octant of
    // the point
    if (point->position.x <= midx) 
        if (point->position.y <= midy) 
            if (point->position.z <= midz)
                pos = TopLeftFront;
            else
                pos = TopLeftBottom;
        else 
            if (point->position.z <= midz)
                pos = BottomLeftFront;
            else
                pos = BottomLeftBack;
    else 
        if (point->position.y <= midy) 
            if (point->position.z <= midz)
                pos = TopRightFront;
            else
                pos = TopRightBottom;
        else 
            if (point->position.z <= midz)
                pos = BottomRightFront;
            else
                pos = BottomRightBack;
 
    // If an empty node is encountered
    if (children[pos] == nullptr) 
    {
       // std::cout << "point being entered X: " << point->position.x << " Y: " << point->position.y << " Z: " << point->position.z << std::endl;   
        children[pos] = new Octree(point);
        return;
    }
 
    // If an internal node is encountered
    else if (children[pos]->point == nullptr) 
    {
        children[pos]->insert(point);
        return;
    }
    else 
    {
        Point* point_ = children[pos]->point;  
        //std::cout << "point_ X: " << point_->position.x << " Y: " << point_->position.y << " Z: " << point_->position.z << std::endl;   
        delete children[pos];
        children[pos] = nullptr;
        switch (pos)
        {
            case TopLeftFront:
                //std::cout << "here1" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(topLeftFront.x, topLeftFront.y, topLeftFront.z), OrbitMath::Vector3D(midx, midy, midz));
                break;
            case TopRightFront:
                //std::cout << "here2" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(midx, topLeftFront.y, topLeftFront.z), OrbitMath::Vector3D(bottomRightBack.x, midy, midz));
                break;
            case BottomRightFront:
                //std::cout << "here3" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(midx, midy, topLeftFront.z), OrbitMath::Vector3D(bottomRightBack.x, bottomRightBack.y, midz));
                break;
            case BottomLeftFront:
                //std::cout << "here4" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(topLeftFront.x, midy, topLeftFront.z), OrbitMath::Vector3D(midx, bottomRightBack.y, midz));
                break;
            case TopLeftBottom:
               // std::cout << "here5" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(topLeftFront.x, topLeftFront.y, midz), OrbitMath::Vector3D(midx, midy, bottomRightBack.z));
                break;
            case TopRightBottom:
                //std::cout << "here6" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(midx, topLeftFront.y, midz), OrbitMath::Vector3D(bottomRightBack.x, midy, bottomRightBack.z));
                break;
            case BottomRightBack:
                //std::cout << "here7" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(midx, midy, midz), OrbitMath::Vector3D(bottomRightBack.x, bottomRightBack.y, bottomRightBack.z));
                break;
            case BottomLeftBack:
                //std::cout << "here8" << std::endl;
                children[pos] = new Octree(OrbitMath::Vector3D(topLeftFront.x, midy, midz), OrbitMath::Vector3D(midx, bottomRightBack.y, bottomRightBack.z));
                break;
        }
        
        // Checking the octant of the new point
        children[pos]->insert(point_);
        children[pos]->insert(point);
    }
}

// Function that returns true if the point
// (x, y, z) exists in the octree
//THIS FUNCTION IS USED FOR TESTING
bool Octree::find(Point point)
{
 
    // Otherwise perform binary search
    // for each ordinate
    int midx = (topLeftFront.x + bottomRightBack.x) / 2;
    int midy = (topLeftFront.y + bottomRightBack.y) / 2;
    int midz = (topLeftFront.z + bottomRightBack.z) / 2;
 
    int pos = -1;
 
    // Deciding the position
    // where to move
    if (point.position.x <= midx) 
        if (point.position.y <= midy) 
            if (point.position.z <= midz)
                pos = TopLeftFront;
            else
                pos = TopLeftBottom;
        else 
            if (point.position.z <= midz)
                pos = BottomLeftFront;
            else
                pos = BottomLeftBack;
    else 
        if (point.position.y <= midy) 
            if (point.position.z <= midz)
                pos = TopRightFront;
            else
                pos = TopRightBottom;
        else 
            if (point.position.z <= midz)
                pos = BottomRightFront;
            else
                pos = BottomRightBack;
 
    // If an internal node is encountered
    if (children[pos] == nullptr) 
        return 0;
    // If an empty node is encountered
    else if (children[pos]->point == nullptr) 
        return children[pos]->find(point);
    else 
        // If node is found with
        // the given value
        if (point.position.x == children[pos]->point->position.x && point.position.y == children[pos]->point->position.y && point.position.z == children[pos]->point->position.z)
            return 1;
    return 0;
}

void Octree::calculateCenterOfMass()
{
    //This is a leaf so center of mass is the point
    if (point != nullptr)
        return;
    int numPoints= 0;
    for(int i = 0; i < 8; i++)
    {
        if(children[i] != nullptr)
        {
            children[i]->calculateCenterOfMass();
            centerOfMass += children[i]->getCenterMass();
            mass += children[i]->getMass();
            numPoints++;
        }
    }
    centerOfMass = centerOfMass / numPoints;
}

OrbitMath::Vector3D Octree::calculateForce(Point * point, double scaleFactor)
{
    double r = point->position.distance(centerOfMass);
    if (this->point != nullptr)
    {
        if ((int)r == 0)
        {
           //cout << "self found\n";
            return OrbitMath::Vector3D(0,0,0);
        }
        OrbitMath::Vector3D direction =  centerOfMass - point->position;
        direction = direction.Normalized();
        return direction * (((G * mass)/ ((r*r))));
    }
    else
    {
        if (abs(topLeftFront.x - bottomRightBack.x) / r < THETA)
        {
            OrbitMath::Vector3D direction =  centerOfMass - point->position;
            direction = direction.Normalized();
            return direction * (((G * mass)/ ((r*r))));
        }
        OrbitMath::Vector3D a;
        for(int i = 0; i < 8; i++)
            if(children[i] != nullptr)
                a += children[i]->calculateForce(point, scaleFactor);
        return a;
    }
}

void Octree::printOctree(int level)
{
    // Increase distance between levels
    level += 5;
 
    // Process right nodes first
    for (int i = 4; i < 8; i++)
    {
        if(children[i] != nullptr)
            children[i]->printOctree(level);
    }
    // Print current node after space
    // count
    cout << endl;
    for (int i = 5; i < level; i++)
        cout << " ";
    if(point == nullptr)
        cout << "junction" << "\n";
    else
        cout << point->position.x << "\n";
    // Process left child
    for (int i = 0; i < 4; i++)
    {
        if(children[i] != nullptr)
            children[i]->printOctree(level);
    }
}

