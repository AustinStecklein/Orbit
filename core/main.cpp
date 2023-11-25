#include "src/Orbit.h"
#include "src/GameObject.h"
#include <iostream>


int main()
{   
    CelestialBody * buffer = new CelestialBody[85000];
    std::cout << buffer << std::endl;
    std::cout << buffer + sizeof(CelestialBody *) << std::endl;
    Orbit orbit(buffer);
    orbit.setup();
    orbit.gameLoop();


    return 0;
}
