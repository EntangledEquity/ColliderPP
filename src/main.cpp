#include <chrono>
#include <iostream>

#include "simulation.h"
using namespace std;

int main(){
    PhySimulator sim("assets/config.json");
    sim.run();

    return 0;
}