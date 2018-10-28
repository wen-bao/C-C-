CXX 	= g++ -std=c++11
SRC 	= src
BIN 	= bin
LIB 	= lib
INCLUDE = include
BUILD 	= build

CXXFLAGS = -I$(INCLUDE) -L$(LIB)

$(BIN)/test : $(SRC)/test.cpp $(LIB)/libMyMath.a
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/test.cpp -lMyMath

$(LIB)/libMyMath.a : $(BUILD)/MyMath.o
	ar crv -o $@ $(BUILD)/MyMath.o

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear :
	rm -rf bin/* lib/* build/* 
