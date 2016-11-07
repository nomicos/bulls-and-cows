# Compiler name.
CC = g++

# Compiler compilation parameters.
FLAGS = -std=c++11 -Wall -fno-rtti -fexceptions

# Delete command (for clean) depending on the OS.
ifeq ($(OS), Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

# Current game version.
VERSION = v1.2.0

# Objects to build.
OBJS = main.o Game.o RandomGenerator.o

# Target executable.
TARGET = Bulls_and_Cows_$(VERSION).exe

all: $(TARGET)

$(TARGET) : $(OBJS) 
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $< $(FLAGS) -o $@

# Dependency rules.
main.o : RandomGenerator.hpp Game.hpp
Game.o : Game.hpp RandomGenerator.hpp
RandomGenerator.o : RandomGenerator.hpp

clean:
	$(RM) *.o *.exe
