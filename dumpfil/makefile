cc = g++
cf =  -g3 -c -std=c++14 -fmax-errors=1
compile = mkdir -p $(obj) ; $(cc) $(cf) $< -o $@
link = mkdir -p $(bin) ; g++ $+ -o $@ $(libs)
lf =
libs = -lm

src = src/
bin = bin/
obj = obj/

all : $(bin)dmpfil

test3 : $(bin)test3


$(bin)dmpfil : $(obj)dmpfil.o $(obj)dfloat.o 
	$(link)
	
$(obj)dmpfil.o : $(src)dmpfil.cpp $(src)dfloat.hpp $(src)MapFile.hpp $(src)strings.hpp
	$(compile)

$(obj)dfloat.o : $(src)dfloat.cpp $(src)dfloat.hpp
	$(compile)
	
$(bin)test3 : $(obj)test3.o
	$(link)
	
$(obj)test3.o : $(src)test3.cpp
	$(compile)


