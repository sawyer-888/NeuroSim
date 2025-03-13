CXX = g++
CXXFLAGS = -std=c++11 -O2 -I"./deps/GLFW/include" -I"./deps/GLEW/include"
LDFLAGS = -L"./deps/GLFW/lib" -L"./deps/GLEW/lib" -lglfw3 -lglew32 -lopengl32 -lgdi32

TARGET = NeuroSim

SRC = src/main.cpp src/neuron.cpp src/synapse.cpp src/network.cpp src/simulation.cpp src/renderer.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
