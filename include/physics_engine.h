#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "physics_object.h"

class PhysicsEngine{
private:
  std::vector<std::unique_ptr<PhysicsObject>> objects;
  
  static bool(*collisionTable)(PhysicsObject*, PhysicsObject*) [4][4];

public:
  void addObject(std::unique_ptr<PhysicsObject> obj);

  
  void update(sf::Time dt);
  void draw(sf::RenderWindow& window);
};


