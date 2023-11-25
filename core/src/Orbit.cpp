#include "Orbit.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Parser/FileInput.h"
#include "src/Display.h"
#include "src/Octree.h"
#include <omp.h>
#define PI 3.14159265358979323846
#define DEG2RAD PI/180


void Orbit::setup()
{
    display = new Display(objects);
    display->buildView();
    //file parse test
    input = new FileInput(objects);
    numObjects = input->getObjectsFromFile();
    display->setFocus(&(objects[0]));
    display->setObjects(objects, numObjects);

}

void Orbit::gameLoop()
{
    clock.restart(); //start clock
    while (display->isWindowOpen())
    {   

        sf::Time time = clock.getElapsedTime();
        
        this->handleEvents(time);
        //rocket->updatePosition(time.asSeconds(), objects, SCALEFACTOR, simPaused);
        //std::vector<Point> points;
        points.clear();
        if (tree != nullptr)
            delete tree;
        tree = new Octree(OrbitMath::Vector3D(-30, -30, -30), OrbitMath::Vector3D(30, 30, 30));
        std::cout << "Start of building tree\n";
        for(int i = 0; i < numObjects; i++)
        {
            points.push_back(Point(objects[i].getPosition(), OrbitMath::Vector3D(0, 0, 0), objects[i].getMass()));
            tree->insert(&points.back());
        }
        std::cout << "end of building tree\n";
        tree->calculateCenterOfMass();
        std::cout << "end of center of mass\n";
        omp_set_num_threads(16);
        #pragma omp parallel for
        for(int i = 0; i < points.size(); i++)
        {
            OrbitMath::Vector3D a = tree->calculateForce(&points[i], SCALEFACTOR);
            objects[i].applyAccelerationVector(a, .5);
            objects[i].updatePosition(.5);
        }

        std::cout << "end of updating position\n";
        display->draw();
    }
}

void Orbit::handleEvents(sf::Time time)
{
    sf::Event event;
    while (display->getWindow()->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    display->getWindow()->close();
                    break;
                case sf::Event::Resized: // catch the resize events
                {
                    // update the view to the new size of the window
                    display->setWindowSize(event.size.width, event.size.height);
                }
                    break;
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    {
                        if (event.mouseWheelScroll.delta > 0)
                            display->zoomWindow(0.9f);
                        else
                            display->zoomWindow(1.1f);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    {
                        sf::Vector2i positioni = sf::Mouse::getPosition(*display->getWindow());
                        sf::Vector2f position = display->getWindow()->mapPixelToCoords(positioni);
                        OrbitMath::Vector3D truePosition(position.x, position.y, 0);
                            //for(auto it = objects.begin(); it != objects.end(); it++)
                            //{
                            //    if((*it)->withInObject(truePosition))
                            //    {
                            //        display->setFocus(*it);
                
                            //    }
                            //}
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.scancode == sf::Keyboard::Scan::Space)
                    {
                        //((Rocket*)rocket)->engineTurnOn(time.asSeconds());
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::Left)
                    {
                        //((Rocket*)rocket)->angleLeft();
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::Right)
                    {
                        //((Rocket*)rocket)->angleRight();
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::R)
                    {
                        //std::cout << "Orbit::Reloading XML file\n";
                        //objects.clear();
                        //objects = input->getObjectsFromFile();
                        //display->setFocus(*(objects.begin()));
                        //display->setObjects(objects);
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::P)
                    {
                        simPaused = !simPaused;
                    }
                    break;
                default:
                    break;
            }
        }
}
