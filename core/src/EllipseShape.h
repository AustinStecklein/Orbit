#pragma once
#include <cmath>
class EllipseShape : public sf::Shape
{
public :
    //radius.x = the semi-major axis and radius.y = the semi-minor axis
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0)) : m_radius(radius)
    {
        updateFoci(radius);
        update();
    }

    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
        updateFoci(radius);
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

    virtual std::size_t  getPointCount() const
    {
        return 32; // fixed, but could be an attribute of the class if needed
    }

    virtual sf::Vector2f getPoint(std::size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

    sf::Vector2f getPrimeFoci() {return PrimeFoci;}
    sf::Vector2f getSubPrimeFoci() {return SubPrimeFoci;}
    float getC() {return C;}
    double getE() {return C / m_radius.x;}

private :
    void updateFoci(const sf::Vector2f& radius = sf::Vector2f(0, 0))
    {
        sf::Vector2f zeroVector = sf::Vector2f(0, 0);
        C = std::sqrt(std::pow(m_radius.x, 2) - std::pow(m_radius.y, 2));
        if (radius.x == radius.y)
        {
            PrimeFoci = zeroVector;
            SubPrimeFoci = zeroVector;
        }
        else 
        {
            PrimeFoci = sf::Vector2f(C, 0);
            SubPrimeFoci = sf::Vector2f(-C, 0);
        }
    }
    //X is semi major axis
    //Y is semi minor axis
    sf::Vector2f m_radius;
    //focus distance;
    float C;
    sf::Vector2f PrimeFoci;
    sf::Vector2f SubPrimeFoci;

    //TODO make number of points updatable
    //std::size_t points;
};