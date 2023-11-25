#pragma once
#include <vector>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "src/CelestialBody.h"
#define WINDOW_SIZE 1024
#define TIMESCALE 1000
#define VIEWSCALE 50/WINDOW_SIZE
class Display
{
    private:
        sf::RenderWindow * window;
        sf::View* view;
        GameObject * focus;
        CelestialBody * objects;
        int numObjects;
        //GameObject * rocket;

    public:
        Display(CelestialBody * objects): objects(objects), numObjects(0) {}
        void buildView();
        void setFocus(CelestialBody * focus);
        void draw();
        void setObjects(CelestialBody * objects,  int numObjects);
        void setWindowSize(float width, float height);
        void zoomWindow(float scale);
        bool isWindowOpen();
        sf::RenderWindow * getWindow() {return window;}
};