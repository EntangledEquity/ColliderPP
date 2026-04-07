#include "physics_circle.h"

Circle::Circle(float r, sf::Vector2f pos) : PhysicsObject(ShapeID::CIRCLE_SHAPE, pos), radius(r) {
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition(pos);
    shape.setFillColor(getAttributes().color);
}

void Circle::sync() {
    shape.setPosition(PhysicsObject::getPosition());
}

void Circle::update(sf::Time dt) {
    PhysicsObject::update(dt);
    sync();
}

void Circle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(const float r) {
    radius = r;
    shape.setRadius(radius);
    // shape.setOrigin(sf::Vector2f(radius, radius)); // pls check in future :)
}

const sf::FloatRect Circle::getGlobalBounds() const {
    sf::Vector2f a = sf::Vector2f(getRadius(),getRadius());
    return sf::FloatRect(getPosition() - a, a * 2.0f);
}