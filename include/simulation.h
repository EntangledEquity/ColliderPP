#pragma once

#include "physics_engine.h"
#include "physics_circle.h"

class PhySimulator{
private:

    sf::RenderWindow window;

    sf::Event event;
    sf::Clock clock;
    sf::Time dt;
    sf::Time time_before_last_sec;
    unsigned int frames_in_last_sec = 0;

    PhysicsEngine engine;

    void process_event();
    void start_frame();

    void render();
    void update();
public:
    PhySimulator(const std::string& config_file_address);

    void run();
};
