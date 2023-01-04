MKDIR   := mkdir -p
RMDIR   := rm -rf
CC      := clang++
PROJECT := sprite
MODULES := Component Entity System Tools Other UserInterface
SRC     := .
BIN     := build/bin
OBJ     := build/obj
SRC_DIR := $(addprefix $(SRC)/,$(MODULES)) $(SRC)
OBJ_DIR := $(addprefix $(OBJ)/,$(MODULES))
INCLUDE := $(addprefix -I,$(SRC_DIR)) -IAssets
SRCS    := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS)) 
EXE     := $(BIN)/$(PROJECT)
CFLAGS  := $(INCLUDE) `sdl2-config --cflags` -std=c++17 -Wall -g
LDLIBS  := `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -g

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ_DIR):
	$(MKDIR) $@

run: $(EXE)
	$<

clean:
	$(RMDIR) $(OBJ) $(BIN)