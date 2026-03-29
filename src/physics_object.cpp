#include "physics_object.h"


//constructor
PhysicsObject::PhysicsObject(ShapeID id, const sf::Vector2f& pos,const PhysicalAttributes& attr): position(pos),attributes(attr),ID(id){
}
//destructor
PhysicsObject::~PhysicsObject() = default;


const sf::Vector2f PhysicsObject::getPosition() const{
    return position;
}
void PhysicsObject::setPosition(const sf::Vector2f& newPosition){
    position=newPosition;
}
const sf::Vector2f PhysicsObject::getVelocity() const{
    return velocity;
}

void PhysicsObject::setVelocity(const sf::Vector2f& newVelocity){
    velocity=newVelocity;
}
const sf::Vector2f PhysicsObject::getAcceleration() const{
    return acceleration;
}

void PhysicsObject::setAcceleration(const sf::Vector2f& newAcceleration){
    acceleration=newAcceleration;
}
const float PhysicsObject::getAngle() const{
    return angle;
}
void PhysicsObject::setAngle(const float& newAngle){
    angle=newAngle;
}
const float PhysicsObject::getAngularVelocity() const{
    return angularVelocity;
}
void PhysicsObject::setAngularVelocity(const float& newAngularVelocity){
    angularVelocity=newAngularVelocity;
}
const float PhysicsObject::getAngularAcceleration() const{
    return angularAcceleration;
}
void PhysicsObject::setAngularAcceleration(const float& newAngularAcceleration){
    angularAcceleration=newAngularAcceleration;
}
const ShapeID PhysicsObject::getID() const{
    return ID;
}


//attributes
const PhysicalAttributes PhysicsObject::getAttributes() const{
    return attributes;
}
void PhysicsObject::setAttributes(const PhysicalAttributes& newAttributes){
    attributes=newAttributes;
}



void PhysicsObject::update(sf::Time dt){
    velocity+=acceleration*dt.asSeconds();
    position+=velocity*dt.asSeconds();
    acceleration = sf::Vector2f(0.f, 0.f);
}


void PhysicsObject::applyForce(const sf::Vector2f& force){
    if (attributes.is_static) {
        return;
    }
    acceleration+=force/attributes.mass;
}

void PhysicsObject::applyImpulse(const sf::Vector2f& impulse){
    if (attributes.is_static){
        return;
    }
    velocity+=impulse/attributes.mass;
}
