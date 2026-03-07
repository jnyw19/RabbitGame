CXX := g++
CXXFLAGS := -std=c++23 -O2

TARGET := bin/RabbitGame
OBJ_DIR := obj
SRC_DIR := src

SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/Rabbit.cpp $(SRC_DIR)/User.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET) run

$(TARGET): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(OBJ_DIR) bin/
