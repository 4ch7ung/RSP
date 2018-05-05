CC = g++
CFLAGS = -g -c -Wall
LDFLAGS =
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXEC = $(BIN_DIR)/hello

all:	mkdirs $(SRC) $(EXEC)

$(EXEC):	$(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

mkdirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
