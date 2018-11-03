CXX 	= g++ -fPIC
INCLUDE = include
BIN 	= bin
BUILD 	= build
SRC 	= src
SLIB	= /usr/lib
DLIB 	= lib

CXXFLAGS = -std=c++11 -I$(INCLUDE)

all : $(BIN)/dltest $(BIN)/test

$(BIN)/dltest : $(SRC)/dltest.cpp $(DLIB)/MyMath.so
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/dltest.cpp -ldl

$(DLIB)/MyMath.so : $(BUILD)/MyMath.o
	$(CXX) -shared -o $@ $(BUILD)/MyMath.o

$(BIN)/test : $(SRC)/test.cpp $(SLIB)/libMyMath.so
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/test.cpp -lMyMath

$(SLIB)/libMyMath.so : $(BUILD)/MyMath.o
	$(CXX) -shared -o $@ $(BUILD)/MyMath.o

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear :
	rm -rf $(BIN)/test $(BIN)/dltest $(BUILD)/MyMath.o $(SLIB)/libMyMath.so $(DLIB)/MyMath.so
