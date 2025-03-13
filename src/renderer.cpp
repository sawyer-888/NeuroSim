#include "renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Renderer::Renderer() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }
}

void Renderer::run(Network& network) {
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Neural Network", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewInit();

    // Store neuron positions to avoid repeated calculations
    std::vector<std::pair<float, float>> neuronPositions(network.getNeurons().size());
    for (auto& neuron : network.getNeurons()) {
        float x = (neuron->getId() % 10) / 5.0f - 1.0f;
        float y = (neuron->getId() / 10) / 5.0f - 1.0f;
        neuronPositions[neuron->getId()] = {x, y};  // Cache position
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw synapses using batch processing
        std::vector<float> synapseVertices;
        for (auto& neuron : network.getNeurons()) {
            float x1 = neuronPositions[neuron->getId()].first;
            float y1 = neuronPositions[neuron->getId()].second;
            for (auto& synapse : neuron->getSynapses()) {
                float x2 = neuronPositions[synapse->getTo()->getId()].first;
                float y2 = neuronPositions[synapse->getTo()->getId()].second;
                synapseVertices.insert(synapseVertices.end(), {x1, y1, x2, y2});
            }
        }

        drawSynapses(synapseVertices);

        // Draw neurons
        for (auto& neuron : network.getNeurons()) {
            float x = neuronPositions[neuron->getId()].first;
            float y = neuronPositions[neuron->getId()].second;
            drawNeuron(x, y, neuron->getActivation() > 1.0f);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::drawNeuron(float x, float y, bool active) {
    glColor3f(active ? 1.0f : 0.2f, 0.2f, active ? 1.0f : 0.2f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 20; ++i) {
        float angle = i * 3.14159f * 2 / 20;
        glVertex2f(x + 0.02f * cos(angle), y + 0.02f * sin(angle));
    }
    glEnd();
}

void Renderer::drawSynapses(const std::vector<float>& vertices) {
    if (vertices.empty()) return;

    glColor3f(0.5f, 0.5f, 0.5f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices.data());
    glDrawArrays(GL_LINES, 0, vertices.size() / 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}
