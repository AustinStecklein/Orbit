#pragma once
#include <vector>
#include "CelestialBody.h"
#include <SFML/Graphics.hpp>
#include "Parser/FileInput.h"
#include "Display.h"
#include "src/Octree.h"
#include <thread>
#include <mutex>

#define WINDOW_SIZE 1024
#define TIMESCALE 1000
#define VIEWSCALE 50/WINDOW_SIZE
#define EARTHMOONDISTANCE 3.84E8
#define SCALEFACTOR EARTHMOONDISTANCE/WINDOW_SIZE
#define NUMTHREADS 4

class Orbit 
{
private:
    Display * display;
    sf::Clock clock;
    //std::vector<GameObject *> objects;
    CelestialBody * objects;
    int numObjects;
    //GameObject * mainBody;
    FileInput *input;
    int iterations;
    int currentit;
    bool simPaused;


    std::vector<Point> points;
    Octree *tree;



public:
    Orbit(CelestialBody * objects): objects(objects), tree(nullptr) {simPaused = true;}
    ~Orbit() {}
    void setup();
    void gameLoop();
    void handleEvents(sf::Time time);
};