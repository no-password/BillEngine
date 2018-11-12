ifeq ($(shell uname -s), Darwin)
LDFLAGS= -L/opt/local/lib -framework OpenGL -lglfw -lGLEW 
MESS=rm -r *.o core *.dSYM space
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw
endif

CXX_FLAGS=-lm -Wall
CXX=g++

SRC_DIR=src
SRC_EXT=cpp
BUILD_DIR=build
TARGET=bin/demo
INCLUDE=-I include

SRC=$(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJ=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.$(SRC_EXT)=.o))

MESS=rm bin/* build/*.o

$(TARGET): $(OBJ)
	@echo "Linking... "
	@echo "$(CXX) $^ -o $(TARGET) $(LDFLAGS)"
	$(CXX) $^ -o $(TARGET) $(LDFLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@echo "$(CXX) $(CXX_FLAGS) $(INCLUDE) -c -o $@ $<"
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c -o $@ $<


clean:
	$(MESS)
