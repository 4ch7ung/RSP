CC = g++
CFLAGS = -g -c -Wall
LDFLAGS = -lncurses
BUILD_DIR = build
SRC_DIR = src
PRODUCT_NAME = program
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
EXEC = $(BIN_DIR)/$(PRODUCT_NAME)

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
