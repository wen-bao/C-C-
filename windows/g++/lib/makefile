CXX 	= g++ -std=c++11
INCLUDE = include
SRC 	= src
BIN 	= bin
BUILD 	= build
LIB 	= lib

CXXFLAGS = -I$(INCLUDE) -L$(LIB)

$(BIN)/test : $(SRC)/test.cpp $(LIB)/MyMath.lib
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/test.cpp -lMyMath

$(LIB)/MyMath.lib : $(BUILD)/MyMath.o
	ar cqs $@ $(BUILD)/MyMath.o

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp $(INCLUDE)/MyMath.h
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear : 
	del /f $(BUILD)\*.o $(LIB)\*.lib $(BIN)\*.exe