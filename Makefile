CXX = g++
CXXFLAGS = -std=c++20 -O3 -Iinclude
SRC = src/Main.cpp src/Database.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = CR_DraftAI

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@