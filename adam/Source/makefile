cpp=g++
lnk=g++
cf=-std=c++14 -g -DDBG=1 -c
lf=-o eve
lib=-lncurses

all : eve

eve : eve.o tty.o parse.o
	$(lnk) $(lf) eve.o tty.o parse.o $(lib)

eve.o : eve.cpp tty.hpp
	$(cpp) $(cf) eve.cpp
	
tty.o : tty.cpp tty.hpp
	$(cpp) $(cf) tty.cpp
	
parse.o : parse.cpp parse.hpp
	$(cpp) $(cf) parse.cpp
	
clean :
	rm *.o eve
