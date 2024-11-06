# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# SDL2 flags (Windows with MSYS2)
SDL_INC = -IC:/msys64/mingw64/include/SDL2
SDL_LIB = -LC:/msys64/mingw64/lib
SDL_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Include directories
INCLUDES = -I$(INCDIR) $(SDL_INC)

# Target executable
TARGET = game.exe

# Build rules
all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SDL_LIB) $(SDL_FLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
	rm -f $(TARGET)

.PHONY: all clean