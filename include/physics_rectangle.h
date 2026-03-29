#pragma once

#include <SFML/Graphics.hpp>
#include "physics_object.h"

class Rectangle : public PhysicsObject {
private:
    float width;
    float breadth;
    sf::RectangleShape shape;
    ShapeID ID = ShapeID::RECTANGLE_SHAPE;

    void sync();
public:
    Rectangle(float width, float breadth, sf::Vector2f position);

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    float getWidth() const;
    float getBreadth() const;
    void setSize(const float w, const float b);
};