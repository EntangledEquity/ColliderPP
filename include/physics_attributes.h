#pragma once
#include <SFML/Graphics.hpp>

struct PhysicalAttributes {
    float mass;
    float angularMass;
    float restitution;
    sf::Color color;
    bool is_static = true;
    bool is_real = true;

    static PhysicalAttributes DEFAULT_PHYSICS_ATTRIBUTE();
};


enum class ShapeID{
    NULL_SHAPE,
    CIRCLE_SHAPE,
    RECTANGLE_SHAPE,
    POLYGON_SHAPE
};
