#include "renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

Renderer::Renderer() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }
}

void Renderer::run(Network& network) {
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Neural Network", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewInit();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // Draw synapses first
        for (auto neuron : network.getNeurons()) {
            float x1 = (neuron->getId() % 10) / 5.0f - 1.0f;
            float y1 = (neuron->getId() / 10) / 5.0f - 1.0f;

            for (auto synapse : neuron->getSynapses()) {
                float x2 = (synapse->getTo()->getId() % 10) / 5.0f - 1.0f;
                float y2 = (synapse->getTo()->getId() / 10) / 5.0f - 1.0f;
                drawSynapse(x1, y1, x2, y2);
            }
        }

        // Draw neurons
        for (auto neuron : network.getNeurons()) {
            float x = (neuron->getId() % 10) / 5.0f - 1.0f;
            float y = (neuron->getId() / 10) / 5.0f - 1.0f;
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
    for (int i = 0; i <= 20; i++) {
        float angle = i * 3.14159f * 2 / 20;
        glVertex2f(x + 0.02f * cos(angle), y + 0.02f * sin(angle));
    }
    glEnd();
}

void Renderer::drawSynapse(float x1, float y1, float x2, float y2) {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}
