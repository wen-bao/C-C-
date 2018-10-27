CXX 	= g++ -std=c++11
SRC 	= src
BIN 	= bin
INCLUDE = include
BUILD 	= build

CXXFLAGS = -I$(INCLUDE) -L$(BIN)

$(BIN)/test : $(SRC)/test.cpp $(BIN)/MyMath.dll
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/test.cpp -lMyMath

$(BIN)/MyMath.dll : $(BUILD)/MyMath.o
	$(CXX) -shared -Wall -o $@ $(BUILD)/MyMath.o

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp $(INCLUDE)/MyMath.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear : 
	del /f $(BUILD)\*.o $(BIN)\*.exe $(BIN)\*.dll