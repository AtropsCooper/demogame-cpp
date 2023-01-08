MKDIR   := mkdir
RMDIR   := rd /s /q 
CC      := g++
PROJECT := DinoDungeon
MODULES := Component Entity System Tools Other UserInterface
SRC     := .
BIN     := build/bin
OBJ     := build/obj
SRC_DIR := $(addprefix $(SRC)/,$(MODULES)) $(SRC)
OBJ_DIR := $(addprefix $(OBJ)/,$(MODULES))
INCLUDE := $(addprefix -I,$(SRC_DIR)) -IAssets
SRCS    := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJS    := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS)) 
EXE     := $(BIN)/$(PROJECT).exe
CFLAGS  := $(INCLUDE) -std=c++17 -Wall -O3
LDLIBS  := -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -mwindows

RC      := windres
RCFLAGS := 
RCS     := $(wildcard *.rc)
RCOBJS  := $(patsubst %.rc,$(OBJ)/%.o,$(RCS))

OBJS    := $(OBJS) $(RCOBJS)

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.rc
	$(RC) $(RCFLAGS) $< -o $@

$(BIN) $(OBJ_DIR):
	$(MKDIR) "$@"

run: $(EXE)
	$<

clean:
	$(RMDIR) "$(OBJ)"
	$(RMDIR) "$(BIN)"