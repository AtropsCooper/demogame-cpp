MKDIR   := mkdir
RMDIR   := rd /s /q 
CC      := g++
PROJECT := DinoDungeon
MODULES := Component Entity System Tools Other UserInterface
SRC     := .
BIN     := build\bin
OBJ     := build\obj
SRC_DIR := $(addprefix $(SRC)/,$(MODULES)) $(SRC)
OBJ_DIR := $(addprefix $(OBJ)/,$(MODULES))
INCLUDE := $(addprefix -I,$(SRC_DIR)) -IAssets -IC:\MinGW\include\SDL2
SRCS    := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS)) 
EXE     := $(BIN)/$(PROJECT).exe
CFLAGS  := $(INCLUDE) -std=c++17 -Wall -g
LDFLAGS = -LC:\MinGW\lib -LC:\MinGW\bin
LDLIBS  := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS) res.res

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	windres res.rc -O coff -o res.res

$(BIN) $(OBJ_DIR):
	$(MKDIR) "$@"

run: $(EXE)
	$<

clean:
	$(RMDIR) $(OBJ) 
	$(RMDIR) $(BIN)