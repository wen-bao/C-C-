CXX 	= g++ -fPIC
INCLUDE = include
BIN 	= bin
BUILD 	= build
SRC 	= src
LIB		= /usr/lib

CXXFLAGS = -std=c++11 -I$(INCLUDE)

$(BIN)/test : $(SRC)/test.cpp $(LIB)/libMyMath.so
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)/test.cpp -lMyMath

$(LIB)/libMyMath.so : $(BUILD)/MyMath.o
	$(CXX) -shared -o $@ $(BUILD)/MyMath.o

$(BUILD)/MyMath.o : $(SRC)/MyMath.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/MyMath.cpp

clear :
	rm -rf $(BIN)/test $(BUILD)/MyMath.o $(LIB)/libMyMath.so
