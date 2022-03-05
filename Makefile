# TODO: build imgui from source with glfw dependencies

UNAME_S = $(shell uname -s)

CC = g++
CFLAGS = -std=c++17 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
LDFLAGS = -lGL -lGLEW -lglfw -lm

ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
	LDFLAGS += -ldl -lpthread
endif

SRC  = $(wildcard Natle.cpp) $(wildcard TLib/*.cpp) $(wildcard TLib/libs/imgui/*.cpp) $(wildcard TLib/libs/stb_image/*.cpp)
OBJ  = $(SRC:.cpp=.o)
BIN = bin

.PHONY: all clean

all: dirs game

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/game

game: $(OBJ)
	$(CC) -o $(BIN)/game $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
