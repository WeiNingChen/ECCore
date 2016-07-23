AR       := ar
ARFLAGS  := cr
CXX      := g++
#CPPFLAGS := -O2 -I../lib
CPPFLAGS := -g -Wall -I../include -I/usr/local/include  

all : ../bin/EC_Core_test

../bin/EC_Core_test : main.o EC_Core.o ECC.o
	$(CXX) $(CPPFLAGS) -L/usr/local/lib $^ -o $@ -lgmp -lgmpxx -lpthread 

main.o: main.cpp EC_Core.o ECC.o 
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

ECDSA.o: ECDSA.cpp EC_Core.o ECC.o 
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

EC_Core.o : EC_Core.cpp ECC.o ../include/EC_Core.h ../include/ECC.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

ECC.o : ECC.cpp ../include/ECC.h
	$(CXX) $(CPPFLAGS) -c $< -o $@  

clean :
	-rm *.o
