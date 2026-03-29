#include "physics_attributes.h"
//const PhysicalAttributes PhysicalAttributes::DEFAULT_PHYSICS_ATTRIBUTES{1.0f, 1.0f, 1.0f, sf::Color::White};
PhysicalAttributes DEFAULT_PHYSICS_ATTRIBUTE(){
    return{{1.0f, 1.0f, 1.0f, sf::Color(std::rand()%256,std::rand()%256,std::rand()%256)}};
}