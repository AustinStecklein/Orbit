#pragma once
#include <string>
#include "rapidxml_utils.hpp"
#include "src/GameObject.h"
#include "src/CelestialBody.h"
class FileInput
{
    private:
        rapidxml::xml_document<> doc;
        CelestialBody* objects;
        void readFile(std::string filename);
        void buildObject(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int color, int count);
    public:
        FileInput(CelestialBody* objects) :objects(objects) {}
        int getObjectsFromFile();
};