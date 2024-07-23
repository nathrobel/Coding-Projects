# Compiler
CXX = g++


# Include directories
INCLUDE_DIRS = -I include
SRC_INCLUDE_DIRS = -I src/include

# Compiler flags
 SDL_INCLUDE_DIRS= -I src/include \
           -I"C:\Users\natha\OneDrive\Desktop\Coding\Libraries\SDL2\i686-w64-mingw32\include\SDL2" \
           -I"C:\Users\natha\OneDrive\Desktop\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\include" \
           -I"C:\Users\natha\OneDrive\Desktop\SDL2_mixer-devel-2.8.0-mingw\SDL2_mixer-2.8.0\i686-w64-mingw32\include" \
           -I"C:\Users\natha\OneDrive\Desktop\SDL2_ttf-devel-2.22.0-mingw\SDL2_ttf-2.22.0\i686-w64-mingw32\include"


CXXFLAGS = $(INCLUDE_DIRS) $(SRC_INCLUDE_DIRS) $(SDL_INCLUDE_DIRS)

# Linker flags
LDFLAGS = -L src/lib \
          -L"C:\Users\natha\OneDrive\Desktop\Coding\Libraries\SDL2\i686-w64-mingw32\lib" \
          -L"C:\Users\natha\OneDrive\Desktop\SDL2_image-devel-2.8.2-mingw\SDL2_image-2.8.2\i686-w64-mingw32\lib" \
          -L"C:\Users\natha\OneDrive\Desktop\SDL2_mixer-devel-2.8.0-mingw\SDL2_mixer-2.8.0\i686-w64-mingw32\lib" \
          -L"C:\Users\natha\OneDrive\Desktop\SDL2_ttf-devel-2.22.0-mingw\SDL2_ttf-2.22.0\i686-w64-mingw32\lib" \
          -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Source files
SRCS = main.cpp AudioManager.cpp gameEngine.cpp window.cpp ball.cpp paddle.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main

# Default target
all: $(EXEC)

# Rule to link object files to create executable
$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile source files to object files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)
