CC = g++
CFLAGS = -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -pthread

INC = -I$(SRC_FOLDER)

SRC_FOLDER = ./src
SRC_FILES = $(wildcard $(SRC_FOLDER)/*.cpp $(SRC_FOLDER)/**/*.cpp)

BUILD_FOLDER = ./build
TARGET_FILE = ./bin/multithreaded-game

OBJ_FOLDER = $(BUILD_FOLDER)/obj
OBJ_FILES = $(patsubst $(SRC_FOLDER)/%.cpp,$(OBJ_FOLDER)/%.o,$(SRC_FILES))

CFLAGS += $(INC)

all:
	$(MAKE) compile_all -B -j$$(nproc)

compile_all: $(OBJ_FILES)
	mkdir -p $(dir $(TARGET_FILE))
	$(CC) -o $(TARGET_FILE) $^ $(CFLAGS)

$(OBJ_FILES): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(CFLAGS) -c

clean:
	rm -r $(BUILD_FOLDER)

run:
	./$(TARGET_FILE)

zip:
	zip -r envio.zip Makefile $(SRC_FOLDER)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET_FILE)