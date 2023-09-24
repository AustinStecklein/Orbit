#pragma once
#include <vector>
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#define WINDOW_SIZE 1024
#define TIMESCALE 1000
#define VIEWSCALE 50/WINDOW_SIZE
class Display
{
    private:
        sf::RenderWindow * window;
        sf::View* view;
        GameObject * focus;
        std::vector<std::vector<sf::Vertex>> objectsPaths;
        std::vector<GameObject *> objects;

    public:
        void buildView();
        void setFocus(GameObject * focus);
        void draw();
        void setObjects(std::vector<GameObject *> objects);
        void setWindowSize(float width, float height);
        void zoomWindow(float scale);
        bool isWindowOpen();
        void computerOffsets();
        sf::RenderWindow * getWindow() {return window;}
};