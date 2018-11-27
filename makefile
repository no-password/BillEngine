ifeq ($(shell uname -s), Darwin)
LDFLAGS= -L/opt/local/lib -framework OpenGL -lglfw -lGLEW 
MESS=rm -r *.o core *.dSYM space
else
LDFLAGS=-lX11 -lGL -lGLU -lglut -lGLEW -lglfw
endif

CXX_FLAGS=-lm -Wall -std=c++17
CXX=g++

SRC_DIR=src
SRC_EXT=cpp
BUILD_DIR=build
TARGET=billengine.a
RUNNER=bin/demo
RUNNER_SRC=demo/demo.cpp
INCLUDE=-I include
TST_SRC_DIR=tst
TST_SUFFIX=Test
TST_DIR=bin/tst

SRC=$(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJ=$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.$(SRC_EXT)=.o))
TST=$(shell find $(TST_SRC_DIR) -type f -name *.$(SRC_EXT))
TST_OBJ=$(patsubst $(TST_SRC_DIR)/%,$(TST_DIR)/%,$(TST:.$(SRC_EXT)=))

MESS=rm bin/* build/*.o billengine.a

all: $(TARGET) $(RUNNER) $(TST_OBJ) test
$(TARGET): $(OBJ)
	#@echo "Linking... "
	#@echo "$(CXX) $^ -o $(TARGET) $(LDFLAGS)"
	#$(CXX) $^ -o $(TARGET) $(LDFLAGS) -o $(TARGET)
	ar rv $(TARGET) $(OBJ)

$(TST_DIR)/%: $(TST_SRC_DIR)/%.$(SRC_EXT) $(TARGET)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $< $(TARGET)

$(RUNNER): $(TARGET)
	$(CXX) $(CXX_FLAGS) $(RUNNER_SRC) $(TARGET) $(INCLUDE) $(LDFLAGS) -o $(RUNNER)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c -o $@ $<

test:
	for test in $$(ls $(TST_DIR)); do ./$(TST_DIR)/$$test; done

clean:
	$(MESS)
