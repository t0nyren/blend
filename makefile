CXX = g++
CXXFLAGS = -Wall -g -O3
INCL_FLAGS = -Iinclude
LD_FLAGS = -Llib/cv -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_flann -lopencv_objdetect
OMP_FLAG = -fopenmp

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJECTS =	$(BUILD_DIR)/stitcher.o \

TARGET1 = $(BIN_DIR)/stitch

.PHONY: all clean

all: $(TARGET1)

$(TARGET1) : $(OBJECTS) $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LD_FLAGS)
	
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCL_FLAGS)

clean:
	$(RM) $(TARGET) $(OBJECTS)