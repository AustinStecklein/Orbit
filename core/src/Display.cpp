#include "src/Display.h"
#include "src/CelestialBody.h"

void Display::buildView()
{
    //setup view
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Orbit");
    window->setVerticalSyncEnabled(true);
    view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE));
    window->setView(*view);
}
void Display::setFocus(GameObject * focus) {this->focus = focus;}

void Display::draw()
{
    window->clear(sf::Color::Black);
    //Get view centered on focus
    if (focus != nullptr)
    {
        view->setCenter(focus->getPosition().x, focus->getPosition().y);
        window->setView(*view);
    }
    //Maybe reduce this down to one for loop at some point
    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        (*it)->draw(window);

    }
    for(auto it = objectsPaths.begin(); it != objectsPaths.end(); it++)
    {
        window->draw(it->data(), it->size(), sf::Lines);
    }

    window->display();
}
void Display::setObjects(std::vector<GameObject *> objects)
{
    this->objects = objects;
}

void Display::setWindowSize(float width, float height)
{
    view->setSize(sf::Vector2f(width * VIEWSCALE, height * VIEWSCALE));
    window->setView(*view);
}

void Display::zoomWindow(float scale)
{
    view->zoom(scale);
    window->setView(*view);
}

bool Display::isWindowOpen() { return window->isOpen(); }

void Display::computerOffsets()
{
    std::vector<OrbitMath::Vector3D> focusPoints = focus->getFuturePoints();
    OrbitMath::Vector3D lastFocusPoint = *(focusPoints.end() -1);
    OrbitMath::Vector3D focusPosition = focus->getPosition();
    std::vector<sf::Vertex> vertexArray;
    std::vector<OrbitMath::Vector3D> currentPoints;
    objectsPaths.clear();
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        //This is an attempt to reduce the number of constructors and memory allocations called. not sure if it does much
        vertexArray.clear();
        currentPoints.clear();
        currentPoints = (*it)->getFuturePoints();
        for (int i = 0; i < currentPoints.size(); i++)
        {
            if (i >= focusPoints.size())
                vertexArray.push_back(sf::Vertex(sf::Vector2f(currentPoints[i].x - lastFocusPoint.x + focusPosition.x, currentPoints[i].y - lastFocusPoint.y + focusPosition.y), ((CelestialBody*)(*it))->getOrbitColor()));
            else
                vertexArray.push_back(sf::Vertex(sf::Vector2f(currentPoints[i].x - focusPoints[i].x + focusPosition.x, currentPoints[i].y - focusPoints[i].y + focusPosition.y), ((CelestialBody*)(*it))->getOrbitColor()));
        }
        objectsPaths.push_back(vertexArray);
    }
}


