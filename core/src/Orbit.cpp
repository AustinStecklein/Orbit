#include "Orbit.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Parser/FileInput.h"
#include "src/Display.h"
#define PI 3.14159265358979323846
#define DEG2RAD PI/180

void Orbit::setup()
{
    display = new Display;
    display->buildView();
    //file parse test
    input = new FileInput;
    objects = input->getObjectsFromFile();
    display->setFocus(*(objects.begin()));
    display->setObjects(objects);

}

void Orbit::gameLoop()
{
    clock.restart(); //start clock
    while (display->isWindowOpen())
    {   

        sf::Time time = clock.getElapsedTime();
        
        this->handleEvents(time);
        for(auto it = objects.begin(); it != objects.end(); it++)
        {
            if(currentit < iterations)
            {
                (*it)->updatePosition(1, objects, SCALEFACTOR, simPaused);
                currentit++;
            }
        }
        if(currentit < iterations)
            display->computerOffsets();
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
                            for(auto it = objects.begin(); it != objects.end(); it++)
                            {
                                if((*it)->withInObject(truePosition))
                                {
                                    display->setFocus(*it);
                                    display->computerOffsets();
                                }
                            }
                    }
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.scancode == sf::Keyboard::Scan::Space)
                    {
                        //rocket->engineTurnOn(time.asSeconds());
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::Left)
                    {
                        //rocket->angleLeft();
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::Right)
                    {
                       // rocket->angleRight();
                    }
                    else if (event.key.scancode == sf::Keyboard::Scan::Scancode::R)
                    {
                        std::cout << "Orbit::Reloading XML file\n";
                        objects.clear();
                        objects = input->getObjectsFromFile();
                        display->setFocus(*(objects.begin()));
                        display->setObjects(objects);
                        display->computerOffsets();
                        currentit = 0;
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
