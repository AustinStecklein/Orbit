#include "rapidxml_utils.hpp"
#include "FileInput.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "src/CelestialBody.h"
#include "src/Vector3D.h"


void FileInput::readFile(std::string filename)
{
    std::string input_xml;
    std::string line;
    std::ifstream in(filename);

    // read file into input_xml
    while(getline(in,line))
        input_xml += line;

    // make a safe-to-modify copy of input_xml
    // (you should never modify the contents of an std::string directly)
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
    xml_copy.push_back('\0');

    doc.parse<0>(&xml_copy[0]);
}

std::vector<GameObject*> FileInput::getObjectsFromFile()
{
    objects.clear();
    readFile("./core/Parser/test.xml");
    rapidxml::xml_node<> *pRoot = doc.first_node();
    for (rapidxml::xml_node<> *object_node = pRoot->first_node("Object"); object_node; object_node = object_node->next_sibling("Object"))
    {
        rapidxml::xml_node<> *velocity_node = object_node->first_node("Velocity");
        rapidxml::xml_node<> *position_node = object_node->first_node("Position");
        if (velocity_node != nullptr && position_node != nullptr)
        {
            OrbitMath::Vector3D velocity(std::stod(velocity_node->first_attribute("x")->value()), std::stod(velocity_node->first_attribute("y")->value()), std::stod(velocity_node->first_attribute("z")->value()));
            OrbitMath::Vector3D position(std::stod(position_node->first_attribute("x")->value()), std::stod(position_node->first_attribute("y")->value()), std::stod(position_node->first_attribute("z")->value()));
            double mass = std::stod(object_node->first_attribute("mass")->value());
            double radius = std::stod(object_node->first_attribute("radius")->value());
            int color = std::stod(object_node->first_attribute("color")->value());
            this->buildObject(velocity, position, mass, radius, color);
        }
        else
            std::cout << "one of the nodes is null\n";
    }
    return objects;
}

void FileInput::buildObject(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int color)
{
    GameObject * newObject = new CelestialBody(velocity, position, mass, radius, color);
    objects.push_back(newObject);
}
