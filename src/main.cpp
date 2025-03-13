#include <iostream>
#include "simulation.h"
#include "renderer.h"

int main() {
    std::cout << "Starting Neural Network Visualization...\n";

    Simulation sim(100);
    Renderer renderer;

    // Start OpenGL rendering
    renderer.run(sim.getNetwork());

    std::cout << "Visualization completed.\n";
    return 0;
}
