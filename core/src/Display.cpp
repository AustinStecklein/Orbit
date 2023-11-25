#include "src/Display.h"
#include "src/CelestialBody.h"

void Display::buildView()
{
    //setup view
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Orbit");
    window->setVerticalSyncEnabled(true);
    view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_SIZE, WINDOW_SIZE));
    window->setView(*view);
     //rocket = new Rocket(*(objects.begin()), 5.97219E24, sf::Vector2f(100.f, 100.f), objects, 1);
}
void Display::setFocus(CelestialBody * focus) {this->focus = focus;}

void Display::draw()
{
    std::cout << "Start of draw\n";
    window->clear(sf::Color::Black);
    //Get view centered on focus
    if (focus != nullptr)
    {
        view->setCenter(focus->getPosition().x, focus->getPosition().y);
        window->setView(*view);
    }
    //Maybe reduce this down to one for loop at some point
    for(int i = 0; i < numObjects; i++)
    {

        objects[i].draw(window, OrbitMath::Vector3D());

    }
    //rocket->draw(window, OrbitMath::Vector3D());
    window->display();
    std::cout << "end of draw\n";
}
void Display::setObjects(CelestialBody * objects,  int numObjects)
{
    this->objects = objects;
    this->numObjects = numObjects;
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



