#pragma once
#include <vector>
#include "CelestialBody.h"
#include <SFML/Graphics.hpp>
#include "Parser/FileInput.h"
#include "Display.h"


#define WINDOW_SIZE 1024
#define TIMESCALE 1000
#define VIEWSCALE 50/WINDOW_SIZE
#define EARTHMOONDISTANCE 3.84E8
#define SCALEFACTOR EARTHMOONDISTANCE/WINDOW_SIZE

class Orbit 
{
private:
    Display * display;
    sf::Clock clock;
    std::vector<GameObject *> objects;
    //GameObject * mainBody;
    FileInput *input;
    int iterations;
    int currentit;
    bool simPaused;

public:
    Orbit() {iterations = 100000; currentit=0; simPaused = true;}
    ~Orbit() {}
    void setup();
    void gameLoop();
    void handleEvents(sf::Time time);

};