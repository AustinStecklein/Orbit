#include "rapidxml_utils.hpp"
#include "FileInput.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "src/CelestialBody.h"
#include "src/Vector3D.h"
#include <fstream>
#include <sstream>

/*
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
    std::cout << "Readfile\n";
}*/

int FileInput::getObjectsFromFile()
{
    std::ifstream file("./core/Parser/dubinski.tab");
    if (!file.is_open())
        std::cout << "File not found\n";

    std::cout << objects << std::endl;
    std::stringstream ss;
    int count = 0;
    //while(file)
    for (int i = 0; i < 15000; i ++)
    {
        std::string line;
        getline(file, line);
        ss << line;
        double mass;
        double x;
        double y;
        double z;
        ss >> mass;
        ss >> x;
        ss >> y;
        ss >> z;
        OrbitMath::Vector3D tempPoistion(x, y, z);
        ss >> x;
        ss >> y;
        ss >> z;
        OrbitMath::Vector3D tempVelocity(x, y, z);
        //std::cout << "count:" << count << std::endl; 
        this->buildObject(tempVelocity, tempPoistion, mass, .25, 1, count);
        count++;
    }


    return count;
}

void FileInput::buildObject(OrbitMath::Vector3D velocity, OrbitMath::Vector3D position, double mass, double radius, int color, int count)
{
    //GameObject * newObject = new CelestialBody(velocity, position, mass, radius, color);
    //objects.push_back(newObject);
    //CelestialBody newbody(velocity, position, mass, radius, color);
    //std::cout << objects + sizeof(GameObject *) * count << std::endl;
    objects[count].setValues(velocity, position, mass, radius, color);

}
