// /#include "src/CelestialBody"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace rapidxml;

int main()
{
    ifstream file ("dubinski.tab");
    if (!file.is_open())
        return -1;
    stringstream ss;
    xml_document<> doc;
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);
    xml_node<>* root = doc.allocate_node(node_element, "Objects");
    doc.append_node(root);
    int count = 0;
    while(file)
    {
        count++;
        string line;
        getline(file, line);
        ss << line;
        string item;
        ss >> item;
        char * name = doc.allocate_string(to_string(count).c_str());
        char * mass = doc.allocate_string(item.c_str());
        char * radius = doc.allocate_string(to_string(5).c_str());
        char * color = doc.allocate_string(to_string(count % 6).c_str());
        ss >> item;
        char * px = doc.allocate_string(item.c_str());
        ss >> item;
        char * py = doc.allocate_string(item.c_str());
        ss >> item;
        char * pz = doc.allocate_string(item.c_str());
        ss >> item;
        char * vx = doc.allocate_string(item.c_str());
        ss >> item;
        char * vy = doc.allocate_string(item.c_str());
        ss >> item;
        char * vz = doc.allocate_string(item.c_str());
        
        xml_node<>* object = doc.allocate_node(node_element, "Object");
        object->append_attribute(doc.allocate_attribute("name", name));
        object->append_attribute(doc.allocate_attribute("mass", mass));
        object->append_attribute(doc.allocate_attribute("radius", radius));
        object->append_attribute(doc.allocate_attribute("color", color));

        xml_node<>* velocity = doc.allocate_node(node_element, "Velocity");
        velocity->append_attribute(doc.allocate_attribute("x", vx));
        velocity->append_attribute(doc.allocate_attribute("y", vy));
        velocity->append_attribute(doc.allocate_attribute("z", vz));

        xml_node<>* position = doc.allocate_node(node_element, "Position");
        position->append_attribute(doc.allocate_attribute("x", px));
        position->append_attribute(doc.allocate_attribute("y", py));
        position->append_attribute(doc.allocate_attribute("z", pz));

        object->append_node(velocity);
        object->append_node(position);

        root->append_node(object);
        ss.clear();
    }

    ofstream outputFile ("dubinski.xml");
    outputFile << doc;
    outputFile.close();
    doc.clear();

    return 0;
}