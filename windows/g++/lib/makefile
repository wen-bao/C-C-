test : test.cpp MyMath.lib
	g++ -o test test.cpp -L"." -lMyMath

MyMath.lib : MyMath.o
	ar cqs MyMath.lib MyMath.o

MyMath.o : MyMath.cpp MyMath.h
	g++ -c MyMath.cpp

clear : 
	del /f *.o *.lib *.exe