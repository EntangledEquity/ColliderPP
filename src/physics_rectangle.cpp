// #include "physics_rectangle.h"

// Rectangle::Rectangle(float w, float b, sf::Vector2f pos) : PhysicsObject(ShapeID::RECTANGLE_SHAPE, pos), width(b), breadth(b) {
//     shape.setSize(width,breadth);
//     shape.setOrigin(width/2, breadth/2);
//     shape.setPosition(pos);
//     shape.setFillColor(attribute.color);
// }

// void Rectangle::sync(){
//     shape.setPosition(PhysicsObject::getPosition());
// }

// void Rectangle::update(sf::Time dt) {
//     PhysicsObject::update(dt);
//     sync();
// }

// void Rectangle::draw(sf::RenderWindow& window) {
//     window.draw(shape);
// }

// float Rectangle::getWidth() const {
//     return width;
// }

// float Rectangle::getBreadth() const {
//     return breadth;
// }

// void Rectangle::setSize(const float w, const float b){
//     width = w;
//     breadth = b;
//     shape.setSize(w,b);
//     shape.setOrigin({width/2, breadth/2});
// }

