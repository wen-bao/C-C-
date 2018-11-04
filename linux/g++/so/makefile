CXX 	= g++ -fPIC
INCLUDE = include
BIN 	= bin
BUILD 	= build
SRC 	= src
LIB		= lib

CXXFLAGS 	= -std=c++11 -I$(INCLUDE) -L$(LIB)
LD_RUN_PATH = -Wl,-rpath=../$(LIB)

all : $(BIN)/dltest $(BIN)/test

$(BIN)/dltest : $(SRC)/dltest.cpp $(LIB)/libMyMath.so
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/dltest.cpp -ldl

$(LIB)/libMyMath.so : $(BUILD)/MyMath.o
	$(CXX) -shared -o $@ $(BUILD)/MyMath.o

$(BIN)/test : $(SRC)/test.cpp $(LIB)/libMyMath.so
	$(CXX) $(CXXFLAGS) $(LD_RUN_PATH) -o $@ $(SRC)/test.cpp -lMyMath

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear :
	rm -rf $(BIN)/test $(BIN)/dltest $(BUILD)/MyMath.o $(LIB)/libMyMath.so
