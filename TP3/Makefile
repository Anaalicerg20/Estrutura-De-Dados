CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGETS = $(BIN_DIR)/tp2.out $(BIN_DIR)/tp3.out

OBJS = \
$(OBJ_DIR)/Compra.o \
$(OBJ_DIR)/HashMap.o \
$(OBJ_DIR)/Historico.o \
$(OBJ_DIR)/Produto.o \
$(OBJ_DIR)/Usuario.o \
$(OBJ_DIR)/Reposicao.o \
$(OBJ_DIR)/Sistema.o \
$(OBJ_DIR)/main.o

all: $(TARGETS)

# tp2.out
$(BIN_DIR)/tp2.out: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@

# tp3.out
$(BIN_DIR)/tp3.out: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@

# Compilação dos arquivos .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/tp2.out
	rm -f $(BIN_DIR)/tp3.out

rebuild: clean all

.PHONY: all clean rebuild