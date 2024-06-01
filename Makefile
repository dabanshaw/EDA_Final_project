CC=g++
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=*.cpp ./lib/*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=CGR
INCLUDES=-I./lib
JSON_INCLUDES=-I/home/sean/Desktop/NTUST_Course/112-2_Software_Development_for_Electronic_Design_Automation/EDA_Final_project/vcpkg/installed/x64-linux/include

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(JSON_INCLUDES) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
