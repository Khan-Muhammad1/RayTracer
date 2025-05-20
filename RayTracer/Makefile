# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O2

# Build target executable:
TARGET = raytracer.exe

# Object files
OBJS = Main.o RayTracer.o

# Link objects into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp to main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile raytracer.cpp to raytracer.o
raytracer.o: raytracer.cpp
	$(CXX) $(CXXFLAGS) -c raytracer.cpp

# Clean up intermediate files
clean:
	rm -f $(OBJS) $(TARGET)

# PHONY targets are not file names
.PHONY: clean
