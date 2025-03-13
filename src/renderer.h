#ifndef RENDERER_H
#define RENDERER_H

#include "network.h"

class Renderer {
public:
    Renderer();
    void run(Network& network);
private:
    void drawNeuron(float x, float y, bool active);
    void drawSynapse(float x1, float y1, float x2, float y2);
};

#endif
