# Compiler name
CC = g++

# Compiler parameters
CPPFLAGS = -std=c++11 -Wall -fno-rtti -fexceptions -c

# Delete command (for clean) depending on the OS
ifeq ($(OS), Windows_NT)
	RM = del /Q
else
	RM = rm -f
endif

VERSION = v1.2.0

OBJS = main.o Game.o RandomGenerator.o
TARGET = Bulls_and_Cows_$(VERSION).exe


all: $(TARGET)

$(TARGET) : $(OBJS) 
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.cpp Game.cpp Game.hpp RandomGenerator.cpp RandomGenerator.hpp
	$(CC) $(CPPFLAGS) main.cpp

Game.o: Game.cpp Game.hpp RandomGenerator.cpp RandomGenerator.hpp
	$(CC) $(CPPFLAGS) Game.cpp

RandomGenerator.o: RandomGenerator.cpp RandomGenerator.hpp
	$(CC) $(CPPFLAGS) RandomGenerator.cpp

clean:
	$(RM) *.o *.exe
