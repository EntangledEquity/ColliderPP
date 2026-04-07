#include "simulation.h"
#include "mjson/json.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>

PhySimulator::PhySimulator(const std::string& config_file_address){
    JObject config_json(config_file_address.c_str());
    window.create(sf::VideoMode(int( config_json["screen_width"]),int(config_json["screen_height"])), std::string(config_json["Name"]));

}

void PhySimulator::process_event(){
    if (event.type == sf::Event::Closed) {
        window.close();
    }else if(event.type ==sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Escape)
            window.close();
    }
    else if(event.type == sf::Event::Resized){
        window.setView(sf::View(sf::FloatRect(0, 0,
        (float)event.size.width, (float)event.size.height)));
    }
}

void PhySimulator::render(){
    window.clear();
    engine.draw(window);
    window.display();
}

void PhySimulator::start_frame(){
    dt = clock.getElapsedTime();
    clock.restart();

    time_before_last_sec+=dt;
    frames_in_last_sec++;
    if(time_before_last_sec.asSeconds() >= 1.0f){
        std::cout << "FPS: \033[33m" << frames_in_last_sec << "\033[0m\n";

        frames_in_last_sec = 0;
        time_before_last_sec -= sf::seconds(1.0f);
    }
}
void PhySimulator::run(){
    clock.restart();
    while (window.isOpen()){

        
        while (window.pollEvent(event)){
            process_event();
        }
        start_frame();
        update();
        render();
    }
}

void PhySimulator::update(){
    engine.update(dt);
}

