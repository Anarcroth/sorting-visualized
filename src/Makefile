# Compiler:
CC = clang++

# Compiler flags:
#  -g    	adds debugging information to the executable file
#  -std=c++11	use c++ 11 standard
#  -Wall 	turns on most, but not all, compiler warnings
#  -lSDL2  	adds the SDL2 library
CPPFLAGS = -g -std=c++11 -Wall -lSDL2

# Invoke the first target entry:
default: srtv

# To create the executable file:
srtv: main.o
	$(CC) $(CPPFLAGS) -o srtv.app main.o

# Provide source files:
main.o: main.cpp
	$(CC) -c main.cpp

# Remove executable files, as well as old .o object
# files and *~ backup files:
clean:
	$(RM) srtv *.o *~
