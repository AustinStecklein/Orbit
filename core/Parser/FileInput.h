#pragma once
#include <string>
#include "rapidxml_utils.hpp"
#include "src/GameObject.h"
class FileInput
{
    private:
        rapidxml::xml_document<> doc;
        std::vector<GameObject*> objects;
        
        void readFile(std::string filename);
        void buildObject(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int color);
    public:
        std::vector<GameObject*> getObjectsFromFile();
};